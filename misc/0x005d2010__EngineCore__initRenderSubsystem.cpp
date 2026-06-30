// FUNC_NAME: EngineCore::initRenderSubsystem
// Function address: 0x005d2010
// Initializes a render subsystem, likely part of EARS framework startup.
// Sets global flags and configures core engine object via vtable calls.

void EngineCore::initRenderSubsystem(int resourceHandle, int param2, void* param3, int param4)
{
    // Step 1: Call sub-initializers
    initSubsystem1();                                                      // FUN_005d8a70
    setConfig(g_someGlobal1, g_someGlobal2, param4);                       // FUN_0060add0
    setParameter(param3);                                                  // FUN_00612210
    registerResource(0, resourceHandle, 8, 0, 0, 0, 1);                   // FUN_0060c8d0
    flushCommands();                                                       // FUN_006102c0

    // Step 2: Retrieve core engine object and call method at vtable+0x144
    int* pCore = g_pCoreObject;                                            // DAT_01205750
    int coreVtable = *pCore;
    int someId = getSomeId();                                              // FUN_0060c9d0
    (*(void (**)(int*, int, int, int))(coreVtable + 0x144))(pCore, 5, 0, someId);

    // Step 3: Set flag if not already 1 (enable feature)
    if (g_bFlag1 != 1) {                                                   // DAT_011da7f0
        (*(void (**)(int*, int, int))(coreVtable + 0x198))(pCore, 0, 1);
        g_bFlag1 = 1;
    }

    // Step 4: Clear flag if non-zero (disable feature)
    if (g_bFlag2 != 0) {                                                   // DAT_011da7f4
        (*(void (**)(int*, int, int, int, int))(coreVtable + 400))(pCore, 0, 0, 0, 0);
        g_bFlag2 = 0;
    }

    return;
}