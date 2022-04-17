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

#include <stdio.h>
#include <stdexcept>

#define LOG_FUNCTION printf("%s\n", __FUNCTION__);

template<class... Args>
void call_callback(const luabridge::LuaRef& fn, Args&&... args) {
   if ( fn.isCallable() ) {
      try {
         fn(std::forward<Args>(args)...);
      } catch (const luabridge::LuaException& e) {
         std::cerr << "Lua EXCEPTION: " << e.what() << std::endl;
      } catch (const std::exception& e) {
         std::cerr << "EXCEPTION: " << e.what() << std::endl;
      }
   } else {
      std::cerr << fn << " is not callable." << std::endl;
   }
}

