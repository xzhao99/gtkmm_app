#pragma once
#include <gtkmm.h>

class MainApplication : public Gtk::Application {
  protected:
    MainApplication();

  public:
    static Glib::RefPtr<MainApplication> create();

  protected:
    // Overrides of default signal handlers:
    void on_startup() override;
    void on_activate() override;

  private:
    void create_window();

    void on_menu_file_new_generic();
    void on_menu_file_quit();
    void on_menu_help_about();

    Glib::RefPtr<Gtk::Builder> m_refBuilder;
};
