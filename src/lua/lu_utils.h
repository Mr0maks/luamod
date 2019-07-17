#pragma once
#include "luai.h"

namespace lm_utils {
void init_api(lua_State *L);
int l_hud_message(lua_State *L);
int l_is_player(lua_State *L);
int l_get_entity_key_value(lua_State *L);
int l_write_logfile(lua_State *L);
int l_dictinary_init(lua_State *L);
int l_dictinary_find_value(lua_State *L);
} // namespace lm_utils
