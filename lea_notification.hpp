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

class LeaNotification : public std::enable_shared_from_this<LeaNotification> {
   public:
      LeaNotification(
            const std::string& title,
            const std::string& body,
            lua_State *L);
      virtual ~LeaNotification();

      static void registerClass(lua_State *L);

      static std::shared_ptr<LeaNotification> create(
            const std::string& title,
            const std::string& body,
            lua_State *L);
      void show();

      std::string _title;
      std::string _body;
      luabridge::LuaRef _icon;
      luabridge::LuaRef _onClick;
      luabridge::LuaRef _userdata;

      void clickHandler(const Glib::VariantBase& v);

   private:
      LeaNotification(const LeaNotification& other);
      const LeaNotification& operator=(const LeaNotification& other);
};
