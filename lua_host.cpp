#include "lua_host.hpp"
#include "checks.hpp"

#include "lea.hpp"
#include "lea_icon.hpp"
#include "lea_tray.hpp"
#include "lea_timer.hpp"
#include "lea_menu.hpp"
#include "lea_notification.hpp"

#include <lua.hpp>

#include <assert.h>

#define LEA "lea"

static const luaL_Reg LEA_METHODS[] = {
   { "log", lea_log },
   { "quit", lea_quit },
   { "loadIcon", lea_icon_load },
   { "createTimer", lea_timer_create },
   { "createMenu", lea_menu_create },
   { "createNotification", lea_notification_create },
   { "createTrayIcon", lea_tray_create }
};

static const luaL_Reg LEA_METATABLE[] = {
   // { "__gc", lea_gc },
};

#define LEA_ICON "lea.icon"

static const luaL_Reg LEA_ICON_METHODS[] = {
   { "load", lea_icon_load },
};

static const luaL_Reg LEA_ICON_METATABLE[] = {
   // { "__gc", lea_gc },
};

#define LEA "lea.tray"

static const luaL_Reg LEA_TRAY_METHODS[] = {
   { "new", lea_tray_new },
   { "setMousePressHandler", lea_tray_setMousePressHandler },
   { "setMouseReleaseHandler", lea_tray_setMouseReleaseHandler },
   { "setMouseScrollHandler", lea_tray_setMouseScrollHandler }
};

static const luaL_Reg LEA_TRAY_METATABLE[] = {
   { "__gc", lea_tray_gc }
};



LuaHost::LuaHost() {
   L = luaL_newstate();

   luaL_openlibs(L);

   {
      CheckForMemoryLeaks check(L);

      luaL_newlib(L, LEA_METHODS);
      luaL_newlib(L, LEA_METHODS);

      lua_setglobal(L, "lea");
   }

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

//          oo                   dP            dP
//                               88            88
// .d8888b. dP 88d888b. .d8888b. 88 .d8888b. d8888P .d8888b. 88d888b.
// Y8ooooo. 88 88'  `88 88'  `88 88 88ooood8   88   88'  `88 88'  `88
//       88 88 88    88 88.  .88 88 88.  ...   88   88.  .88 88    88
// `88888P' dP dP    dP `8888P88 dP `88888P'   dP   `88888P' dP    dP
//                           .88
//                       d8888P

LuaHost *LuaSingleton::_singleton = NULL;

void LuaSingleton::create() {
   assert(LuaSingleton::_singleton == NULL);

   LuaSingleton::_singleton = new LuaHost();
}

void LuaSingleton::destroy() {
   assert(LuaSingleton::_singleton != NULL);

   delete LuaSingleton::_singleton;
   LuaSingleton::_singleton = NULL;
}

LuaHost& LuaSingleton::get() {
   return *LuaSingleton::_singleton;
}
