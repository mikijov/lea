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

class LeaIcon : public std::enable_shared_from_this<LeaIcon> {
   public:
      LeaIcon();
      virtual ~LeaIcon();

      static void registerClass(lua_State *L);

      static std::shared_ptr<LeaIcon> load(const char* filename, lua_State *L);

      Glib::RefPtr<Gdk::Pixbuf> _icon;

   private:
      LeaIcon(const LeaIcon& other);
      const LeaIcon& operator=(const LeaIcon& other);
};
