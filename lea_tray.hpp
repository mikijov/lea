#pragma once

struct lua_State;

int lea_tray_create(lua_State *L);
int lea_tray_destroy(lua_State *L);
int lea_tray_setClickHandler(lua_State *L);
int lea_tray_setScrollHandler(lua_State *L);
