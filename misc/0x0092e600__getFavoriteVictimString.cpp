// FUNC_NAME: getFavoriteVictimString

char* __cdecl getFavoriteVictimString(void)
{
    // local variable used as output for FUN_004BB370 (likely hash or key)
    int outHash = 0;

    // g_pScoreDataBase is a global pointer to a score data manager structure
    // +0x4: pointer to current player's score data
    int* pScoreDataPtr = *(int**)(g_pScoreDataBase + 4);

    int* pScoreObject = 0;
    if (pScoreDataPtr != 0)
    {
        // *pScoreDataPtr is a pointer to a per-player score structure
        // subtract 0x1f30 to get the base of that structure
        pScoreObject = (int*)((char*)*pScoreDataPtr - 0x1f30);
    }

    // g_pMultiplayerGlobals + 0x16c: flag indicating multiplayer scoreboard is active
    if (*(int*)(g_pMultiplayerGlobals + 0x16c) != 0 && pScoreObject != 0)
    {
        // Get a localization hash using the global localization database,
        // the string key stored at pScoreObject + 0x1ef8, and output hash
        int locResult = FUN_004BB370(g_pLocalizationDB, *(int*)(pScoreObject + 0x1ef8), &outHash);

        // Convert the result to a string ID
        int stringId = FUN_004BAF60(locResult);

        if (stringId != 0)
        {
            // Retrieve the actual string pointer from the string table
            int* stringPtr = (int*)FUN_004BB600(stringId);
            if ((char*)*stringPtr != 0)
            {
                return (char*)*stringPtr;
            }
            // Fallback to empty string
            return (char*)g_pEmptyString;
        }
    }

    // Default localization key for "No favorite victim" in multiplayer finalscore
    return "$mp_finalscore_no_favorite_victim";
}