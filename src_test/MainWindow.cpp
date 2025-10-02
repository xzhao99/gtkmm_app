#include "MainWindow.h"
#include <cmath>
#include <epoxy/gl.h>
#include <glibmm.h>
#include <iostream>
#include <memory>
#include <stdexcept>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// --- ModelItem Implementation ---
Glib::RefPtr<ModelItem> ModelItem::create(const Glib::ustring& filename) {
    return Glib::make_refptr_for_instance<ModelItem>(new ModelItem(filename));
}

Glib::ustring ModelItem::get_filename() const { return m_filename; }

ModelItem::ModelItem(const Glib::ustring& filename) : m_filename(filename) {}

// --- Shader sources ---
const GLchar* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    void main() {
        gl_Position = projection * view * model * vec4(aPos, 1.0);
    }
)";

const GLchar* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    }
)";

// --- MainWindow Implementation ---
MainWindow::MainWindow() {
    set_title("Mesh Framework (gtkmm 4.10+)");
    set_default_size(800, 600);

    auto app = get_application();
    if (app) {
        m_file_menu = Gio::Menu::create();
        m_file_menu->append("_Open", "app.open");
        m_file_menu->append("_Quit", "app.quit");
        m_menu_bar.set_menu_model(m_file_menu);
        m_main_box.append(m_menu_bar);
    }

    app->add_action("open", sigc::mem_fun(*this, &MainWindow::on_menu_file_open));
    app->add_action("quit", sigc::mem_fun(*this, &MainWindow::on_menu_file_quit));

    auto toolbar_box = Gtk::Box(Gtk::Orientation::HORIZONTAL);
    m_main_box.append(toolbar_box);

    m_open_toolbutton.set_icon_name("document-open-symbolic");
    m_open_toolbutton.set_tooltip_text("Open a file");
    toolbar_box.append(m_open_toolbutton);

    auto open_menu_item = Gio::Menu::create();
    open_menu_item->append("Open", "app.open");
    m_open_toolbutton.set_menu_model(open_menu_item);

    m_main_box.append(m_content_box);
    m_content_box.set_hexpand(true);
    m_content_box.set_vexpand(true);

    m_pipeline_frame.set_label("Pipeline Browser");
    m_content_box.append(m_pipeline_frame);
    m_pipeline_frame.set_size_request(200, -1);
    m_pipeline_frame.set_halign(Gtk::Align::FILL);
    m_pipeline_frame.set_valign(Gtk::Align::FILL);

    m_pipeline_frame.set_child(m_scrolled_window);
    m_scrolled_window.set_child(m_pipeline_listview);

    m_ref_liststore = Gio::ListStore<ModelItem>::create();
    m_ref_selection_model = Gtk::SingleSelection::create(m_ref_liststore);
    m_pipeline_listview.set_model(m_ref_selection_model);

    auto factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect([](const Glib::RefPtr<Gtk::ListItem>& item) {
        item->set_child(*Gtk::manage(new Gtk::Label()));
    });
    factory->signal_bind().connect([](const Glib::RefPtr<Gtk::ListItem>& item) {
        auto generic_item = item->get_item();
        auto model_item = std::dynamic_pointer_cast<ModelItem>(generic_item);
        if (model_item) {
            auto label = dynamic_cast<Gtk::Label*>(item->get_child());
            if (label) {
                label->set_text(model_item->get_filename());
            }
        }
    });
    m_pipeline_listview.set_factory(factory);

    m_view_frame.set_label("View");
    m_content_box.append(m_view_frame);
    m_view_frame.set_hexpand(true);
    m_view_frame.set_vexpand(true);
    m_view_frame.set_child(m_gl_area);

    m_gl_area.set_auto_render(true);

    m_gl_area.signal_realize().connect(sigc::mem_fun(*this, &MainWindow::on_realize));
    m_gl_area.signal_unrealize().connect(sigc::mem_fun(*this, &MainWindow::on_unrealize));

    // FINAL FIX: Using a lambda expression to correctly bind the render signal
    m_gl_area.signal_render().connect(
        [this](const std::shared_ptr<Gdk::GLContext>& context) { return on_render(context); },
        false);

    m_motion_controller = Gtk::EventControllerMotion::create();
    m_motion_controller->signal_motion().connect(sigc::mem_fun(*this, &MainWindow::on_motion));
    m_gl_area.add_controller(m_motion_controller);

    m_scroll_controller = Gtk::EventControllerScroll::create();
    m_scroll_controller->set_flags(Gtk::EventControllerScroll::Flags::VERTICAL);
    m_scroll_controller->signal_scroll().connect(sigc::mem_fun(*this, &MainWindow::on_scroll),
                                                 false);
    m_gl_area.add_controller(m_scroll_controller);

    m_click_controller = Gtk::GestureClick::create();
    m_click_controller->set_button(0);
    m_click_controller->signal_pressed().connect(sigc::mem_fun(*this, &MainWindow::on_button_press),
                                                 false);
    m_click_controller->signal_released().connect(
        sigc::mem_fun(*this, &MainWindow::on_button_release), false);
    m_gl_area.add_controller(m_click_controller);

    set_child(m_main_box);
}

