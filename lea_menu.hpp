#pragma once

#include <lua.hpp>
#include <LuaBridge.h>

#include <gtkmm.h>

#include <memory>

class LeaMenuItem;

class LeaMenu : public std::enable_shared_from_this<LeaMenu> {
   public:
      explicit LeaMenu(lua_State *L);
      virtual ~LeaMenu();

      static void registerClass(lua_State *L);

      std::shared_ptr<Gtk::Menu> _menu;

   private:
      static std::shared_ptr<LeaMenu> create(
            lua_State *L
            );
      void addItem(
            const std::string& label,
            luabridge::LuaRef onSelect,
            lua_State *L
            );
      void addSeparator(
            lua_State *L
            );
      std::shared_ptr<LeaMenu> addSubmenu(
            const std::string& label,
            lua_State *L
            );

      std::vector<std::shared_ptr<Gtk::MenuItem> > _items;

      void clickHandler(const luabridge::LuaRef& onClick);

   private:
      LeaMenu(const LeaMenu& other);
      const LeaMenu& operator=(const LeaMenu& other);
};

// class LeaMenuItem : public std::enable_shared_from_this<LeaMenuItem> {
//    public:
//       explicit LeaMenuItem(lua_State *L);
//       virtual ~LeaMenuItem();
//
//       static void registerClass(lua_State *L);
//
//    private:
//       static std::shared_ptr<LeaMenuItem> create(
//             lua_State *L
//             );
//
//       luabridge::LuaRef _onMousePress;
//       luabridge::LuaRef _onMouseRelease;
//       luabridge::LuaRef _onMouseScroll;
//       luabridge::LuaRef _userdata;
//
//       bool mousePressHandler(GdkEventButton* e);
//       bool mouseReleaseHandler(GdkEventButton* e);
//       bool mouseScrollHandler(GdkEventScroll* e);
//
//       Glib::RefPtr<Gtk::MenuItem> _menuItem;
//       Glib::RefPtr<Gtk::Menu> _submenu;
//
//    private:
//       LeaMenuItem(const LeaMenuItem& other);
//       const LeaMenuItem& operator=(const LeaMenuItem& other);
// };
