#pragma once

struct lua_State;

int lea_notification_show(lua_State *L);
int lea_notification_setClickHandler(lua_State *L);
int lea_notification_setTimeout(lua_State *L);
