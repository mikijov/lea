#pragma once

#include <stdexcept>

struct lua_State;

struct LuaHostException : public std::runtime_error {
   public:
      LuaHostException(const char* msg) : runtime_error(msg) {}
};

class LuaHost {
   public:
      LuaHost();
      ~LuaHost();

      void load_script(const char* filename);
      void getObject(const char* name);
      void getMethod(const char *name);

      void onConfigure();
      void onInit();
      void onQuit();

   private:
      lua_State *L;

   private:
      LuaHost(const LuaHost&);
      const LuaHost& operator=(const LuaHost&);
};



