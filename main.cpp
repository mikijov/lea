// #include "lua_host.hpp"

#include "lea.hpp"

#include <lua.hpp>

#include <iostream>

#include <LuaBridge.h>

// #include <gtkmm.h>

// #include <iostream>
// #include <vector>

// void llog(const std::string& msg) {
//    std::cout << msg << std::endl;
// }
//
int main(int argc, char **argv) {
   // Gtk::Main kit(argc, argv);

   lua_State *L = luaL_newstate();
   printf("1\n");

   luaL_openlibs(L);
   printf("2\n");

   luabridge::enableExceptions(L);
   printf("3\n");

   {
      // luabridge::LuaRef onConfig(L);
      // luabridge::LuaRef onInit(L);
      // luabridge::LuaRef onQuit(L);

      Lea::registerClass(L);
      // luabridge::getGlobalNamespace(L)
      //    .beginNamespace("lea")
      //       .addFunction("log", &Lea::log)
      //       // .addFunction("llog", &llog)
      //       // .addFunction("quit", &Lea::quit)
      //       // .addProperty("onConfig", &onConfig)
      //       // .addProperty("onInit", &onInit)
      //       // .addProperty("onQuit", &onQuit)
      //    .endNamespace();
      printf("4\n");

      luaL_dostring(L, ""
            "lea.log(\"hello world\")" "\n"
            "lea.quit()" "\n"
            "lea.log(tunguzija)" "\n"
            "");
      // luaL_dofile(L, "../test.lua");
      printf("5\n");

      // Gtk::Main::run();
      printf("6\n");
   }

   lua_close(L);
   printf("7\n");

   return 0;
}
