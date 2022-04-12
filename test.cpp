#include <lua.hpp>
#include "checks.hpp"

#include <stdio.h>
#include <assert.h>
#include <stdexcept>

#include <LuaBridge.h>

// dP
// 88
// 88 .d8888b. .d8888b.
// 88 88ooood8 88'  `88
// 88 88.  ... 88.  .88
// dP `88888P' `88888P8

#define LEA "lea"

static int lea_log(lua_State *L) {
   if (lua_gettop(L) != 1) {
      lua_pushliteral(L, "incorrect number of arguments");
      lua_error(L);
   }
   if (!lua_isstring(L, 1)) {
      lua_pushliteral(L, "argument must be a string");
      lua_error(L);
   }
   printf("%s\n", lua_tostring(L, 1));
   return 0;
}

static int lea_quit(lua_State *L) {
   if (lua_gettop(L) != 0) {
      lua_pushliteral(L, "incorrect number of arguments");
      lua_error(L);
   }
   // quit = true;
   return 0;
}

static const luaL_Reg LEA_METHODS[] = {
   { "log", lea_log },
   { "quit", lea_quit }
};

static const luaL_Reg LEA_METATABLE[] = {
   // { "__gc", lea_gc },
};

//   dP
//   88
// d8888P 88d888b. .d8888b. dP    dP
//   88   88'  `88 88'  `88 88    88
//   88   88       88.  .88 88.  .88
//   dP   dP       `88888P8 `8888P88
//                               .88
//                           d8888P

#define LEA_TRAY "lea.tray"

static int lea_tray_new(lua_State *L) {
   if (lua_gettop(L) != 0) {
      lua_pushliteral(L, "incorrect number of arguments");
      lua_error(L);
   }
   // quit = true;
   return 0;
}

static int lea_tray_gc(lua_State *L) {
   if (lua_gettop(L) != 0) {
      lua_pushliteral(L, "incorrect number of arguments");
      lua_error(L);
   }
   // quit = true;
   return 0;
}

static const luaL_Reg LEA_TRAY_METHODS[] = {
   { "new", lea_tray_new },
   { "onClick", NULL }
};

static const luaL_Reg LEA_TRAY_METATABLE[] = {
   { "__gc", lea_tray_gc }
};

//                     oo
//
// 88d8b.d8b. .d8888b. dP 88d888b.
// 88'`88'`88 88'  `88 88 88'  `88
// 88  88  88 88.  .88 88 88    88
// dP  dP  dP `88888P8 dP dP    dP

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

   private:
      lua_State *L;

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

class TestObject {
   public:
      explicit TestObject(const std::string& msg, lua_State* L) :
         _msg(msg),
         _callback(L)
      {
         std::cout << "create: " << _msg << std::endl;
      }

      ~TestObject() {
         std::cout << "destroy: " << _msg << std::endl;
      }

      void reset() {
         _msg = "<default>";
      }

      static TestObject* create(const std::string& msg, lua_State* L) {
         return new TestObject(msg, L);
      }

      static void registerClass(lua_State *L) {
         luabridge::getGlobalNamespace (L)
            .beginNamespace ("lea")
               .beginClass <TestObject> ("TestObject")
                  .addStaticFunction ("create", &TestObject::create)
                  .addProperty ("message", &TestObject::_msg)
                  .addProperty ("callback", &TestObject::_callback)
                  .addFunction ("reset", &TestObject::reset)
               .endClass ()
            .endNamespace ();
      }

   private:
      std::string _msg;
      luabridge::LuaRef _callback;

   private:
      TestObject();
      TestObject(const TestObject& other);
      const TestObject& operator=(const TestObject& other);
};

void llog(const std::string& msg) {
   std::cout << msg << std::endl;
}

