#include "lea_icon.hpp"
#include "lua_host.hpp"
#include "checks.hpp"

#include <gtkmm.h>

#include <lua.hpp>

int lea_icon_load(lua_State *L) {
   LOG_FUNCTION;

   if (lua_gettop(L) != 1) {
      lua_pushliteral(L, "incorrect number of arguments");
      lua_error(L);
   }
   if (!lua_isstring(L, 1)) {
      lua_pushliteral(L, "argument must be a string");
      lua_error(L);
   }

   auto icon = Gdk::Pixbuf::create_from_file(lua_tostring(L, 1));
   LuaSingleton::get().registerObject(icon);

   lua_pushlightuserdata(L, icon.get());

   return 1;
}


