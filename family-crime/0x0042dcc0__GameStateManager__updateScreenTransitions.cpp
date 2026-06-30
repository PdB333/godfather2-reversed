// FUNC_NAME: GameStateManager::updateScreenTransitions

bool GameStateManager::updateScreenTransitions() {
    // Generic update (likely input/polling)
    updateInput();

    // Check if HUD should be shown and current screen state is 0 (e.g., gameplay)
    if (g_bShowHUD && m_screenState == kScreenState_Gameplay) {
        enterHUDState();
        registerRenderCallback(onHUDRender);
        initializeHUD();
        showHUD();

        g_bPendingFullRedraw = true;
        g_currentCameraAngle = g_targetCameraAngle;
    }

    // Check if menu should be shown and current screen state is not 1 (e.g., not already in menu)
    if (g_bShowMenu && m_screenState != kScreenState_Menu) {
        enterMenuState();
    }

    return 1;
}