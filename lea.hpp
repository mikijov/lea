#pragma once

#include <lua.hpp>
#include <LuaBridge.h>

#include <memory>

class Lea : public std::enable_shared_from_this<Lea> {
   public:
      static void registerClass(lua_State *L);

      static void log(const std::string& msg);
      static void quit();

      struct VarStorage {
         VarStorage(lua_State *L) :
            onConfigure(L),
            onInit(L),
            onQuit(L)
         {}

         luabridge::LuaRef onConfigure;
         luabridge::LuaRef onInit;
         luabridge::LuaRef onQuit;
      };
      static std::unique_ptr<VarStorage> vars;

   private:
      Lea(const Lea& other);
      const Lea& operator=(const Lea& other);
};
