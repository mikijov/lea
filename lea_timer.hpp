#pragma once

struct lua_State;

int lea_timer_create(lua_State *L);
int lea_timer_destroy(lua_State *L);
int lea_timer_resetTimeout(lua_State *L);
