#pragma once

#include <gtkmm.h>

class Application : public Gtk::Application {
  protected:
    Application();

  public:
    static Glib::RefPtr<Application> create();

  protected:
    void on_startup() override;
    void on_activate() override;

#if 0
    void on_action_file_open();
    void on_action_file_quit();
    void on_action_help_about();
    Glib::RefPtr<Gio::SimpleAction> m_act_file_open;
    Glib::RefPtr<Gio::SimpleAction> m_act_file_quit;
    Glib::RefPtr<Gio::SimpleAction> m_act_help_about;
#endif

  private:
    void create_window();

    void on_menu_file_new_generic();
    void on_menu_file_quit();
    void on_menu_help_about();

    Glib::RefPtr<Gtk::Builder> m_refBuilder;
};
