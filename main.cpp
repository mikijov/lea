#include "lea.hpp"

#include <lua.hpp>
#include <LuaBridge.h>
#include <gtkmm.h>

#include <iostream>

int main(int argc, char **argv) {
   Gtk::Main kit(argc, argv);

   lua_State *L = luaL_newstate();

   luaL_openlibs(L);

   luabridge::enableExceptions(L);

   Lea::registerClass(L);

   // luaL_dostring(L, ""
   //       "lea.log(\"hello world\")" "\n"
   //       "lea.quit()" "\n"
   //       "lea.log(tunguzija)" "\n"
   //       "");
   luaL_dofile(L, "../main.lua");

   if (Lea::vars->onConfigure.isCallable()) {
      Lea::vars->onConfigure();
   }

   if (Lea::vars->onInit.isCallable()) {
      Lea::vars->onInit();
   }

   if (Lea::vars->onQuit.isCallable()) {
      Lea::vars->onQuit();
   }

   Lea::vars.release();

   Gtk::Main::run();

   lua_close(L);

   return 0;
}
