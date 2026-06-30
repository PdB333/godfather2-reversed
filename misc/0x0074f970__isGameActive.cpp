// FUNC_NAME: isGameActive
// Address: 0x0074f970
// Role: Checks whether the game is in an active gameplay state (not paused/menu)

int isGameActive(void) {
    // Get the singleton game manager instance
    void* pManager = getGameManager(); // FUN_00800a90, likely returns a pointer to GodfatherGameManager or similar
    if (pManager == nullptr) {
        return 0;
    }
    // Check flag at offset 0x328 (e.g., bIsPaused or bInMenu)
    return (*(int*)((char*)pManager + 0x328) == 0) ? 1 : 0;
}