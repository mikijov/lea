#include "lea_menu.hpp"
#include "checks.hpp"

#include <lua.hpp>

LeaMenu::LeaMenu(lua_State *L) {
   _menu = std::make_shared<Gtk::Menu>();
}

LeaMenu::~LeaMenu() {
   LOG_FUNCTION;
}

void LeaMenu::registerClass(lua_State *L) {
   luabridge::getGlobalNamespace(L)
      .beginNamespace("lea")
         .beginClass<LeaMenu>("Menu")
            .addStaticFunction("create", &LeaMenu::create)
            .addFunction("addItem", &LeaMenu::addItem)
            .addFunction("addSeparator", &LeaMenu::addSeparator)
            .addFunction("addSubmenu", &LeaMenu::addSubmenu)
         .endClass()
      .endNamespace();
}

std::shared_ptr<LeaMenu> LeaMenu::create(
      lua_State *L)
{
   auto menu = std::make_shared<LeaMenu>(L);
   return menu;
}

void LeaMenu::addItem(
      const std::string& label,
      luabridge::LuaRef onSelect,
      lua_State *L
      )
{
   auto item = std::make_shared<Gtk::MenuItem>(label);
   item->show();
   item->signal_activate().connect(
         sigc::bind(
            sigc::mem_fun(*this,&LeaMenu::clickHandler),
            onSelect
            )
         );

   _items.push_back(item);
   _menu->append(*item);
}

void LeaMenu::addSeparator(
      lua_State *L
      )
{
   auto item = std::make_shared<Gtk::SeparatorMenuItem>();
   _items.push_back(item);
   item->show();
   _menu->append(*item);
}

std::shared_ptr<LeaMenu> LeaMenu::addSubmenu(
      const std::string& label,
      lua_State *L
      )
{
   auto item = std::make_shared<Gtk::MenuItem>(label);
   _items.push_back(item);

   auto submenu = create(L);
   item->set_submenu(*submenu->_menu);
   item->show();

   _menu->append(*item);

   return submenu;
}

void LeaMenu::clickHandler(const luabridge::LuaRef& onClick) {
   callr(onClick, this);
}

