#include "PipelineBrowser.h"

PipelineBrowser::PipelineBrowser() {
    // Use a ListStore of ModelItem
    // m_list_store = Glib::RefPtr<Gio::ListStore<ModelItem>>(ModelItem::create("")->get_type());
    // m_column_view.set_model(m_list_store);

    // Add columns: name, visible toggle
    // m_column_view.append_column(ModelItem::create("Name")->name());
    // m_column_view.append_column("Visible", ModelItem::create("")->visible());

    set_child(m_column_view);
}

void PipelineBrowser::add_model(const std::string& name) {
    auto item = ModelItem::create(name);
    m_list_store->append(item);
}

void PipelineBrowser::set_visible(int row, bool visible) {
    // auto obj = m_list_store->get(row);
    // auto item = Glib::RefPtr<ModelItem>::cast_dynamic(obj);
    // if (item) {
    //     item->visible = visible;
    // }
}

// PipelineBrowser::ModelItem::ModelItem() : name("ddd"), visible(true) {}

Glib::RefPtr<PipelineBrowser::ModelItem>
PipelineBrowser::ModelItem::create(const Glib::ustring& name_) {
    auto obj = Glib::RefPtr<ModelItem>(new ModelItem());
    obj->name = name_;
    obj->visible = true;
    return obj;
}
