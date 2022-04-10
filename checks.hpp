#pragma once

#include <lua.hpp>

#include <stdio.h>

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
