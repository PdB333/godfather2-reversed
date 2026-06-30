// FUNC_NAME: isGameplayActive
// Function at 0x00527e20: Checks if game state allows gameplay by comparing a timer to two thresholds and verifying a flag bit is not set.
// Global variables: g_gameTime (0x00e2af44), g_gameTimeThreshold1 (0x01197d70), g_gameTimeThreshold2 (0x01197d74), g_gameStateFlags (0x01197d90)
// The bit 0x400000 (bit 22) likely indicates paused/menu/cutscene state.

int isGameplayActive() {
    // Condition: timer is <= both thresholds, OR flag bit is set
    // Then AND with flag bit not set -> effectively timer <= thresholds AND bit clear
    if (((g_gameTime <= g_gameTimeThreshold1 && g_gameTime <= g_gameTimeThreshold2) ||
        ((g_gameStateFlags & 0x400000) != 0)) &&
        ((g_gameStateFlags & 0x400000) == 0)) {
        return 1;
    }
    return 0;
}