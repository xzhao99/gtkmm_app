#pragma once
#include <gtkmm.h>

#include "MachineWorks.h"

// Class for our OpenGL Canvas, inherits from Gtk::GLArea.
class MwGLArea : public Gtk::GLArea {
  public:
    MwGLArea();

  protected:
    // Signal handlers:
    void on_realize() override;
    void on_unrealize() override;
    bool on_render(const Glib::RefPtr<Gdk::GLContext>& context) override;
};