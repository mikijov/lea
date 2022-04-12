#include <lua.hpp>
#include <LuaBridge.h>

void log(const std::string& msg) {
   std::cout << msg << std::endl;
}

int main(int argc, char **argv) {
   lua_State *L = luaL_newstate();

   luaL_openlibs(L);
   luabridge::enableExceptions(L);

   {
      // luabridge::LuaRef onInit(L);

      luabridge::getGlobalNamespace(L)
         .beginNamespace("lea")
            .addFunction("log", &log)
            // .addProperty("onInit", &onInit)
         .endNamespace();

      // luaL_dostring(L, ""
      //       "lea.log(\"hello world\")" "\n"
      //       "");
      luaL_dofile(L, "t.lua");

      // if (onInit.isFunction()) {
      //    onInit();
      // }
   }

   lua_gc(L, LUA_GCCOLLECT);
   lua_close(L);

   return 0;
}
