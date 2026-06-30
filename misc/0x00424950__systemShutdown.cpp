// FUNC_NAME: systemShutdown
// Address: 0x00424950
// Role: Global shutdown routine - calls cleanup registration and invokes singleton virtual method (likely release/shutdown)
void systemShutdown(void)
{
    // Register a cleanup callback (0 = null context, function pointer at LAB_00424870)
    FUN_00607d50(0, &LAB_00424870);

    // If the engine singleton exists, call its first vtable method (likely a release or shutdown) with argument 1
    if (g_pEngineSingleton != (void**)0x0) {
        (*(void(__thiscall*)(void*, int))*g_pEngineSingleton[0])(g_pEngineSingleton, 1);
    }
}