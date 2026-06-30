// FUNC_NAME: GameManager::checkAndApplyRumble
void GameManager::checkAndApplyRumble(void)
{
    // Check if game is in a state where rumble is allowed (e.g., not paused, not in menus)
    bool isGameActive = FUN_004166b0();  // Likely returns true if the game is running and interactive
    if ((isGameActive) && ((DAT_011f7430 & 1) != 0)) {  // DAT_011f7430 bit 0 -> rumble enabled flag
        // Actual rumble processing: apply force feedback to controller(s)
        FUN_00614a50();  // Handles XInputSetState or similar
    }
    // If conditions not met, skip rumble
}