#include <iostream>

#include <lua.hpp>

static bool quit = false;

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
   quit = true;
   return 0;
}

int main(int argc, char ** argv) {
   lua_State *L = luaL_newstate();
   luaL_openlibs(L);

   lua_newtable(L);
   lua_pushcfunction(L, lea_log); lua_setfield(L, -2, "log");
   lua_pushcfunction(L, lea_quit); lua_setfield(L, -2, "quit");
   lua_setglobal(L, "lea");

   if (luaL_loadfile(L, "../main.lua") != LUA_OK) {
      printf("failed to load file\n");
      return 1;
   }
   if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
      printf("ERROR running file: %s\n", lua_tostring(L, -1));
      lua_pop(L, 1);
   }

   printf("%d\n", lua_gettop(L));
   if (lua_getglobal(L, "lea") == LUA_TTABLE) {
      if (lua_getfield(L, -1, "onConfigure") == LUA_TFUNCTION) {
         if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
            printf("ERROR lea.onConfigure: %s\n", lua_tostring(L, -1));
            lua_pop(L, 1);
         }
      } else {
         printf("no lea.onConfigure\n");
      }
   } else {
      printf("lea is not a table\n");
   }
   lua_pop(L, 1);

   printf("%d\n", lua_gettop(L));
   if (lua_getglobal(L, "lea") == LUA_TTABLE) {
      if (lua_getfield(L, -1, "onInit") == LUA_TFUNCTION) {
         if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
            printf("ERROR lea.onInit: %s\n", lua_tostring(L, -1));
            lua_pop(L, 1);
         }
      } else {
         printf("no lea.onInit\n");
      }
   } else {
      printf("lea is not a table\n");
   }
   lua_pop(L, 1);

   printf("%d\n", lua_gettop(L));
   if (lua_getglobal(L, "lea") == LUA_TTABLE) {
      if (lua_getfield(L, -1, "onQuit") == LUA_TFUNCTION) {
         if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
            printf("ERROR lea.onQuit: %s\n", lua_tostring(L, -1));
            lua_pop(L, 1);
         }
      } else {
         printf("no lea.onQuit\n");
      }
   } else {
      printf("lea is not a table\n");
   }
   lua_pop(L, 1);

   printf("%d\n", lua_gettop(L));
   lua_close(L);
   return 0;
}

// #include <libnotify/notify.h>
//
// #include <QApplication>
// #include <QLabel>
// #include <QMenu>
// #include <QPushButton>
// #include <QSystemTrayIcon>
// #include <QMessageBox>
//
//
// int show_notification() {
// 	NotifyNotification *notification = notify_notification_new(
//           "Hello world",
//           "This is an example notification.",
//           "dialog-information"
//           );
// 	notify_notification_show(notification, NULL);
// 	g_object_unref(G_OBJECT(notification));
// 	return 0;
// }
//
// class LeaObject: public QObject {
//    public:
//       LeaObject() {
//          _icon = new QIcon("cactus.svg");
//
//          _trayIcon = new QSystemTrayIcon(*_icon);
//
//          connect(_trayIcon, &QSystemTrayIcon::activated, this, &LeaObject::iconActivated);
//          connect(_trayIcon, &QSystemTrayIcon::messageClicked, this, &LeaObject::messageClicked);
//
//          _trayIcon->show();
//       }
//
//       void iconActivated(QSystemTrayIcon::ActivationReason reason) {
//          switch (reason) {
//             case QSystemTrayIcon::Trigger:
//                _trayIcon->showMessage("Reason", "Trigger");
//                break;
//             case QSystemTrayIcon::DoubleClick:
//                _trayIcon->showMessage("Reason", "DoubleClick");
//                show_notification();
//                break;
//             case QSystemTrayIcon::MiddleClick:
//                _trayIcon->showMessage("Reason", "MiddleClick");
//                break;
//             default:
//                QApplication::quit();
//                ;
//          }
//       }
//
//       void messageClicked() {
//          std::cout << "messageClicked" << std::endl;
//       }
//
//    private:
//       QIcon *_icon;
//       QSystemTrayIcon *_trayIcon;
//
//    private:
//       LeaObject(const LeaObject&);
//       const LeaObject& operator=(const LeaObject&) const;
// };
//
// int main(int argc, char **argv)
// {
//    QApplication app(argc, argv);
//    notify_init("lea");
//
//    LeaObject lea;
//
//    // QPushButton button(*icon, "Hello world!");
//    // button.show();
//    //
//    // std::cout << "QSystemTrayIcon" << std::endl;
//    // if (QSystemTrayIcon::isSystemTrayAvailable()) {
//    //    std::cout << "SystemTray available." << std::endl;
//    // }
//    // if (QSystemTrayIcon::supportsMessages()) {
//    //    std::cout << "Messages supported." << std::endl;
//    // }
//
//    // QMenu *trayIconMenu = new QMenu();
//    // trayIconMenu->addAction(minimizeAction);
//    // trayIconMenu->addAction(maximizeAction);
//    // trayIconMenu->addAction(restoreAction);
//    // trayIconMenu->addSeparator();
//    // trayIconMenu->addAction(quitAction);
//
//    int exitCode = app.exec();
//    notify_uninit();
//    return exitCode;
// }
