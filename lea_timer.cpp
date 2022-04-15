#include "lea_timer.hpp"
#include "checks.hpp"

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
   callr(_onTimeout, this);
   if (!_shouldRepeat) {
      _timerConnection.disconnect();
   }
   return _shouldRepeat;
}
