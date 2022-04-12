#include "lea_tray.hpp"
#include "lua_host.hpp"
#include "checks.hpp"

#include <lua.hpp>
#include <gtkmm.h>

#include <stdio.h>

static bool button_press(GdkEventButton* e) {
   LOG_FUNCTION;

   printf("button_press: %d\n", e->button);
   return true;
}

static bool button_release(GdkEventButton* e) {
   LOG_FUNCTION;

   printf("button_release: %d\n", e->button);
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
   if (!icon) {
      lua_pushliteral(L, "argument must be an icon");
      lua_error(L);
   }

   auto tray = Gtk::StatusIcon::create(icon);

   LuaSingleton::get().registerObject(tray);

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
   if (!lua_islightuserdata(L, 1)) {
      lua_pushliteral(L, "argument must be a lightuserdata");
      lua_error(L);
   }

   auto tray = Glib::RefPtr<Gtk::StatusIcon>::cast_dynamic(
         LuaSingleton::get().getObject(lua_touserdata(L, 1)));
   if (!tray) {
      lua_pushliteral(L, "argument must be a tray");
      lua_error(L);
   }

   LuaSingleton::get().releaseObject(tray);

   return 0;
}

int lea_tray_setMousePressHandler(lua_State *L) {
   printf("params: %d\n", lua_gettop(L));
   for (int i = 1; i <= lua_gettop(L); ++i) {
      printf("%d: %s\n", i, lua_typename(L, lua_type(L, i)));
   }

   printf("%d\n", lua_type(L, 1));
   printf("%d\n", lua_type(L, 2));
   printf("%d\n", lua_type(L, 3));

   return 0;
   //
   //
   //
   // if (lua_gettop(L) != 1) {
   //    lua_pushliteral(L, "incorrect number of arguments");
   //    lua_error(L);
   // }
   // if (!lua_isstring(L, 1)) {
   //    lua_pushliteral(L, "argument must be a string");
   //    lua_error(L);
   // }
   //
   // auto tray = Glib::RefPtr<Gtk::StatusIcon>::cast_dynamic(
   //       LuaSingleton::get().getObject(lua_touserdata(L, 1)));
   // if (!tray) {
   //    lua_pushliteral(L, "argument must be a tray");
   //    lua_error(L);
   // }
   // tray->signal_button_press_event().connect(sigc::ptr_fun(button_press));
   //
   //
   //
   // m_button1.signal_clicked().connect(
   //       sigc::bind<Glib::ustring>(
   //          sigc::mem_fun(*this, &HelloWorld::on_button_clicked), "button 1") );
   //
   // return 0;
}

int lea_tray_setMouseReleaseHandler(lua_State *L) {
   if (lua_gettop(L) != 1) {
      lua_pushliteral(L, "incorrect number of arguments");
      lua_error(L);
   }
   if (!lua_isstring(L, 1)) {
      lua_pushliteral(L, "argument must be a string");
      lua_error(L);
   }

   auto tray = Glib::RefPtr<Gtk::StatusIcon>::cast_dynamic(
         LuaSingleton::get().getObject(lua_touserdata(L, 1)));
   if (!tray) {
      lua_pushliteral(L, "argument must be a tray");
      lua_error(L);
   }
   tray->signal_button_release_event().connect(sigc::ptr_fun(button_release));

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

   auto tray = Glib::RefPtr<Gtk::StatusIcon>::cast_dynamic(
         LuaSingleton::get().getObject(lua_touserdata(L, 1)));
   if (!tray) {
      lua_pushliteral(L, "argument must be a tray");
      lua_error(L);
   }
   tray->signal_scroll_event().connect(sigc::ptr_fun(scroll));

   return 0;
}

