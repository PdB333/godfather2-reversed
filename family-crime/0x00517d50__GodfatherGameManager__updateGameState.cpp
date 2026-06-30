// FUNC_NAME: GodfatherGameManager::updateGameState

void __fastcall GodfatherGameManager::updateGameState(int this, int param_edx)
{
    // Global variables (likely time/state)
    int currentTime = DAT_00e2af44;              // Current frame count or game time
    int minTime1 = DAT_012192dc;                 // Threshold for state transition
    int minTime2 = _DAT_012192e8;                // Alternative threshold
    int minTime3 = DAT_012192ec;                 // Another threshold
    int state = DAT_012192f0;                    // Current game state (e.g., 0 = initial, 2 = loading, 4 = paused, etc.)

    // Check if current time is within allowed range for transitions
    if (currentTime <= minTime1 &&
        (currentTime <= minTime2 || currentTime <= minTime3))
    {
        if (state < 5)
        {
            if (state == 4)                     // Paused state
            {
                FUN_005186d0(0);                 // resumeGame(0) or setPause(false)
                return;
            }
            if (state == 0)                     // Initial state
            {
                FUN_00518010(param_edx);         // startGame(param_edx)
                return;
            }
            if (state == 2)                     // Loading state
            {
                FUN_00518750();                  // showLoadingScreen()
                return;
            }
        }
        else
        {
            if (state == 8)                     // In-game state
            {
                FUN_005187a0();                  // enterGameplay()
            }
            else if (state == 0x4000000)        // Special state (e.g., cinematic skip)
            {
                FUN_005186d0(1);                 // pauseGame(1)
                return;
            }
        }
    }
    // else: no state transition
}