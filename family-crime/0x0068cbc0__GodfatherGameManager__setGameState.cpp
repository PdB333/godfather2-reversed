// FUNC_NAME: GodfatherGameManager::setGameState
void __thiscall GodfatherGameManager::setGameState(uint8_t state) {
    // +0x14: current state byte
    this->stateByte = state;
    // Global state variable (0x00f17964)
    g_gameState = (uint32_t)state;
    // +0x18: unknown counter, reset to 0
    this->someCounter = 0;
    // Write game state to global structure at offset 0xc (0x012234d8)
    *(uint32_t*)(g_gameStateManager + 0xc) = g_gameState;

    // Call internal update function
    FUN_005648c0(); // likely updateGameStateDependent

    // +0x10: mode indicator (1 = some specific mode)
    if (this->mode == 1) {
        // Check global pointer and its dereferences
        if (g_someOtherGlobal != 0) {
            int** ptr = *(int**)(g_someOtherGlobal + 4);
            if (ptr != 0 && ptr != (int**)0x1f30) {
                // Notify state change to some subsystem
                FUN_00799220(this->stateByte); // likely handleStateTransition
            }
        }
        // Reset something with parameter 0
        FUN_00444930(0); // likely resetTimers
    }

    // If mode is not 3, set to 2
    if (this->mode != 3) {
        this->mode = 2;
    }
}