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

#include "lea_icon.hpp"
#include "lea_util.hpp"

#include <gtkmm.h>

#include <lua.hpp>

LeaIcon::LeaIcon() {
}

LeaIcon::~LeaIcon() {
   LOG_FUNCTION;
}

void LeaIcon::registerClass(lua_State *L) {
   luabridge::getGlobalNamespace(L)
      .beginNamespace("lea")
         .beginClass<LeaIcon>("Icon")
            .addStaticFunction("load", &LeaIcon::load)
         .endClass()
      .endNamespace();
}

std::shared_ptr<LeaIcon> LeaIcon::load(const char* filename, lua_State *L) {
   auto icon = std::make_shared<LeaIcon>();
   icon->_icon = Gdk::Pixbuf::create_from_file(filename);
   return icon;
}
