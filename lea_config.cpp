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

#include "lea_config.hpp"
#include "lea_util.hpp"

#include <LuaBridge.h>

LeaConfig::LeaConfig(lua_State *L) :
   _appName(L)
{
}

LeaConfig::~LeaConfig() {
   LOG_FUNCTION;
}

void LeaConfig::registerClass(lua_State *L) {
   luabridge::getGlobalNamespace(L)
      .beginNamespace("lea")
         .beginClass<LeaConfig>("Config")
            .addProperty("appName", &LeaConfig::_appName)
         .endClass()
      .endNamespace();
}
