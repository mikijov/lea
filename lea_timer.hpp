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

class LeaTimer : public std::enable_shared_from_this<LeaTimer> {
   public:
      LeaTimer(
            float seconds,
            bool shouldRepeat,
            lua_State *L);
      virtual ~LeaTimer();

      static void registerClass(lua_State *L);

   private:
      static std::shared_ptr<LeaTimer> create(
            float timeout,
            bool shouldRepeat,
            lua_State *L
            );
      void reset(
            float timeout,
            bool shouldRepeat,
            lua_State *L
            );
      void stop(
            lua_State *L
            );

      luabridge::LuaRef _onTimeout;
      luabridge::LuaRef _userdata;

      bool timeoutHandler();

      sigc::connection _timerConnection;
      bool _shouldRepeat;

   private:
      LeaTimer(const LeaTimer& other);
      const LeaTimer& operator=(const LeaTimer& other);
};
