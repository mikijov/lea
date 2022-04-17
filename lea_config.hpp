#pragma once

#include <lua.hpp>
#include <LuaBridge.h>

class LeaConfig : public std::enable_shared_from_this<LeaConfig> {
   public:
      LeaConfig(lua_State *L);
      virtual ~LeaConfig();

      static void registerClass(lua_State *L);

      luabridge::LuaRef _appName;

   private:
      LeaConfig(const LeaConfig& other);
      const LeaConfig& operator=(const LeaConfig& other);
};
