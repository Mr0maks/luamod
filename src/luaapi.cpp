#include <extdll.h>
#include <meta_api.h>
#include "plugins.h"

int lPrint (lua_State *L);
int lLoad (lua_State *L);
int lSubscribe (lua_State *L);
void loadLuaApi(lua_State *state)
{
    luaL_openlibs(state);
    lua_register(state, "print", lPrint);
    lua_register(state, "load", lLoad);
    lua_register(state, "subscribe", lSubscribe);
}