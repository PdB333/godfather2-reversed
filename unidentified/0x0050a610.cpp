// FUNC_0050a610: GameStateManager::GetCurrentMissionID
// Address: 0x0050a610
// Role: Retrieves the current mission ID from the global game state manager singleton.
// Called from various places to check which mission is active.

int GameStateManager::GetCurrentMissionID(void)
{
    GameStateManager *pManager = GameStateManager::GetInstance(); // FUN_00421170
    if (pManager != (GameStateManager *)0x0) {
        return *(int *)((int)pManager + 0x14); // m_iCurrentMissionID at +0x14
    }
    return 0;
}