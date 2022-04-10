#include "lua_host.hpp"

#include <gtkmm.h>

#include <iostream>
#include <vector>

int main(int argc, char **argv) {
    Gtk::Main kit(argc, argv);

    LuaSingleton::create();

    try {
       LuaSingleton::get().load_script("../main.lua");
       LuaSingleton::get().onConfigure();
       LuaSingleton::get().onInit();

       Gtk::Main::run();

       LuaSingleton::destroy();
    }
    catch (const std::exception& e) {
       printf("EXCEPTION: %s\n", e.what());
       return 1;
    }

    return 0;
}
