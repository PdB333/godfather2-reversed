// FUNC_NAME: TimedActionSystem::updateTimers
extern float g_currentTime; // DAT_00e2af44
extern float g_timerA; // DAT_01197d70
extern float g_timerB; // DAT_01197d74
extern int g_actionFlags; // DAT_01197d90 (bit 22 used)
extern int g_unknownInt1; // DAT_01197d78
extern int g_unknownInt2; // DAT_01197d7c
extern float g_defaultFloat1; // DAT_00e2b118
extern float g_defaultFloat2; // DAT_00e2b1a4
extern float g_defaultFloat3; // DAT_00e446c4

void TimedActionSystem::updateTimers()
{
    // Check if current time is before both timers, or if the action flag is set (bit 22)
    if ((g_currentTime <= g_timerA && g_currentTime <= g_timerB) || (g_actionFlags & 0x400000) != 0)
    {
        // Execute the pending action (e.g., trigger vibration, state transition)
        FUN_005279e0();
    }

    // Reset all timer and state variables
    g_timerA = 0.0f;
    g_timerB = 0.0f;
    g_unknownInt1 = 0;
    g_unknownInt2 = 0;

    // Restore default values from configuration globals
    g_defaultFloat1 = g_defaultFloat1; // Note: self-assignment? Likely different global address
    g_defaultFloat2 = g_defaultFloat2; // from DAT_00e2b118 => g_unknownFloatA, etc.
    g_defaultFloat3 = g_defaultFloat3;
    g_defaultFloat2 = g_defaultFloat2; // duplicate? Possibly two different fields

    // Clear the action flags
    g_actionFlags = 0;
}