int main(int argc, char **argv) {
   lua_State *L = luaL_newstate();

   llog("1");

   luaL_openlibs(L);
   llog("2");

   luabridge::enableExceptions(L);
   llog("3");

   luabridge::LuaRef onConfig(L);
   luabridge::LuaRef onInit(L);
   luabridge::LuaRef onQuit(L);

   luabridge::getGlobalNamespace(L)
      .beginNamespace("lea")
         .addFunction("log", &llog)
         .addProperty("onConfig", &onConfig)
         .addProperty("onInit", &onInit)
         .addProperty("onQuit", &onQuit)
      .endNamespace();
   llog("4");
   TestObject::registerClass(L);
   llog("5");

   luaL_dofile(L, "../test.lua");
   llog("6");

   if (onConfig.isFunction()) {
      onConfig();
   }
   llog("7");
   if (onInit.isFunction()) {
      onInit();
   }
   llog("8");
   lua_gc(L, LUA_GCCOLLECT);

   // LuaSingleton::create();
   //
   // LuaSingleton::get().load_script("../main.lua");
   // LuaSingleton::get().onConfigure();
   // LuaSingleton::get().onInit();
   //
   // LuaSingleton::destroy();

   return 0;
}

// dP
// 88
// 88 dP    dP .d8888b.
// 88 88    88 88'  `88
// 88 88.  .88 88.  .88
// dP `88888P' `88888P8

LuaHost::LuaHost() {
   L = luaL_newstate();

   luaL_openlibs(L);

   {
      CheckForMemoryLeaks check(L);

      luaL_newlib(L, LEA_METHODS);
      luaL_newlib(L, LEA_METHODS);

      lua_setglobal(L, "lea");
   }

}

LuaHost::~LuaHost() {
   lua_close(L);
}

void LuaHost::load_script(const char* filename) {
   if (luaL_loadfile(L, filename) != LUA_OK) {
      throw LuaHostException("failed to load script file");
   }
   if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
      throw LuaHostException("failed to run lua script");
   }
}

void LuaHost::getObject(const char* name) {
   int type = lua_getglobal(L, name);
   if (type == LUA_TNONE) {
      lua_pop(L, 1);
      return;
   }
   if (type != LUA_TTABLE) {
      lua_pop(L, 1);
      throw LuaHostException("requested name is not an object");
   }
}

void LuaHost::getMethod(const char *name) {
   int type = lua_getfield(L, -1, name);
   if (type == LUA_TNONE) {
      lua_pop(L, 1);
      return;
   }
   if (type != LUA_TFUNCTION) {
      lua_pop(L, 1);
      throw LuaHostException("requested field is not a function");
   }
}

void LuaHost::onConfigure() {
   CheckForMemoryLeaks c(L);

   getObject("lea");
   getMethod("onConfigure");

   if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
      lua_pop(L, 1);
      throw LuaHostException(lua_tostring(L, -1));
   }
   lua_pop(L, 1);
}

void LuaHost::onInit() {
   CheckForMemoryLeaks c(L);

   getObject("lea");
   getMethod("onInit");

   if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
      lua_pop(L, 1);
      throw LuaHostException(lua_tostring(L, -1));
   }
   lua_pop(L, 1);
}

void LuaHost::onQuit() {
   CheckForMemoryLeaks c(L);

   getObject("lea");
   getMethod("onQuit");

   if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
      lua_pop(L, 1);
      throw LuaHostException(lua_tostring(L, -1));
   }
   lua_pop(L, 1);
}

//          oo                   dP            dP
//                               88            88
// .d8888b. dP 88d888b. .d8888b. 88 .d8888b. d8888P .d8888b. 88d888b.
// Y8ooooo. 88 88'  `88 88'  `88 88 88ooood8   88   88'  `88 88'  `88
//       88 88 88    88 88.  .88 88 88.  ...   88   88.  .88 88    88
// `88888P' dP dP    dP `8888P88 dP `88888P'   dP   `88888P' dP    dP
//                           .88
//                       d8888P

LuaHost *LuaSingleton::_singleton = NULL;

void LuaSingleton::create() {
   assert(LuaSingleton::_singleton == NULL);

   LuaSingleton::_singleton = new LuaHost();
}

void LuaSingleton::destroy() {
   assert(LuaSingleton::_singleton != NULL);

   delete LuaSingleton::_singleton;
   LuaSingleton::_singleton = NULL;
}

LuaHost& LuaSingleton::get() {
   return *LuaSingleton::_singleton;
}
