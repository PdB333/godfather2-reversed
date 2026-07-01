// FUNC_NAME: DifficultyManager::updateDifficulty
int DifficultyManager::updateDifficulty(void)
{
    int difficultyLevel = 0;
    // g_difficultyManager is a global pointer to a DifficultyManager instance
    // +0xd8: likely a flag indicating whether dynamic difficulty is enabled
    if ((g_difficultyManager != 0) && (*(int *)(g_difficultyManager + 0xd8) != 0)) {
        difficultyLevel = setDifficultyLevel(2); // Hard difficulty
    }
    // g_playerState is a global pointer to a PlayerState object
    // +0x64 (100): likely player's health or level; condition: <8 or >0x13 (19)
    if ((g_playerState != 0) &&
        ((*(int *)(g_playerState + 100) < 8 || (0x13 < *(int *)(g_playerState + 100))))) {
        if (difficultyLevel != 0) goto LAB_0078dc01;
        difficultyLevel = setDifficultyLevel(1); // Medium difficulty
    }
    if (difficultyLevel == 0) {
        setDifficultyLevel(0); // Easy difficulty
    }
LAB_0078dc01:
    int outParam = 0;
    int baseValue = getDifficultyValue(&outParam); // returns some base value
    return baseValue + 0x50; // final difficulty offset
}