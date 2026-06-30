// FUNC_NAME: GameStateManager::processCommand
void GameStateManager::processCommand(int actionIndex, int playerSlot)
{
    // Global game state manager at 0x12233b4
    // +0x564 = current game mode (char). 0x12 indicates a specific mode (e.g., loading/menu)
    char currentMode = *(char *)(g_pGameStateManager + 0x564);
    if (currentMode == 0x12) {
        return; // Skip processing in this mode
    }

    // playerSlot must be less than 15 (max players/controllers)
    if ((playerSlot < 15) && (currentMode != 0x12)) {
        // Perform some per-player initialization/update
        char modeArg = currentMode; // passed to helper
        GameStateManager::getComponent(modeArg); // returns something
        GameStateManager::updateSomething(); // update auxiliary state
    }

    // DWORD array at 0x1129bd4, indexed by actionIndex * 2
    // This array holds opaque handles/IDs
    undefined4 actionHandle = g_actionTable[actionIndex * 2];

    // Retrieve the component again (likely the same pointer each time)
    int *pComponent = (int *)GameStateManager::getComponent(currentMode);
    
    // Call the second vtable method (offset 8) with the action handle
    (**(code **)(*pComponent + 8))(actionHandle);
}