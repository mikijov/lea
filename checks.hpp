#pragma once

#include <lua.hpp>
#include <LuaBridge.h>

#include <stdio.h>
#include <stdexcept>

class CheckForMemoryLeaks {
   public:
      CheckForMemoryLeaks(lua_State* L) :
         _L(L)
      {
         top = lua_gettop(_L);
      }

      ~CheckForMemoryLeaks() {
         int newTop = lua_gettop(_L);
         if (newTop != top) {
            printf("stack changed %d->%d (%d)\n", top, newTop, newTop - top);
         }
      }
   private:
      lua_State *_L;
      int top;
   private:
      CheckForMemoryLeaks(const CheckForMemoryLeaks&);
      const CheckForMemoryLeaks& operator=(const CheckForMemoryLeaks&);
};


#define LOG_FUNCTION printf("%s\n", __FUNCTION__);

template<class... Args>
void callr(const luabridge::LuaRef& fn, Args&&... args) {
   if ( fn.isCallable() ) {
      try {
         fn(std::forward<Args>(args)...);
      } catch (const luabridge::LuaException& e) {
         std::cerr << "Lua EXCEPTION: " << e.what() << std::endl;
      } catch (const std::exception& e) {
         std::cerr << "EXCEPTION: " << e.what() << std::endl;
      }
   } else {
      std::cerr << fn << " is not callable.";
   }
}

