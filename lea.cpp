#include "lea.hpp"
#include "checks.hpp"

#include <LuaBridge.h>
#include <gtkmm.h>

std::unique_ptr<Lea::VarStorage> Lea::vars;

void Lea::log(const std::string& msg) {
   std::cerr << msg << std::endl;
}

void Lea::quit() {
   Gtk::Application::get_default()->quit();
}

void Lea::registerClass(lua_State *L) {
   Lea::vars = std::make_unique<Lea::VarStorage>(L);

   luabridge::getGlobalNamespace(L)
      .beginNamespace("lea")
         .addFunction("log", &Lea::log)
         .addFunction("quit", &Lea::quit)
         .addProperty("onConfigure", &Lea::vars->onConfigure)
         .addProperty("onInit", &Lea::vars->onInit)
         .addProperty("onQuit", &Lea::vars->onQuit)
      .endNamespace();
}
