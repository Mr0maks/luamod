#include "zone_luamod_mem.h"
#include "zone.h"

void Lua_Alloc_Init(void);

byte *luamod_mem_pool; //main mempool!!

void Memory_Pools_Init()
{
    Lua_Alloc_Init();
    luamod_mem_pool = Mem_AllocPool("Luamod main mempool");
}