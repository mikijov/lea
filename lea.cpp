#include "lea.hpp"

#include <lua.hpp>

int lea_log(lua_State *L) {
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

int lea_quit(lua_State *L) {
   if (lua_gettop(L) != 0) {
      lua_pushliteral(L, "incorrect number of arguments");
      lua_error(L);
   }
   // quit = true;
   return 0;
}
