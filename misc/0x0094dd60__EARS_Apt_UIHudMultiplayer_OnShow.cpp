// Xbox PDB: EARS_Apt_UIHudMultiplayer_OnShow
// FUNC_NAME: HUDManager::updateScoreAndSpecialties
void HUDManager::updateScoreAndSpecialties() {
    // Check if we need to show specialties (e.g., unlock notification)
    if (m_bShowSpecialties) { // +0x48
        sendUICommand("AddSpecialties", 0, &g_uiCommandData, 0);
    }

    // Always update score display elements
    sendUICommand("SetScoreLimit", 0, &g_uiCommandData, 0);
    sendUICommand("UpdateScoreMultiplier", 0, &g_uiCommandData, 0);
    sendUICommand("UpdateScoreDisplay", 0, &g_uiCommandData, 0);

    // Call virtual update on the global UI manager (vtable+0x28)
    g_pUIManager->process();

    // Check invincibility state and show if active
    if (m_bInvincible) { // +0xba
        sendUICommand("StartInvincibility", 0, &g_uiCommandData, 0);
    }
}