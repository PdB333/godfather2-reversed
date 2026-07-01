// FUNC_NAME: GodfatherGameManager::updateGameState
void __fastcall GodfatherGameManager::updateGameState(int *this) {
    bool bVar1;

    bVar1 = FUN_00481620(); // Check if game start menu is active
    if (bVar1) {
        bVar1 = FUN_007dca70(this); // Check if we're in a transition state (e.g., loading)
        if (!bVar1) {
            // Not in transition – begin actual game session
            FUN_00481530();   // Initialize gameplay systems (e.g., mission manager)
            FUN_00705e70();   // Start world simulation
            this[0x927] &= 0xffffffdf; // Clear bit 5 of flags at offset 0x927 (e.g., inMainMenu)
            FUN_0093a2f0();   // Update camera or HUD state

            // Check bit 2 of flags at offset 0x928 (e.g., firstUpdateDone)
            if ((this[0x928] >> 2) & 1) {
                // Call vtable function at offset 0x288 with command 5,0,0
                // This might be a "startTutorial" or "showIntroduction" event
                (**(void (__thiscall **)(int*, int, int, int))(this[0] + 0x288))(this, 5, 0, 0);
                this[0x928] &= 0xfffffffb; // Clear bit 2 of flags at offset 0x928
            }
            this[0x929] &= 0xfffff7ff; // Clear bit 11 of flags at offset 0x929 (e.g., pausePending)
            return;
        }
    }
    // If game start menu not active OR we are in transition, check other condition
    bVar1 = FUN_00481640(); // Check if game over state is active
    if (!bVar1) {
        // Not game over – return
        return;
    }
    // Game over – handle end-of-game sequence
    FUN_00472120(); // Show game over screen or trigger win/lose logic
    return;
}