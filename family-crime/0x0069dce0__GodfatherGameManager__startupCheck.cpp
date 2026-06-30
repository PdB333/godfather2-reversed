// FUNC_NAME: GodfatherGameManager::startupCheck
int GodfatherGameManager::startupCheck(void)
{
    char statusFlag;

    // gpGameManager is a global pointer to the main game manager singleton
    if (DAT_01223484 == 0) {
        // If no game manager exists, set paused state to false (resume)
        setPaused(false);
    }
    else {
        // Otherwise check if the game manager is ready via a status function
        statusFlag = isGameReady(); // FUN_008a4380
        if ((statusFlag != '\0') || (*(int *)(DAT_01223484 + 0xc) != 0)) {
            // Game not fully initialized yet; can't start
            return 0;
        }
    }

    // Ensure global initialization flag is set and game is not already active
    if ((DAT_0122337c != 0) && (DAT_0112a02b == '\0')) {
        DAT_0112a02b = '\x01'; // Mark game as active
        setGameActive(true);    // FUN_004067e0
    }

    // Finally set paused state to false (resume gameplay)
    setPaused(false);
    return 1;
}