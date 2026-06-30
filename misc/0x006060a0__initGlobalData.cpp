// FUNC_NAME: initGlobalData
void initGlobalData(void)
{
    // Clear main global data buffer (0x38260 bytes)
    memset(&g_globalDataBuffer, 0, 0x38260);

    // Initialize handle table to -1 (0x200 bytes)
    memset(&g_handleTable, 0xFF, 0x200);

    // Reset two flag bytes
    g_someFlag1 = 0;
    g_someFlag2 = 0;

    // Store result of system initialization call
    g_somePointer = FUN_00ab4c40();

    // Initialize subsystems
    FUN_006185d0();
    FUN_00606b50(); // Called three times (likely per-slot init)
    FUN_00606b50();
    FUN_00606b50();
    FUN_006156e0();
}