// FUNC_NAME: ViewportManager::clearActiveViewport

extern int g_currentRenderTargetAddress;  // DAT_011f3910
extern int g_currentRenderTargetFlags;   // DAT_011f3914
extern int g_currentViewportAddress;     // DAT_011f38f0
extern int g_currentViewportFlags;       // DAT_011f38f4
extern int g_defaultRenderTarget;        // DAT_012058a8
extern int g_defaultViewport;            // DAT_012058a4
extern void* g_pScene;                   // DAT_012054dc
extern int g_viewportIdTable[20];        // DAT_01218e50 (IDs)
extern int g_viewportFlagsTable[20];     // DAT_01218e54 (flags)

void __fastcall ViewportManager::clearActiveViewport(void* pDevice)
{
    // --- Save current render target state and set to default ---
    int savedRTAddr = g_currentRenderTargetAddress;
    int savedRTFlags = g_currentRenderTargetFlags;
    g_currentRenderTargetAddress = g_defaultRenderTarget;
    g_currentRenderTargetFlags = 0;
    FUN_00609340(4, savedRTAddr, savedRTFlags, pDevice); // push/set render target
    FUN_0060dc10(); // commit/clear

    // --- Save again (now the default) and apply override if scene present ---
    int savedRT2Addr = g_currentRenderTargetAddress;
    int savedRT2Flags = g_currentRenderTargetFlags;
    g_currentRenderTargetAddress = g_defaultRenderTarget;
    if (g_pScene != nullptr) {
        g_currentRenderTargetAddress = *(int*)((char*)g_pScene + 0x170); // scene-specific render target override
    }
    g_currentRenderTargetFlags = 0;
    FUN_00609340(4, savedRT2Addr, savedRT2Flags, pDevice); // set render target again

    // --- Determine viewport address (default or scene override) ---
    int viewportAddr = g_defaultViewport;
    if (g_pScene != nullptr) {
        viewportAddr = *(int*)((char*)g_pScene + 0x16c); // scene-specific viewport override
    }

    // --- Find matching viewport entry and clear its dirty flags ---
    for (int i = 0; i < 20; i++) {
        if (g_viewportIdTable[i] == viewportAddr) {
            g_viewportFlagsTable[i] &= 0xFFFFFFFC; // clear bottom 2 bits (dirty/valid flags)
            break;
        }
    }

    // --- Set current viewport and clear depth/stencil ---
    int savedVPAddr = g_currentViewportAddress;
    int savedVPFlags = g_currentViewportFlags;
    g_currentViewportAddress = viewportAddr;
    g_currentViewportFlags = 0;
    FUN_00609340(0, savedVPAddr, savedVPFlags, pDevice); // set viewport
    FUN_0060db60(0, 0, 0, 1.0f, 1.0f); // clear depth/stencil to 1.0
}