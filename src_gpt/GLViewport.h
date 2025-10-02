#pragma once

#include <gtkmm.h>

#include <epoxy/gl.h>

class GLViewport : public Gtk::GLArea {
  public:
    GLViewport();
    ~GLViewport() override = default;

  protected:
    // Overrides
    Glib::RefPtr<Gdk::GLContext> on_create_context() override;
    bool on_render(const Glib::RefPtr<Gdk::GLContext>& context) override;
    void on_resize(int width, int height) override;

    // Input handlers
    bool on_scroll_event(Gtk::EventControllerScroll* scroll_event);
    bool on_motion_notify_event();
    bool on_button_press_event();
    bool on_button_release_event();

    Glib::RefPtr<Gtk::EventControllerScroll> m_eventControllerScroll;

    // Internal state
    double m_zoom = 1.0;
    double m_rotate_x = 0.0, m_rotate_y = 0.0;
    double m_translate_x = 0.0, m_translate_y = 0.0;
    bool m_dragging = false;
    double m_last_x = 0.0, m_last_y = 0.0;
};
