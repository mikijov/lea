#pragma once

struct lua_State;

int lea_menu_create(lua_State *L);
int lea_menu_addSubMenu(lua_State *L);
int lea_menu_addItem(lua_State *L);
int lea_menu_addSeparator(lua_State *L);
