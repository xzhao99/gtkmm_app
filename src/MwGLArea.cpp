#include "MwGLArea.h"

#include <cmath> // For mathematical functions
#include <filesystem>
#include <iostream> // For standard input/output operations
#include <vector>   // For std::vector
namespace fs = std::filesystem;

// -----------------------------------------------------------------------------------------------
MwGLArea::MwGLArea() {
    set_allowed_apis(Gdk::GLApi::GL);

#if 0
    auto motion_controller = Gtk::EventControllerMotion::create();
    motion_controller->signal_motion().connect(sigc::mem_fun(*this, &MwGLArea::on_mouse_motion));
    add_controller(motion_controller);

    auto click_controller_middle = Gtk::GestureClick::create();
    click_controller_middle->set_button(GDK_BUTTON_MIDDLE);
    click_controller_middle->signal_pressed().connect([this](int /*n_press*/, double x, double y) {
        this->on_mouse_press(GDK_BUTTON_MIDDLE, x, y);
    });
    click_controller_middle->signal_released().connect(
        sigc::mem_fun(*this, &MwGLArea::on_mouse_release));
    add_controller(click_controller_middle);

    auto click_controller_right = Gtk::GestureClick::create();
    click_controller_right->set_button(GDK_BUTTON_SECONDARY);
    click_controller_right->signal_pressed().connect([this](int /*n_press*/, double x, double y) {
        this->on_mouse_press(GDK_BUTTON_SECONDARY, x, y);
    });
    click_controller_right->signal_released().connect(
        sigc::mem_fun(*this, &MwGLArea::on_mouse_release));
    add_controller(click_controller_right);

    auto scroll_controller = Gtk::EventControllerScroll::create();
    scroll_controller->set_flags(Gtk::EventControllerScroll::Flags::VERTICAL);
    scroll_controller->signal_scroll().connect(
        [this](double /*dx*/, double dy) { return this->on_scroll(dy); }, false);
    add_controller(scroll_controller);
#endif

    set_focusable(true);
    set_focus_on_click(true);
}

// -----------------------------------------------------------------------------------------------
void MwGLArea::on_realize() {
    Gtk::GLArea::on_realize();

    initialize_mw();

    try {
        make_current();
        throw_if_error();

        // load Prim
        fs::path stl_file{"/mnt/c/workdir/data_cutsim/pg_test_swept_volume.stl"};
        LtBoolean try_to_close = FALSE;
        LtBoolean binary_file = TRUE;
        LtDouble max_vert_tol = 0.01;
        FILE* fp = LiFileOpen(stl_file.string().c_str(), LI_FILE_READ);
        if (fp) {
            LtPrim prim = LiMWUSolidCreateFromSTLFile(fp, binary_file, LI_MW_SOLID_TYPE_STOCK,
                                                      try_to_close, 0.0, max_vert_tol);
            LiFileClose(fp);
        } else {
            std::cerr << "\nFailed to open STL file. Terminate MachineWorks\n" << std::endl;
            LtStatus status = LiTerminate();
        }

    } catch (const Gdk::GLError& gle) {
        std::cerr << "GLArea error on realize: " << gle.domain() << "-" << gle.code() << "-"
                  << gle.what() << std::endl;
    }
}

// -----------------------------------------------------------------------------------------------
void MwGLArea::on_unrealize() {
    try {
        make_current();
        throw_if_error();

    } catch (const Gdk::GLError& gle) {
        std::cerr << "GLArea error on unrealize: " << gle.domain() << "-" << gle.code() << "-"
                  << gle.what() << std::endl;
    }

    terminate_mw();
    Gtk::GLArea::on_unrealize();
}

// -----------------------------------------------------------------------------------------------
bool MwGLArea::on_render(const Glib::RefPtr<Gdk::GLContext>& /*context*/) {
    try {
        make_current();
        throw_if_error();

        glViewport(0, 0, get_width(), get_height());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw_object();

        glFlush();

        return true;
    } catch (const Gdk::GLError& gle) {
        std::cerr << "GLArea error on render: " << gle.domain() << "-" << gle.code() << "-"
                  << gle.what() << std::endl;
        return false;
    }
}
