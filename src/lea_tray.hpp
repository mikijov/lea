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

#include "lea_icon.hpp"
#include "lea_menu.hpp"

#include <lua.hpp>
#include <LuaBridge.h>

#include <gtkmm.h>

#include <memory>

class LeaSystemTray : public std::enable_shared_from_this<LeaSystemTray> {
   public:
      LeaSystemTray(const std::shared_ptr<LeaIcon>& icon, lua_State *L);
      virtual ~LeaSystemTray();

      static void registerClass(lua_State *L);

   private:
      static std::shared_ptr<LeaSystemTray> create(
            const std::shared_ptr<LeaIcon>& icon,
            lua_State *L
            );
      void showMenu(
            const std::shared_ptr<LeaMenu>& menu,
            int button,
            lua_State *L
            );

      luabridge::LuaRef _onMousePress;
      luabridge::LuaRef _onMouseRelease;
      luabridge::LuaRef _onMouseScroll;
      luabridge::LuaRef _userdata;

      bool mousePressHandler(GdkEventButton* e);
      bool mouseReleaseHandler(GdkEventButton* e);
      bool mouseScrollHandler(GdkEventScroll* e);

      Glib::RefPtr<Gtk::StatusIcon> _statusIcon;

   private:
      LeaSystemTray(const LeaSystemTray& other);
      const LeaSystemTray& operator=(const LeaSystemTray& other);
};
