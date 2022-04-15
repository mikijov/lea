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
