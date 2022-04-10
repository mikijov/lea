#pragma once

#include <stdexcept>
#include <map>

#include <gtkmm.h>

struct lua_State;

struct LuaHostException : public std::runtime_error {
   public:
      LuaHostException(const char* msg) : runtime_error(msg) {}
};

class LuaHost {
   public:
      LuaHost();
      ~LuaHost();

      void load_script(const char* filename);
      void getObject(const char* name);
      void getMethod(const char *name);

      void onConfigure();
      void onInit();
      void onQuit();

      void registerObject(const Glib::RefPtr<Glib::Object>& o) {
         managed_objects[reinterpret_cast<uintptr_t>(o.get())] = o;
      }

      void releaseObject(const Glib::RefPtr<Glib::Object>& o) {
         managed_objects.erase(reinterpret_cast<uintptr_t>(o.get()));
      }

      const Glib::RefPtr<Glib::Object>& getObject(uintptr_t o) {
         return managed_objects[o];
      }

      const Glib::RefPtr<Glib::Object>& getObject(void* o) {
         return getObject(reinterpret_cast<uintptr_t>(o));
      }

   private:
      lua_State *L;
      std::map<uintptr_t,Glib::RefPtr<Glib::Object> > managed_objects;

   private:
      LuaHost(const LuaHost&);
      const LuaHost& operator=(const LuaHost&);
};

class LuaSingleton {
   public:
      static void create();
      static void destroy();

      static LuaHost& get();

   private:
      static LuaHost *_singleton;

   private:
      LuaSingleton();
};

