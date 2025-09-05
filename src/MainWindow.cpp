#include "MainWindow.h"
#include <iostream>

// ------------------------------------------------------------------------------------------------
MainWindow::MainWindow()
    : m_box_top(Gtk::Orientation::VERTICAL), m_box1(Gtk::Orientation::VERTICAL, 10),
      m_box2(Gtk::Orientation::VERTICAL, 10), m_radio_btn1("button1"), m_radio_btn2("button2"),
      m_radio_btn3("button3"), m_button_close("close") // creates a new button with label "close".
{
    // Set title and border of the window
    set_title("radio buttons");

    // Gtk::CheckButton and Gtk::ToggleButton have set_group() methods.
    // They act as radio buttons, if they are included in a group.

    // put button 2 and 3 in the same group as 1
    m_radio_btn2.set_group(m_radio_btn1);
    m_radio_btn3.set_group(m_radio_btn1);

    // add outer box to the window(because the window can only contain a single widget)
    set_child(m_box_top);

    // put the inner boxes and the separator in the outer box
    m_box_top.append(m_box1);
    m_box_top.append(m_separator);
    m_box_top.append(m_box2);
    m_separator.set_expand();

    // set the inner boxes' margins
    m_box1.set_margin(10);
    m_box2.set_margin(10);

    // put radio buttons in box 1
    m_box1.append(m_radio_btn1);
    m_box1.append(m_radio_btn2);
    m_box1.append(m_radio_btn3);
    m_radio_btn1.set_expand();
    m_radio_btn2.set_expand();
    m_radio_btn3.set_expand();

    // When first make a group of them, they will all be off. We set the 2nd button active
    m_radio_btn2.set_active();

    // Connect the toggled signal of the button to on_button_toggled()
    m_radio_btn1.signal_realize().connect(
        sigc::mem_fun(*this, &MainWindow::on_radio_button1_checked));
    m_radio_btn2.signal_realize().connect(
        sigc::mem_fun(*this, &MainWindow::on_radio_button2_checked));
    m_radio_btn3.signal_realize().connect(
        sigc::mem_fun(*this, &MainWindow::on_radio_button3_checked));
    m_radio_btn1.signal_unrealize().connect(
        sigc::mem_fun(*this, &MainWindow::on_radio_button1_unchecked));
    m_radio_btn2.signal_unrealize().connect(
        sigc::mem_fun(*this, &MainWindow::on_radio_button2_unchecked));
    m_radio_btn3.signal_unrealize().connect(
        sigc::mem_fun(*this, &MainWindow::on_radio_button3_unchecked));

    // put the Close button in Box 2 and set it as the default button
    m_box2.append(m_button_close);
    m_button_close.set_expand();
    // The default widget is the widget that is activated when the user presses Enter in a dialog.
    set_default_widget(m_button_close);

    // When the button receives the "clicked" signal, it will call the
    // on_close_button_clicked() method defined below.
    m_button_close.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::on_close_button_clicked));
}

// ------------------------------------------------------------------------------------------------
MainWindow::~MainWindow() {}

// ------------------------------------------------------------------------------------------------
void MainWindow::on_close_button_clicked() {
    std::cout << "Bye World!" << std::endl;

    // to close the application
    set_visible(false);
}

// ------------------------------------------------------------------------------------------------
void MainWindow::on_radio_button1_checked() { std::cout << "radio1 checked!" << std::endl; }

// ------------------------------------------------------------------------------------------------
void MainWindow::on_radio_button2_checked() { std::cout << "radio2 checked!" << std::endl; }

// ------------------------------------------------------------------------------------------------
void MainWindow::on_radio_button3_checked() { std::cout << "radio3 checked!" << std::endl; }

// ------------------------------------------------------------------------------------------------
void MainWindow::on_radio_button1_unchecked() { std::cout << "radio1 unrealized!" << std::endl; }

// ------------------------------------------------------------------------------------------------
void MainWindow::on_radio_button2_unchecked() { std::cout << "radio2 unrealized!" << std::endl; }

// ------------------------------------------------------------------------------------------------
void MainWindow::on_radio_button3_unchecked() { std::cout << "radio3 unrealized!" << std::endl; }