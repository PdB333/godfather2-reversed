// FUNC_NAME: GodfatherGameManager::setDebugOverlayState

void __cdecl GodfatherGameManager::setDebugOverlayState(char forceDefaultMode) {
    int *pManager = g_pGameManager; // 0x012233b4
    if (pManager == nullptr) {
        return;
    }

    // Determine base mode: 6 (normal) or 0x16 (cinematic mode)
    int mode = 6;
    if (g_bIsInCinematic != 0) {
        mode = 0x16;
    }

    // Store current camera pointer at +0x540 (m_pCamera)
    pManager[0x540 / 4] = getCurrentCamera();

    // Override mode if forced to default
    if (forceDefaultMode == 0) {
        mode = 6;
    }

    // Set rendering mode 3 (overlay type)
    setRenderingMode(3, mode);

    // Determine debug view sub-mode (2 = debug camera, 1 = normal? actually 1 = cinematic)
    uint debugSubMode = 2;
    if (forceDefaultMode != 0) {
        if (isDebugCameraEnabled() != 0) {
            debugSubMode = 1;
        }
    }

    // Check gameplay mode
    char bInGameplay = isInGameplayMode();
    // Compute second rendering mode: if in gameplay, value becomes (4 | debugSubMode); else (8 | debugSubMode)
    uint secondMode = ((bInGameplay != 0) ? 4 : 8) | debugSubMode;
    setRenderingMode(2, secondMode);

    g_bDebugOverlayActive = 1; // 0x01129faf
}