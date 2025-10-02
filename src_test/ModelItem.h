
#pragma once

#include <glibmm/object.h>
#include <glibmm/ustring.h>

class ModelItem : public Glib::Object {
  public:
    // Create a new instance with a filename.
    static Glib::RefPtr<ModelItem> create(const Glib::ustring& filename);

    // Get the filename.
    Glib::ustring get_filename() const;

  protected:
    ModelItem(const Glib::ustring& filename);

  private:
    Glib::ustring m_filename;
};
