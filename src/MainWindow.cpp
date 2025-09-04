#include "MainWindow.h"
#include <iostream>

// ------------------------------------------------------------------------------------------------
MainWindow::MainWindow()
    : m_button("Print Hello World") // creates a new button with label "Print Hello World".
{
    // Sets the margin around the button.
    m_button.set_margin(10);

    // When the button receives the "clicked" signal, it will call the
    // on_button_clicked() method defined below.
    m_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_clicked));

    // This packs the button into the Window (a container).
    set_child(m_button);
}

// ------------------------------------------------------------------------------------------------
MainWindow::~MainWindow() {}

// ------------------------------------------------------------------------------------------------
void MainWindow::on_button_clicked() { std::cout << "Hello World!" << std::endl; }