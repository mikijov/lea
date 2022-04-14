#include "lea.hpp"
#include "lea_icon.hpp"
#include "lea_tray.hpp"
#include "lea_notification.hpp"
#include "checks.hpp"

#include <lua.hpp>
#include <LuaBridge.h>
#include <gtkmm.h>

#include <iostream>

int main(int argc, char **argv) {
   auto app = Gtk::Application::create(argc, argv, "xyz.haker.lea");
   app->hold();

   lua_State *L = luaL_newstate();
   luabridge::enableExceptions(L);
   luaL_openlibs(L);

   Lea::registerClass(L);
   LeaIcon::registerClass(L);
   LeaSystemTray::registerClass(L);
   LeaNotification::registerClass(L);

   if (luaL_dofile(L, "../main.lua") != LUA_OK) {
      std::cerr << "Failed to run main.lua." << std::endl;
      return 1;
   }

   callr(Lea::vars->onConfigure);
   callr(Lea::vars->onInit);

   app->run();

   callr(Lea::vars->onQuit);

   Lea::vars.release();

   lua_close(L);

   return 0;
}
