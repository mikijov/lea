#include "lua_host.hpp"

#include <lua.hpp>

class CheckForMemoryLeaks {
   public:
      CheckForMemoryLeaks(lua_State* L) :
         _L(L)
      {
         top = lua_gettop(_L);
      }

      ~CheckForMemoryLeaks() {
         int newTop = lua_gettop(_L);
         if (newTop != top) {
            printf("stack changed %d->%d (%d)\n", top, newTop, newTop - top);
         }
      }
   private:
      lua_State *_L;
      int top;
   private:
      CheckForMemoryLeaks(const CheckForMemoryLeaks&);
      const CheckForMemoryLeaks& operator=(const CheckForMemoryLeaks&);
};

static int lea_log(lua_State *L) {
   if (lua_gettop(L) != 1) {
      lua_pushliteral(L, "incorrect number of arguments");
      lua_error(L);
   }
   if (!lua_isstring(L, 1)) {
      lua_pushliteral(L, "argument must be a string");
      lua_error(L);
   }
   printf("%s\n", lua_tostring(L, 1));
   return 0;
}

static int lea_quit(lua_State *L) {
   if (lua_gettop(L) != 0) {
      lua_pushliteral(L, "incorrect number of arguments");
      lua_error(L);
   }
   // quit = true;
   return 0;
}

LuaHost::LuaHost() {
   L = luaL_newstate();
   luaL_openlibs(L);

   lua_newtable(L);
   lua_pushcfunction(L, lea_log); lua_setfield(L, -2, "log");
   lua_pushcfunction(L, lea_quit); lua_setfield(L, -2, "quit");
   lua_setglobal(L, "lea");
}

LuaHost::~LuaHost() {
   lua_close(L);
}

void LuaHost::load_script(const char* filename) {
   if (luaL_loadfile(L, filename) != LUA_OK) {
      throw LuaHostException("failed to load script file");
   }
   if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
      throw LuaHostException("failed to run lua script");
   }
}

void LuaHost::getObject(const char* name) {
   int type = lua_getglobal(L, name);
   if (type == LUA_TNONE) {
      lua_pop(L, 1);
      return;
   }
   if (type != LUA_TTABLE) {
      lua_pop(L, 1);
      throw LuaHostException("requested name is not an object");
   }
}

void LuaHost::getMethod(const char *name) {
   int type = lua_getfield(L, -1, name);
   if (type == LUA_TNONE) {
      lua_pop(L, 1);
      return;
   }
   if (type != LUA_TFUNCTION) {
      lua_pop(L, 1);
      throw LuaHostException("requested field is not a function");
   }
}

void LuaHost::onConfigure() {
   CheckForMemoryLeaks c(L);

   getObject("lea");
   getMethod("onConfigure");

   if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
      lua_pop(L, 1);
      throw LuaHostException(lua_tostring(L, -1));
   }
   lua_pop(L, 1);
}

void LuaHost::onInit() {
   CheckForMemoryLeaks c(L);

   getObject("lea");
   getMethod("onInit");

   if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
      lua_pop(L, 1);
      throw LuaHostException(lua_tostring(L, -1));
   }
   lua_pop(L, 1);
}

void LuaHost::onQuit() {
   CheckForMemoryLeaks c(L);

   getObject("lea");
   getMethod("onQuit");

   if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
      lua_pop(L, 1);
      throw LuaHostException(lua_tostring(L, -1));
   }
   lua_pop(L, 1);
}
