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

LuaHost::LuaHost() {
   L = luaL_newstate();
   luaL_openlibs(L);

   {
      CheckForMemoryLeaks check(L);

      lua_newtable(L);
      lua_pushcfunction(L, lea_log); lua_setfield(L, -2, "log");
      lua_pushcfunction(L, lea_quit); lua_setfield(L, -2, "quit");

      {
         CheckForMemoryLeaks check(L);

         lua_newtable(L);
         lua_pushcfunction(L, lea_tray_create); lua_setfield(L, -2, "create");
         lua_pushcfunction(L, lea_tray_destroy); lua_setfield(L, -2, "destroy");
         lua_pushcfunction(L, lea_tray_setClickHandler); lua_setfield(L, -2, "setClickHandler");
         lua_pushcfunction(L, lea_tray_setScrollHandler); lua_setfield(L, -2, "setScrollHandler");
         lua_setfield(L, -2, "tray");
      }

      {
         CheckForMemoryLeaks check(L);

         lua_newtable(L);
         lua_pushcfunction(L, lea_icon_load); lua_setfield(L, -2, "load");
         lua_setfield(L, -2, "icon");
      }

      {
         CheckForMemoryLeaks check(L);

         lua_newtable(L);
         lua_pushcfunction(L, lea_timer_create); lua_setfield(L, -2, "create");
         lua_pushcfunction(L, lea_timer_destroy); lua_setfield(L, -2, "destroy");
         lua_pushcfunction(L, lea_timer_resetTimeout); lua_setfield(L, -2, "resetTimeout");
         lua_setfield(L, -2, "timer");
      }

      {
         CheckForMemoryLeaks check(L);

         lua_newtable(L);
         lua_pushcfunction(L, lea_menu_create); lua_setfield(L, -2, "create");
         lua_pushcfunction(L, lea_menu_addSubMenu); lua_setfield(L, -2, "addSubMenu");
         lua_pushcfunction(L, lea_menu_addItem); lua_setfield(L, -2, "addItem");
         lua_pushcfunction(L, lea_menu_addSeparator); lua_setfield(L, -2, "addSeparator");
         lua_setfield(L, -2, "menu");
      }

      {
         CheckForMemoryLeaks check(L);

         lua_newtable(L);
         lua_pushcfunction(L, lea_notification_create); lua_setfield(L, -2, "show");
         lua_pushcfunction(L, lea_notification_setClickHandler); lua_setfield(L, -2, "setClickHandler");
         lua_pushcfunction(L, lea_notification_setTimeout); lua_setfield(L, -2, "setTimeout");
         lua_setfield(L, -2, "notification");
      }

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
