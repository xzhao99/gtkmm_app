#pragma once
#include "MyGLArea.h"

class MainWindow : public Gtk::ApplicationWindow {
  public:
    MainWindow();
    virtual ~MainWindow() {};

  protected:
    // Signal handlers:
    void on_menu_others();

    void on_menu_choices(const Glib::ustring& parameter);
    void on_menu_choices_other(int parameter);
    void on_menu_toggle();

    // Child widgets:
    Gtk::Box m_main_vbox;
    MyGLArea m_gl_area; // Our OpenGL area
    Glib::RefPtr<Gtk::Builder> m_refBuilder;

    // Two sets of choices:
    Glib::RefPtr<Gio::SimpleAction> m_refChoice;
    Glib::RefPtr<Gio::SimpleAction> m_refChoiceOther;

    Glib::RefPtr<Gio::SimpleAction> m_refToggle;
};