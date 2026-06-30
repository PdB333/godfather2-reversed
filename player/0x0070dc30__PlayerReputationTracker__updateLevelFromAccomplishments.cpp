// FUNC_NAME: PlayerReputationTracker::updateLevelFromAccomplishments

void __thiscall PlayerReputationTracker::updateLevelFromAccomplishments(int thisPtr, int newLevelThreshold)
{
    int achievementId = getAchievementId();          // FUN_004ab370 - returns some ID
    applyAchievement(achievementId);                // FUN_0043b210 - apply achievement
    finalizeAchievement(achievementId);             // FUN_0043ad10 - finalize/complete achievement

    int *accomplishmentFlags = (int *)getAccomplishmentFlags(); // FUN_004ab360 - returns pointer to 4-int flags (16 bytes total)

    // Check if any of the four accomplishment flags are non-zero (i.e., some progress was made)
    if ( (accomplishmentFlags[0] != 0) || (accomplishmentFlags[1] != 0) ||
         (accomplishmentFlags[2] != 0) || (accomplishmentFlags[3] != 0) )
    {
        // If the current level (stored at offset +0x3e0) is less than the new threshold + 1,
        // update the level to the new value.
        // +0x3e0: int currentLevel
        if (*(int *)(thisPtr + 0x3e0) < newLevelThreshold + 1)
        {
            *(int *)(thisPtr + 0x3e0) = newLevelThreshold + 1;
        }
    }
}