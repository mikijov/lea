#include "lea_tray.hpp"
#include "checks.hpp"

#include <LuaBridge.h>

LeaSystemTray::LeaSystemTray(const std::shared_ptr<LeaIcon>& icon, lua_State *L) :
   _onMousePress(L),
   _onMouseRelease(L),
   _onMouseScroll(L),
   _userData(L)
{
   _statusIcon = Gtk::StatusIcon::create(icon->_icon);

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
            .addProperty("onMousePress", &LeaSystemTray::_onMousePress)
            .addProperty("onMouseRelease", &LeaSystemTray::_onMouseRelease)
            .addProperty("onMouseScroll", &LeaSystemTray::_onMouseScroll)
            .addProperty("userData", &LeaSystemTray::_onMouseScroll)
         .endClass()
      .endNamespace();
}

std::shared_ptr<LeaSystemTray> LeaSystemTray::create(
      const std::shared_ptr<LeaIcon>& icon,
      lua_State *L
      )
{
   return std::make_shared<LeaSystemTray>(icon, L);
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
