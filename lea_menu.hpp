/*
    Lea - Lightweight UI for your tools.
    Copyright (C) 2022   Milutin Jovanović

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
