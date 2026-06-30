// FUNC_NAME: GameManager::updateGameState
// Function at 0x00537a90 - calls internal update/dispatch function with global manager and state sub-object
void GameManager::updateGameState(void)
{
    // g_pGameManager (DAT_0121a390) - global singleton pointer
    // g_pGameState + 0x8 (DAT_0121b638) - likely pointer to current active scene/state
    FUN_0060ab00(g_pGameManager, *(int *)((uint8_t *)g_pGameState + 8));
}