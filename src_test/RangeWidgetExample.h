#pragma once
#include <gtkmm/adjustment.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/dropdown.h>
#include <gtkmm/scale.h>
#include <gtkmm/scrollbar.h>
#include <gtkmm/separator.h>
#include <gtkmm/window.h>

#include <glibmm/refptr.h>

class RangeWidgetExample : public Gtk::Window {
  public:
    RangeWidgetExample(/* args */);
    ~RangeWidgetExample() override {};

  protected:
    // Signal handlers:
    void on_checkbutton_toggled();
    void on_dropdown_position();
    void on_adjustment1_value_changed();
    void on_adjustment2_value_changed();
    void on_button_quit() { set_visible(false); };

    // Child widgets: V: vertical box; H: horizontal box

    Gtk::Box m_VBox_Top, m_VBox2, m_VBox_HScale;
    Gtk::Box m_HBox_Scales, m_HBox_DropDown, m_HBox_Digits, m_HBox_PageSize;

    // all range widgets are associated with an Adjustment object.
    Glib::RefPtr<Gtk::Adjustment> m_adjustment;
    Glib::RefPtr<Gtk::Adjustment> m_adjustment_digits, m_adjustment_pagesize;

    Gtk::Scale m_VScale;
    Gtk::Scale m_HScale, m_Scale_Digits, m_Scale_PageSize;

    Gtk::Separator m_Separator;

    Gtk::CheckButton m_CheckButton;

    Gtk::Scrollbar m_Scrollbar;

    Gtk::DropDown m_DropDown_Position;

    Gtk::Button m_Button_Quit;

  private:
    /* data */
};
