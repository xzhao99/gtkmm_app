#pragma once

// #include "GLViewport.h"
// #include "PipelineBrowser.h"
#include <gtkmm.h>

class MainWindow : public Gtk::ApplicationWindow {
  public:
    MainWindow();
    ~MainWindow() override = default;

  protected:
    // Signal handlers:
    void on_menu_others();

    void on_menu_choices(const Glib::ustring& parameter);
    void on_menu_choices_other(int parameter);
    void on_menu_toggle();

    // Child widgets:
    Gtk::Box m_Box;

    Glib::RefPtr<Gtk::Builder> m_refBuilder;

    // Two sets of choices:
    Glib::RefPtr<Gio::SimpleAction> m_refChoice;
    Glib::RefPtr<Gio::SimpleAction> m_refChoiceOther;

    Glib::RefPtr<Gio::SimpleAction> m_refToggle;
};
