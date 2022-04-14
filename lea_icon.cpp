#include "lea_icon.hpp"
#include "checks.hpp"

#include <gtkmm.h>

#include <lua.hpp>

LeaIcon::LeaIcon() {
}

LeaIcon::~LeaIcon() {
   LOG_FUNCTION;
}

void LeaIcon::registerClass(lua_State *L) {
   luabridge::getGlobalNamespace(L)
      .beginNamespace("lea")
         .beginClass<LeaIcon>("Icon")
            .addStaticFunction("load", &LeaIcon::load)
         .endClass()
      .endNamespace();
}

std::shared_ptr<LeaIcon> LeaIcon::load(const char* filename, lua_State *L) {
   auto icon = std::make_shared<LeaIcon>();
   icon->_icon = Gdk::Pixbuf::create_from_file(filename);
   return icon;
}
