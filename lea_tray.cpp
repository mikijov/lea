#include "lea_tray.hpp"
#include "checks.hpp"

#include <LuaBridge.h>

LeaSystemTray::LeaSystemTray(lua_State *L) :
   _onMousePress(L),
   _onMouseRelease(L),
   _onMouseScroll(L),
   _userData(L)
{
   // auto icon = Glib::RefPtr<Gdk::Pixbuf>::cast_dynamic(
   //       LuaSingleton::get().getObject(lua_touserdata(L, 1)));
   // if (!icon) {
   //    lua_pushliteral(L, "argument must be an icon");
   //    lua_error(L);
   // }

   _statusIcon = Gtk::StatusIcon::create(Gtk::Stock::SELECT_COLOR);

   _statusIcon->signal_button_press_event().connect(
         sigc::mem_fun(*this,&LeaSystemTray::mousePressHandler));
   _statusIcon->signal_button_release_event().connect(
         sigc::mem_fun(*this,&LeaSystemTray::mouseReleaseHandler));
   _statusIcon->signal_scroll_event().connect(
         sigc::mem_fun(*this,&LeaSystemTray::mouseScrollHandler));
}

LeaSystemTray::~LeaSystemTray() {
   LOG_FUNCTION;
}

void LeaSystemTray::registerClass(lua_State *L) {
   luabridge::getGlobalNamespace(L)
      .beginNamespace("lea")
         .beginClass<LeaSystemTray>("SystemTray")
            .addStaticFunction("create", &LeaSystemTray::create)
            // .addFunction("test", &LeaSystemTray::test)
            .addProperty("onMousePress", &LeaSystemTray::_onMousePress)
            .addProperty("onMouseRelease", &LeaSystemTray::_onMouseRelease)
            .addProperty("onMouseScroll", &LeaSystemTray::_onMouseScroll)
            .addProperty("userData", &LeaSystemTray::_onMouseScroll)
         .endClass()
      .endNamespace();
}

std::shared_ptr<LeaSystemTray> LeaSystemTray::create(lua_State *L) {
   return std::make_shared<LeaSystemTray>(L);
}

bool LeaSystemTray::mousePressHandler(GdkEventButton* e) {
   callr(_onMousePress);
   return true;
}

bool LeaSystemTray::mouseReleaseHandler(GdkEventButton* e) {
   callr(_onMouseRelease);
   return true;
}

bool LeaSystemTray::mouseScrollHandler(GdkEventScroll* e) {
   callr(_onMouseScroll);
   return true;
}
