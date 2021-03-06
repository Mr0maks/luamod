#include <extdll.h>
#include <meta_api.h>
#include "ex_rehlds_api.h"

meta_globals_t *gpMetaGlobals;
gamedll_funcs_t *gpGamedllFuncs;
mutil_funcs_t *gpMetaUtilFuncs;
enginefuncs_t *g_pengfuncsTable;

bool g_meta_init = false;

plugin_info_t Plugin_info = {
    META_INTERFACE_VERSION, // ifvers
    "LuaMod", // name
    LUAMOD_VERSION, // version
    __DATE__, // date
    "Mr0maks", // author
    "https://github.com/GG-Project/luamod", // url
    "LM", // logtag
    PT_ANYTIME, // (when) loadable
    PT_NEVER, // (when) unloadable
};

void Meta_Init(void) { g_meta_init = true; }

C_DLLEXPORT int Meta_Query(char *interfaceVersion, plugin_info_t **plinfo, mutil_funcs_t *pMetaUtilFuncs)
{
    *plinfo = &Plugin_info;
    gpMetaUtilFuncs = pMetaUtilFuncs;
    return TRUE;
}

META_FUNCTIONS gMetaFunctionTable = {
    NULL, // pfnGetEntityAPI		HL SDK; called before game DLL
    NULL, // pfnGetEntityAPI_Post		META; called after game DLL
    GetEntityAPI2, // pfnGetEntityAPI2		HL SDK2; called before game DLL
    GetEntityAPI2_Post, // pfnGetEntityAPI2_Post	META; called after game DLL
    GetNewDLLFunctions, // pfnGetNewDLLFunctions	HL SDK2; called before game DLL
    GetNewDLLFunctions_Post, // pfnGetNewDLLFunctions_Post	META; called after game DLL
    GetEngineFunctions, // pfnGetEngineFunctions	META; called before HL engine
    GetEngineFunctions_Post, // pfnGetEngineFunctions_Post	META; called after HL engine
};

void worker_load();

C_DLLEXPORT int Meta_Attach(PLUG_LOADTIME now, META_FUNCTIONS *pFunctionTable, meta_globals_t *pMGlobals, gamedll_funcs_t *pGamedllFuncs)
{
    gpMetaGlobals = pMGlobals;
    gpGamedllFuncs = pGamedllFuncs;

    worker_load();

#ifdef REHLDS_SUPPORT
    if (meta_init_rehlds_api())
        g_engfuncs.pfnServerPrint("ReHLDS API successfully initialized.\n");
#endif

    memcpy(pFunctionTable, &gMetaFunctionTable, sizeof(META_FUNCTIONS));
    return TRUE;
}

C_DLLEXPORT int Meta_Detach(PLUG_LOADTIME now, PL_UNLOAD_REASON reason) { return TRUE; }
