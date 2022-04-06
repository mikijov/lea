#include <iostream>

// #include <lua.hpp>
//
// static int sum(lua_State *L) {
//    int n = lua_gettop(L); // number of arguments
//    lua_Number sum = 0.0;
//    for (int i = 1; i <= n; i++) {
//       if (!lua_isnumber(L, i)) {
//          lua_pushliteral(L, "incorrect argument");
//          lua_error(L);
//       }
//       sum += lua_tonumber(L, i);
//    }
//    lua_pushnumber(L, sum); // second result
//    return 1; // number of results
// }
//
// int main(int argc, char ** argv) {
//    lua_State *L = luaL_newstate();
//    luaL_openlibs(L);
//    lua_register(L, "sum", sum);
//
//    // Our Lua code, it simply prints a Hello, World message
//    const char *code = "print(sum(1, 2, 3))";
//
//    // here we load the string and use lua_pcall for run the code
//    if (luaL_loadstring(L, code) == LUA_OK) {
//       if (lua_pcall(L, 0, 0, 0) == LUA_OK) {
//          // if it was executed successfuly we remove the code from the stack
//          lua_pop(L, lua_gettop(L));
//       }
//    }
//
//    lua_close(L);
//    return 0;
// }


#include <QApplication>
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QSystemTrayIcon>
#include <QMessageBox>

class LeaObject: public QObject {
   public:
      LeaObject() {
         _icon = new QIcon("cactus.svg");

         _trayIcon = new QSystemTrayIcon(*_icon);

         connect(_trayIcon, &QSystemTrayIcon::activated, this, &LeaObject::iconActivated);
         connect(_trayIcon, &QSystemTrayIcon::messageClicked, this, &LeaObject::messageClicked);

         _trayIcon->show();
      }

      void iconActivated(QSystemTrayIcon::ActivationReason reason) {
         switch (reason) {
            case QSystemTrayIcon::Trigger:
               _trayIcon->showMessage("Reason", "Trigger");
               break;
            case QSystemTrayIcon::DoubleClick:
               _trayIcon->showMessage("Reason", "DoubleClick");
               break;
            case QSystemTrayIcon::MiddleClick:
               _trayIcon->showMessage("Reason", "MiddleClick");
               break;
            default:
               QApplication::quit();
               ;
         }
      }

      void messageClicked() {
         std::cout << "messageClicked" << std::endl;
      }

   private:
      QIcon *_icon;
      QSystemTrayIcon *_trayIcon;

   private:
      LeaObject(const LeaObject&);
      const LeaObject& operator=(const LeaObject&) const;
};

int main(int argc, char **argv)
{
   QApplication app(argc, argv);

   LeaObject lea;

   // QPushButton button(*icon, "Hello world!");
   // button.show();
   //
   // std::cout << "QSystemTrayIcon" << std::endl;
   // if (QSystemTrayIcon::isSystemTrayAvailable()) {
   //    std::cout << "SystemTray available." << std::endl;
   // }
   // if (QSystemTrayIcon::supportsMessages()) {
   //    std::cout << "Messages supported." << std::endl;
   // }

   // QMenu *trayIconMenu = new QMenu();
   // trayIconMenu->addAction(minimizeAction);
   // trayIconMenu->addAction(maximizeAction);
   // trayIconMenu->addAction(restoreAction);
   // trayIconMenu->addSeparator();
   // trayIconMenu->addAction(quitAction);

   return app.exec();
}
