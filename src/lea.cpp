/*
    Lea - Lightweight UI for your tools.
    Copyright (C) 2022   Milutin Jovanović

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "lea.hpp"
#include "lea_util.hpp"

#include <LuaBridge.h>
#include <gtkmm.h>

std::unique_ptr<Lea::VarStorage> Lea::vars;

void Lea::log(const std::string& msg) {
   std::cerr << msg << std::endl;
}

void Lea::quit() {
   Gtk::Application::get_default()->quit();
}

void Lea::registerClass(lua_State *L) {
   Lea::vars = std::make_unique<Lea::VarStorage>(L);

   luabridge::getGlobalNamespace(L)
      .beginNamespace("lea")
         .addFunction("log", &Lea::log)
         .addFunction("quit", &Lea::quit)
         .addProperty("VERSION", &Lea::vars->VERSION, false)
         .addProperty("onConfigure", &Lea::vars->onConfigure)
         .addProperty("onInit", &Lea::vars->onInit)
         .addProperty("onQuit", &Lea::vars->onQuit)
      .endNamespace();
}
