#include "lua_host.hpp"

#include <gtkmm.h>

#include <iostream>
#include <vector>

int main(int argc, char **argv) {
    Gtk::Main kit(argc, argv);

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

    Gtk::Main::run();

    return 0;
}
