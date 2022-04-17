#include "lea_config.hpp"
#include "lea_util.hpp"

#include <LuaBridge.h>

LeaConfig::LeaConfig(lua_State *L) :
   _appName(L)
{
}

LeaConfig::~LeaConfig() {
   LOG_FUNCTION;
}

void LeaConfig::registerClass(lua_State *L) {
   luabridge::getGlobalNamespace(L)
      .beginNamespace("lea")
         .beginClass<LeaConfig>("Config")
            .addProperty("appName", &LeaConfig::_appName)
         .endClass()
      .endNamespace();
}
