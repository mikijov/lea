#pragma once

#include <lua.hpp>
#include <LuaBridge.h>

#include <gtkmm.h>

#include <memory>

class LeaSystemTray : public std::enable_shared_from_this<LeaSystemTray> {
   public:
      explicit LeaSystemTray(lua_State *L);
      virtual ~LeaSystemTray();

      static void registerClass(lua_State *L);

   private:
      static std::shared_ptr<LeaSystemTray> create(lua_State *L);

      luabridge::LuaRef _onMousePress;
      luabridge::LuaRef _onMouseRelease;
      luabridge::LuaRef _onMouseScroll;
      luabridge::LuaRef _userData;

      bool mousePressHandler(GdkEventButton* e);
      bool mouseReleaseHandler(GdkEventButton* e);
      bool mouseScrollHandler(GdkEventScroll* e);

      Glib::RefPtr<Gtk::StatusIcon> _statusIcon;

   private:
      LeaSystemTray(const LeaSystemTray& other);
      const LeaSystemTray& operator=(const LeaSystemTray& other);
};
