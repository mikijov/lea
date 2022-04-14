#pragma once

#include <lua.hpp>
#include <LuaBridge.h>

#include <gtkmm.h>

#include <memory>

class LeaIcon : public std::enable_shared_from_this<LeaIcon> {
   public:
      LeaIcon();
      virtual ~LeaIcon();

      static void registerClass(lua_State *L);

      static std::shared_ptr<LeaIcon> load(const char* filename, lua_State *L);

      Glib::RefPtr<Gdk::Pixbuf> _icon;

   private:
      LeaIcon(const LeaIcon& other);
      const LeaIcon& operator=(const LeaIcon& other);
};
