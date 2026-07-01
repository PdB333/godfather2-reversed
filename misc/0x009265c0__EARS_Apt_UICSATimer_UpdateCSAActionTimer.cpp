// Xbox PDB: EARS_Apt_UICSATimer_UpdateCSAActionTimer
// FUNC_NAME: CSATimer::updateTimer
// Function address: 0x009265c0
// Updates a timer progress based on ratio of param_2 to param_3, scaled by global max.
// Called from FUN_008def00 (likely part of CSA action system)

extern float g_CSAActionTimerMax; // Global DAT_00d5f4b4, maximum progress value

void CSATimer::updateTimer(float currentTime, float totalDuration) {
    if (m_active) { // +0x48 boolean flag indicating timer is active
        float progress = (currentTime / totalDuration) * g_CSAActionTimerMax;
        if (progress < 0.0f) {
            progress = 0.0f;
        } else if (progress > g_CSAActionTimerMax) {
            progress = g_CSAActionTimerMax;
        }
        m_progress = progress; // +0x50 float storing current progress

        // Log the update using debug function
        Debug::logUpdate("UpdateCSAActionTimer", 0, &g_CSAActionTimerMax, 0);
    }
}