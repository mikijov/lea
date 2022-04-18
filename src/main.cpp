/*
    Lea - Lightweight UI for your tools.
    Copyright (C) 2022   Milutin Jovanović

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
