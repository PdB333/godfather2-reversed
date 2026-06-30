// FUNC_NAME: clampDisplaySettings
void clampDisplaySettings() {
    // Clamp global display settings (likely FPS and resolution)
    if (g_minFps < 0x16) {          // 22
        g_minFps = 0x16;
    }
    if (0x16 < g_maxFps) {          // 22
        g_maxFps = 0x16;
    }
    g_bVsyncEnabled = 1;            // +0x?? (part of global state)

    if (g_minFps < 0xe) {           // 14
        g_minFps = 0xe;
    }
    if (0xe < g_maxFps) {           // 14
        g_maxFps = 0xe;
    }
    g_bTripleBuffering = 0;         // +0x??

    if (g_minResolutionX < 0xa8) {  // 168
        g_minResolutionX = 0xa8;
    }
    if (0xa7 < g_maxResolutionX) {  // 167 < max => set to 168
        g_maxResolutionX = 0xa8;
    }
    g_bSomeFlag = 0;                // +0x??

    if (g_minResolutionX < 0xbe) {  // 190
        g_minResolutionX = 0xbe;
    }
    if (0xbd < g_maxResolutionX) {  // 189 < max => set to 190
        g_maxResolutionX = 0xbe;
    }
    g_bAnotherFlag = 0;             // +0x??

    // Call settings-related functions
    FUN_00613440(1);                // setSomeSetting(1)
    FUN_00612a60();                 // applySettingChanges()

    // Sync a stored resolution value and possibly update a device object
    int currentResX = DAT_01163cc8; // current horizontal resolution (may be from registry)
    if (g_storedResX != currentResX) {
        // Call method at vtable offset 0x15c on object at DAT_01205750
        // (likely IDirect3D9::Reset or similar)
        (**(code **)(*DAT_01205750 + 0x15c))(DAT_01205750, currentResX);
        g_storedResX = currentResX;
    }

    // Copy 12 bytes from global structure to some output buffer (maybe video mode info)
    FUN_0060c8d0(0, &DAT_01163c80, 0xc, 0, 0, 0, 1);
}