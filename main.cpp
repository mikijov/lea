#include <iostream>

#include <lua.hpp>


int main(int argc, char ** argv) {
   lua_State *L = luaL_newstate();
   luaL_openlibs(L);

   // Our Lua code, it simply prints a Hello, World message
   const char *code = "print('Hello, World!')";

   // here we load the string and use lua_pcall for run the code
   if (luaL_loadstring(L, code) == LUA_OK) {
      if (lua_pcall(L, 0, 0, 0) == LUA_OK) {
         // if it was executed successfuly we remove the code from the stack
         lua_pop(L, lua_gettop(L));
      }
   }

   lua_close(L);
   return 0;
}
