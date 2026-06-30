// FUNC_NAME: isGameStateActive
// Address: 0x00608210
// Checks if global game state is set to mode 1 or 2 (likely playing or paused)
int isGameStateActive(void)
{
    // Global variable at 0x00f15a14 - likely represents current game mode
    if ((gGameMode != 1) && (gGameMode != 2)) {
        return 0;
    }
    return 1;
}