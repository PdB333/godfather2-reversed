// FUNC_NAME: PlayerReputationTracker::updateIdleTimer
int __thiscall PlayerReputationTracker::updateIdleTimer(char advance)
{
    // advance == 0 means the timer is not being paused/reset
    // gGameManager->m_bPlayerInactive (offset +0x6c) indicates if the player is in a state that blocks progression
    // gCurrentGameState (DAT_01130548) == 6 likely corresponds to a specific game phase (e.g., investigation)
    if (advance == '\0' && gGameManager->m_bPlayerInactive == 0) {
        // Current game state must be the correct phase for this timer to run
        if (gCurrentGameState == 6) {
            // Increment the accumulator (offset +0x64 = 100)
            this->m_timerCounter += gTimerIncrement;
            // Check if the total elapsed time (in ms? or frames?) exceeds 30000
            if ((uint)this->m_timerCounter < 30000) {
                return 0;
            }
            // Trigger state transition: set global state to 7 and call the next step
            gGlobalState = 7;
            FUN_00931010(); // likely triggers cutscene or next mission phase
        }
        return 1; // returned when timer was allowed to run and either completed or state not 6
    }
    // If advance is non-zero or player is busy, reset the timer
    this->m_timerCounter = 0;
    return 0;
}