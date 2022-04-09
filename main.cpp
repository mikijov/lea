#include "lua_host.hpp"

int main(int argc, char **argv)
{
   try {
      LuaHost host;
      host.load_script("../main.lua");
      host.onConfigure();
      host.onInit();
   }
   catch (const std::exception& e) {
      printf("EXCEPTION: %s\n", e.what());
      return 1;
   }
   return 0;
}

// #include <iostream>


// static bool quit = false;


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
