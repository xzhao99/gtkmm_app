#pragma once

#include <gtkmm.h>

class PipelineBrowser : public Gtk::ScrolledWindow {
  public:
    PipelineBrowser();
    ~PipelineBrowser() override = default;

    void add_model(const std::string& name);
    void set_visible(int row, bool visible);

    //
    class ModelItem : public Glib::Object {
      public:
        static Glib::RefPtr<ModelItem> create(const Glib::ustring& name);
        Glib::Property<Glib::ustring> name;
        Glib::Property<bool> visible;

      protected:
        ModelItem();
    };

  protected:
    Gtk::ColumnView m_column_view;
    Glib::RefPtr<Gio::ListStore<ModelItem>> m_list_store;
};
