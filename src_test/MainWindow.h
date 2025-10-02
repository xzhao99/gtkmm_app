#pragma once

#include "ModelItem.h"
#include <epoxy/gl.h>
#include <gtkmm.h>
#include <string>
#include <vector>

class MainWindow : public Gtk::Window {
  public:
    MainWindow();
    virtual ~MainWindow();

  protected:
    // Signal handlers for menu actions
    void on_menu_file_open();
    void on_menu_file_quit();

    // Signal handlers for Gtk::GLArea
    void on_realize();
    void on_unrealize();
    bool on_render(const std::shared_ptr<Gdk::GLContext>& context);

    // Event handlers for mouse interaction using Gtk::EventController
    void on_motion(double x, double y);
    void on_button_press(int n_press, double x, double y);
    void on_button_release(int n_press, double x, double y);
    void on_scroll(double dx, double dy);

    // Callback for the asynchronous FileDialog
    void on_file_dialog_open_response(const Glib::RefPtr<Gio::AsyncResult>& result,
                                      const Glib::RefPtr<Gtk::FileDialog>& dialog);

    // Member widgets
    Gtk::Box m_main_box{Gtk::Orientation::VERTICAL};
    Gtk::Box m_content_box{Gtk::Orientation::HORIZONTAL};

    // Menu and Toolbar
    Glib::RefPtr<Gio::Menu> m_file_menu;
    Gtk::PopoverMenuBar m_menu_bar;
    Gtk::MenuButton m_open_toolbutton;

    // Pipeline browser (using modern Gtk::ListView)
    Gtk::Frame m_pipeline_frame;
    Gtk::ScrolledWindow m_scrolled_window;
    Glib::RefPtr<Gio::ListStore<ModelItem>> m_ref_liststore;
    // New: Selection model for the ListView
    Glib::RefPtr<Gtk::SingleSelection> m_ref_selection_model;
    Gtk::ListView m_pipeline_listview;

    // View window (now with Gtk::GLArea)
    Gtk::Frame m_view_frame;
    Gtk::GLArea m_gl_area;

  private:
    // Event controllers for the GLArea
    Glib::RefPtr<Gtk::EventControllerMotion> m_motion_controller;
    Glib::RefPtr<Gtk::EventControllerScroll> m_scroll_controller;
    Glib::RefPtr<Gtk::GestureClick> m_click_controller;

    // OpenGL render state
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_program;

    // Camera state
    float m_zoom = 1.0f;
    float m_pan_x = 0.0f;
    float m_pan_y = 0.0f;
    float m_rotate_x = 0.0f;
    float m_rotate_y = 0.0f;

    // Mouse interaction state
    double m_last_x, m_last_y;
    bool m_left_mouse_down = false;
    bool m_right_mouse_down = false;
};
