#include "lea_tray.hpp"
#include "lua_host.hpp"
#include "checks.hpp"

#include <lua.hpp>
#include <gtkmm.h>

#include <stdio.h>

static void activate() {
   printf("activated\n");
}

static bool button_press(GdkEventButton* e) {
   LOG_FUNCTION;

   printf("button_press: %d at %dx%d\n", e->button);
   return true;
}

static bool button_release(GdkEventButton* e) {
   LOG_FUNCTION;

   printf("button_release: %d at %dx%d\n", e->button);
   return true;
}

static bool scroll(GdkEventScroll* e) {
   LOG_FUNCTION;

   printf("scroll\n");
   return true;
}

static bool query_tooltip() {
   LOG_FUNCTION;

   printf("query_tooltip\n");
   return true;
}

int lea_tray_create(lua_State *L) {
   LOG_FUNCTION;

   if (lua_gettop(L) != 1) {
      lua_pushliteral(L, "incorrect number of arguments");
      lua_error(L);
   }
   if (!lua_islightuserdata(L, 1)) {
      lua_pushliteral(L, "argument must be a lightuserdata");
      lua_error(L);
   }

   auto icon = Glib::RefPtr<Gdk::Pixbuf>::cast_dynamic(
         LuaSingleton::get().getObject(lua_touserdata(L, 1)));

   // Gdk::Pixbuf *icon = dynamic_cast<Gdk::Pixbuf>(object);
   //
   // if (icon == NULL) {
   //    lua_pushliteral(L, "argument must be an icon");
   //    lua_error(L);
   // }

   auto tray = Gtk::StatusIcon::create(icon);
   LuaSingleton::get().registerObject(tray);

   tray->signal_activate().connect(sigc::ptr_fun(activate));
   tray->signal_button_press_event().connect(sigc::ptr_fun(button_press));
   tray->signal_button_release_event().connect(sigc::ptr_fun(button_release));
   tray->signal_scroll_event().connect(sigc::ptr_fun(scroll));
   // tray->signal_query_tooltip().connect(sigc::ptr_fun());

   lua_pushlightuserdata(L, tray.get());

   return 1;
}

int lea_tray_destroy(lua_State *L) {
   LOG_FUNCTION;

   if (lua_gettop(L) != 1) {
      lua_pushliteral(L, "incorrect number of arguments");
      lua_error(L);
   }
   if (!lua_isstring(L, 1)) {
      lua_pushliteral(L, "argument must be a string");
      lua_error(L);
   }

   return 0;
}

int lea_tray_setClickHandler(lua_State *L) {
   if (lua_gettop(L) != 1) {
      lua_pushliteral(L, "incorrect number of arguments");
      lua_error(L);
   }
   if (!lua_isstring(L, 1)) {
      lua_pushliteral(L, "argument must be a string");
      lua_error(L);
   }
   return 0;
}

int lea_tray_setScrollHandler(lua_State *L) {
   if (lua_gettop(L) != 1) {
      lua_pushliteral(L, "incorrect number of arguments");
      lua_error(L);
   }
   if (!lua_isstring(L, 1)) {
      lua_pushliteral(L, "argument must be a string");
      lua_error(L);
   }
   return 0;
}

