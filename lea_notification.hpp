#pragma once

#include <lua.hpp>
#include <LuaBridge.h>

#include <gtkmm.h>

#include <memory>

class LeaNotification : public std::enable_shared_from_this<LeaNotification> {
   public:
      LeaNotification(
            const std::string& title,
            const std::string& body,
            lua_State *L);
      virtual ~LeaNotification();

      static void registerClass(lua_State *L);

      static std::shared_ptr<LeaNotification> create(
            const std::string& title,
            const std::string& body,
            lua_State *L);
      void show();

      std::string _title;
      std::string _body;
      luabridge::LuaRef _icon;
      luabridge::LuaRef _onClick;
      luabridge::LuaRef _userdata;

      void clickHandler(const Glib::VariantBase& v);

   private:
      LeaNotification(const LeaNotification& other);
      const LeaNotification& operator=(const LeaNotification& other);
};
