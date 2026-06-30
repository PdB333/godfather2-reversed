// FUNC_NAME: GodfatherGameManager::getScenarioMissionHash
// Function address: 0x0072d160
// Role: Returns a mission hash based on current scenario, or default if cheat/flag conditions not met.
// Uses __fastcall: param_1 is this pointer.

unsigned int __fastcall GodfatherGameManager::getScenarioMissionHash(void* this_ptr) {
    unsigned int defaultHash = 0xf273b21a; // Generic default mission hash
    unsigned int flags = *(unsigned int*)((char*)this_ptr + 0x8e0); // +0x8e0: m_gameFlags

    // Check bit 10 (0x400) of the game flags
    if ((flags & (1 << 10)) != 0) {
        // Check if cheat/debug mode is active
        if (isCheatModeEnabled() != 0) {
            int scenarioIndex = getCurrentScenarioIndex(); // Returns 1-4
            switch (scenarioIndex) {
                case 1:
                    return 0x1450f56b; // Campaign mission hash
                case 2:
                    return 0x675e71f6; // Hit mission hash
                case 3:
                case 4:
                    return 0x5c087c1e; // Favor or empire mission hash
            }
        }
    }
    return defaultHash;
}