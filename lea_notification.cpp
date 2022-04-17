/*
    Lea - Lightweight UI for your tools.
    Copyright (C) 2022   Milutin Jovanović

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "lea_notification.hpp"
#include "lea_icon.hpp"
#include "lea_util.hpp"

#include <LuaBridge.h>

#include <gtkmm.h>

LeaNotification::LeaNotification(
      const std::string& title,
      const std::string& body,
      lua_State *L) :
   _title(title),
   _body(body),
   _icon(L),
   _onClick(L),
   _userdata(L)
{
}

LeaNotification::~LeaNotification() {
   LOG_FUNCTION;
}

void LeaNotification::registerClass(lua_State *L) {
   luabridge::getGlobalNamespace(L)
      .beginNamespace("lea")
         .beginClass<LeaNotification>("Notification")
            .addStaticFunction("create", &LeaNotification::create)
            .addFunction("show", &LeaNotification::show)
            .addProperty("icon", &LeaNotification::_icon)
            .addProperty("onClick", &LeaNotification::_onClick)
            .addProperty("userdata", &LeaNotification::_userdata)
         .endClass()
      .endNamespace();
}

std::shared_ptr<LeaNotification> LeaNotification::create(
      const std::string& title,
      const std::string& body,
      lua_State *L)
{
   return std::make_shared<LeaNotification>(title, body, L);
}

Glib::RefPtr<Gio::SimpleAction> act;

void LeaNotification::show() {
   static int id = 0;

   auto notification = Gio::Notification::create(_title);
   notification->set_body(_body);
   if (_icon.isValid()) {
      const std::shared_ptr<LeaIcon> icon = _icon;
      notification->set_icon(icon->_icon);
   }
   if (_onClick.isCallable()) {
      char sname[256];
      sprintf(sname, "notification-%d", ++id);
      char nname[256];
      sprintf(nname, "app.%s", sname);

      act = Gtk::Application::get_default()->add_action(sname);
      act->signal_activate().connect(
         sigc::mem_fun(*this,&LeaNotification::clickHandler));

      notification->add_button("Activate", nname);
   }
   Gtk::Application::get_default()->send_notification(notification);
}

void LeaNotification::clickHandler(const Glib::VariantBase& /*v*/) {
   call_callback(_onClick, this);
}
