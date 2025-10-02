#include "MainWindow.h"
#include "RangeWidgetExample.h"

#include <gtkmm/application.h>

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create("org.mesh.framework");

    // Shows the window and returns when it is closed.
    return app->make_window_and_run<MainWindow>(argc, argv);

    // return app->make_window_and_run<RangeWidgetExample>(argc, argv);
}