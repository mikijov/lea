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

#include "lea_timer.hpp"
#include "lea_util.hpp"

#include <LuaBridge.h>

#include <cmath>

LeaTimer::LeaTimer(
      float timeout,
      bool shouldRepeat,
      lua_State *L) :
   _onTimeout(L),
   _userdata(L),
   _shouldRepeat(shouldRepeat)
{
   _timerConnection = Glib::signal_timeout().connect(
         sigc::mem_fun(*this,&LeaTimer::timeoutHandler),
         lround(timeout * 1000));
}

LeaTimer::~LeaTimer() {
   LOG_FUNCTION;

   _timerConnection.disconnect();
}

void LeaTimer::registerClass(lua_State *L) {
   luabridge::getGlobalNamespace(L)
      .beginNamespace("lea")
         .beginClass<LeaTimer>("Timer")
            .addStaticFunction("create", &LeaTimer::create)
            .addFunction("reset", &LeaTimer::reset)
            .addFunction("stop", &LeaTimer::stop)
            .addProperty("onTimeout", &LeaTimer::_onTimeout)
            .addProperty("userdata", &LeaTimer::_userdata)
         .endClass()
      .endNamespace();
}

std::shared_ptr<LeaTimer> LeaTimer::create(
      float timeout,
      bool shouldRepeat,
      lua_State *L
      )
{
   return std::make_shared<LeaTimer>(timeout, shouldRepeat, L);
}

void LeaTimer::reset(
      float timeout,
      bool shouldRepeat,
      lua_State *L
      )
{
   _timerConnection.disconnect();
   _shouldRepeat = shouldRepeat;
   _timerConnection = Glib::signal_timeout().connect(
         sigc::mem_fun(*this,&LeaTimer::timeoutHandler),
         lround(timeout * 1000));
}

void LeaTimer::stop(
      lua_State *L
      )
{
   _timerConnection.disconnect();
}

bool LeaTimer::timeoutHandler() {
   call_callback(_onTimeout, this);
   if (!_shouldRepeat) {
      _timerConnection.disconnect();
   }
   return _shouldRepeat;
}
