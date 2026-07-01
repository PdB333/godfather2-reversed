// FUNC_NAME: GodfatherGameManager::getActivePlayer
void* __thiscall GodfatherGameManager::getActivePlayer(void) {
    // param_1 = this
    // Dereference this + 0x58 to get a pointer to the simulation manager
    void* simManager = *(void**)((char*)this + 0x58); // +0x58 likely pointer to SimManager

    if (simManager != 0) {
        // Check bit 10 (0x400) at offset 0x8E0 in the simulation manager
        uint flags = *(uint*)((char*)simManager + 0x8E0);
        if ((flags >> 10) & 1) {
            // If the flag is set, call a global function that returns the player object
            return FUN_00800a90(); // e.g., getSimPlayer()
        }
    }
    return 0; // return nullptr if condition not met
}