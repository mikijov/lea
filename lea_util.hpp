#pragma once

#include <lua.hpp>
#include <LuaBridge.h>

#include <stdio.h>
#include <stdexcept>

#define LOG_FUNCTION printf("%s\n", __FUNCTION__);

template<class... Args>
void call_callback(const luabridge::LuaRef& fn, Args&&... args) {
   if ( fn.isCallable() ) {
      try {
         fn(std::forward<Args>(args)...);
      } catch (const luabridge::LuaException& e) {
         std::cerr << "Lua EXCEPTION: " << e.what() << std::endl;
      } catch (const std::exception& e) {
         std::cerr << "EXCEPTION: " << e.what() << std::endl;
      }
   } else {
      std::cerr << fn << " is not callable." << std::endl;
   }
}