MainWindow::~MainWindow() {}

void MainWindow::on_realize() {
    m_gl_area.make_current();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    m_program = glCreateProgram();
    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);
    glLinkProgram(m_program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f};

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void MainWindow::on_unrealize() {
    m_gl_area.make_current();
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteProgram(m_program);
}

bool MainWindow::on_render(const std::shared_ptr<Gdk::GLContext>& context) {
    m_gl_area.make_current();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(m_program);

    GLint modelLoc = glGetUniformLocation(m_program, "model");
    GLint viewLoc = glGetUniformLocation(m_program, "view");
    GLint projLoc = glGetUniformLocation(m_program, "projection");

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(m_rotate_x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_rotate_y), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(m_pan_x, m_pan_y, -3.0f * m_zoom));

    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f), (float)m_gl_area.get_width() / (float)m_gl_area.get_height(), 0.1f,
        100.0f);

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    return true;
}

void MainWindow::on_menu_file_open() {
    auto dialog = Gtk::FileDialog::create();
    dialog->set_title("Open File");
    dialog->open(*this, sigc::mem_fun(*this, &MainWindow::on_file_dialog_open_response));
}

void MainWindow::on_file_dialog_open_response(const Glib::RefPtr<Gio::AsyncResult>& result,
                                              const Glib::RefPtr<Gtk::FileDialog>& dialog) {
    try {
        auto file = dialog->open_finish(result);
        if (file) {
            std::cout << "Opened file: " << file->get_path() << std::endl;
            auto model_item = ModelItem::create(file->get_path());
            m_ref_liststore->append(model_item);
        } else {
            std::cout << "File dialog was cancelled." << std::endl;
        }
    } catch (const Glib::Error& ex) {
        std::cerr << "Error opening file: " << ex.what() << std::endl;
    }
}

void MainWindow::on_menu_file_quit() { hide(); }

void MainWindow::on_motion(double x, double y) {
    if (m_left_mouse_down) {
        m_pan_x += (x - m_last_x) * 0.005f * m_zoom;
        m_pan_y -= (y - m_last_y) * 0.005f * m_zoom;
        m_gl_area.queue_render();
    } else if (m_right_mouse_down) {
        m_rotate_y += (x - m_last_x) * 0.5f;
        m_rotate_x += (y - m_last_y) * 0.5f;
        m_gl_area.queue_render();
    }
    m_last_x = x;
    m_last_y = y;
}

void MainWindow::on_button_press(int n_press, double x, double y) {
    m_last_x = x;
    m_last_y = y;
    if (m_click_controller->get_current_button() == 1) {
        m_left_mouse_down = true;
    } else if (m_click_controller->get_current_button() == 3) {
        m_right_mouse_down = true;
    }
}

void MainWindow::on_button_release(int n_press, double x, double y) {
    if (m_click_controller->get_current_button() == 1) {
        m_left_mouse_down = false;
    } else if (m_click_controller->get_current_button() == 3) {
        m_right_mouse_down = false;
    }
}

void MainWindow::on_scroll(double dx, double dy) {
    if (dy > 0) {
        m_zoom *= 0.9f;
    } else if (dy < 0) {
        m_zoom *= 1.1f;
    }
    m_gl_area.queue_render();
}
