#include "lea.hpp"

#include <LuaBridge.h>

std::unique_ptr<Lea::VarStorage> Lea::vars;

void Lea::log(const std::string& msg) {
   std::cerr << msg << std::endl;
}

void Lea::quit() {
   log("quit");
}

void Lea::registerClass(lua_State *L) {
   Lea::vars = std::make_unique<Lea::VarStorage>(L);

   luabridge::getGlobalNamespace(L)
      .beginNamespace("lea")
         .addFunction("log", &Lea::log)
         .addFunction("quit", &Lea::quit)
         .addProperty("onConfig", &Lea::vars->onConfig)
         .addProperty("onInit", &Lea::vars->onInit)
         .addProperty("onQuit", &Lea::vars->onQuit)
      .endNamespace();
}
