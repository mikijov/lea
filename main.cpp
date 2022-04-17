#include "lea.hpp"
#include "lea_config.hpp"
#include "lea_icon.hpp"
#include "lea_tray.hpp"
#include "lea_notification.hpp"
#include "lea_timer.hpp"
#include "lea_menu.hpp"
#include "lea_util.hpp"

#include <lua.hpp>
#include <LuaBridge.h>
#include <gtkmm.h>

#include <iostream>

int main(int argc, char **argv) {
   lua_State *L = luaL_newstate();
   luabridge::enableExceptions(L);
   luaL_openlibs(L);

   Lea::registerClass(L);
   LeaConfig::registerClass(L);
   LeaIcon::registerClass(L);
   LeaSystemTray::registerClass(L);
   LeaNotification::registerClass(L);
   LeaTimer::registerClass(L);
   LeaMenu::registerClass(L);

   if (luaL_dofile(L, "../main.lua") != LUA_OK) {
      std::cerr << "Failed to run main.lua." << std::endl;
      return 1;
   }

   auto config = std::make_shared<LeaConfig>(L);
   config->_appName = "xyz.haker.lea";

   call_callback(Lea::vars->onConfigure, *config);

   auto app = Gtk::Application::create(argc, argv, config->_appName.tostring());
   app->hold();

   call_callback(Lea::vars->onInit);

   app->run();

   call_callback(Lea::vars->onQuit);

   Lea::vars.release();

   lua_close(L);

   return 0;
}
