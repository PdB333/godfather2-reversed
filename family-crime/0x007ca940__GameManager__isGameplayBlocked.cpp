// FUNC_NAME: GameManager::isGameplayBlocked
// Function at 0x007ca940: Checks global conditions that block gameplay (pause, menu, cutscene)
bool __thiscall GameManager::isGameplayBlocked(void* this_ptr)
{
    char condition;
    if (this_ptr == nullptr) {
        return false; // No manager means not blocked
    }
    condition = isGamePaused(); // FUN_0045f120 - returns 1 if paused
    if ((condition != 1) &&
        (condition = isMenuActive(), condition == 0) && // FUN_0045eef0 - returns non-zero if menu active
        (condition = isCutscenePlaying(), condition == 0)) // FUN_007f7c50 - returns non-zero if cutscene playing
    {
        return false; // Not blocked (no pause, no menu, no cutscene)
    }
    return true; // Blocked (pause, menu, or cutscene active)
}