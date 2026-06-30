// FUNC_NAME: setPlayerConditionFlags
// Address: 0x005e2c20
// Sets condition flags on the player entity if cheats/debug mode is active.
// Returns 1 on success, 0 on failure.
int setPlayerConditionFlags(uint newFlags)
{
    // Global pointer to a game manager (likely CheatManager or DebugMenu)
    // Byte at offset 0x1744 indicates whether cheats are enabled.
    if (*(char *)(DAT_0122350c + 0x1744) != 0)
    {
        // Retrieve the player entity/actor pointer.
        // Function at 0x005e2150 returns a pointer to the player's state object.
        int *pEntity = (int *)FUN_005e2150();
        if (pEntity != 0)
        {
            // OR the new flags into the field at offset 0x250 (e.g., conditionFlags).
            pEntity[0x94] |= newFlags; // 0x250 / 4 = 0x94, assuming 4-byte int
            return 1;
        }
    }
    return 0;
}