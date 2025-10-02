#include "GLViewport.h"
#include <iostream>

GLViewport::GLViewport() {
    // Enable events for mouse/scroll
    set_can_focus(true);
    set_focus_on_click(true);

    /*
    *
    // Connect the scroll signal to the handler function
    m_eventControllerScroll = Gtk::EventControllerScroll::create();
    m_eventControllerScroll->signal_scroll().connect(
        sigc::mem_fun(*this, &GLViewport::on_scroll_event), false);

    signal_motion_notify_event().connect(sigc::mem_fun(*this, &GLViewport::on_motion_notify_event),
                                         false);
    signal_button_press_event().connect(sigc::mem_fun(*this, &GLViewport::on_button_press_event),
                                        false);
    signal_button_release_event().connect(
        sigc::mem_fun(*this, &GLViewport::on_button_release_event), false);
        */
}

Glib::RefPtr<Gdk::GLContext> GLViewport::on_create_context() {
    auto ctx = Gtk::GLArea::on_create_context();
    // Optionally configure GL version, etc.
    return ctx;
}

bool GLViewport::on_render(const Glib::RefPtr<Gdk::GLContext>& context) {
    make_current();
    if (has_error()) {
        std::cerr << "GLArea has error state\n";
        return false;
    }

    // Clear and render your mesh here
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup viewport, projection, model‑view etc, using m_zoom, m_rotate, m_translate

    // TODO: your rendering code...

    // If you want continuous animation, queue a redraw:
    queue_render();

    return true;
}

void GLViewport::on_resize(int width, int height) {
    Gtk::GLArea::on_resize(width, height);
    // Optionally update projection here
}

bool GLViewport::on_scroll_event(Gtk::EventControllerScroll* scroll_event) {
    double delta = 1.0;
    m_zoom *= 1.1;

    queue_render();
    return true;
}

bool GLViewport::on_button_press_event() {

    m_dragging = true;

    return true;
}

bool GLViewport::on_button_release_event() {

    m_dragging = false;
    return true;
}

bool GLViewport::on_motion_notify_event() {
    if (m_dragging) {
        double dx = m_last_x;
        double dy = m_last_y;
        // For example, drag can rotate or translate
        m_rotate_x += dy * 0.5;
        m_rotate_y += dx * 0.5;
        // m_last_x = ;
        // m_last_y = motion_event->y;
        queue_render();
    }
    return true;
}
