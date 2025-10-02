#pragma once
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/separator.h>
#include <gtkmm/window.h>

class MainWindow : public Gtk::Window {
  public:
    MainWindow();
    ~MainWindow() override;

  protected:
    // Signal handlers:
    void on_close_button_clicked();

    void on_radio_button1_checked();
    void on_radio_button2_checked();
    void on_radio_button3_checked();

    void on_radio_button1_unchecked();
    void on_radio_button2_unchecked();
    void on_radio_button3_unchecked();

    // Member widgets:
    Gtk::Box m_box_top, m_box1, m_box2;
    Gtk::CheckButton m_radio_btn1, m_radio_btn2, m_radio_btn3;
    Gtk::Separator m_separator;
    Gtk::Button m_button_close;
};
