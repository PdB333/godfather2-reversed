// FUNC_NAME: getSystemLanguageIndex
// Address: 0x0069d8a0
// Returns an internal language index based on the system's default language ID.
// The mapping translates Windows primary language IDs to game-specific language IDs.
static int getSystemLanguageIndex()
{
    LANGID langId = GetUserDefaultLangID();
    // Extract primary language ID (lower 10 bits)
    switch (langId & 0x3FF)
    {
    case 5:   // LANG_KOREAN? - returns 1
        return 1;
    case 7:   // LANG_GERMAN - returns 3
        return 3;
    case 10:  // LANG_SPANISH - returns 7
        return 7;
    case 12:  // LANG_FRENCH - returns 2
        return 2;
    case 16:  // LANG_ITALIAN - returns 4
        return 4;
    case 19:  // LANG_DUTCH - returns 8
        return 8;
    case 21:  // LANG_PORTUGUESE? - returns 5
        return 5;
    case 25:  // LANG_NORWEGIAN? - returns 6
        return 6;
    default:
        return 0; // English or unknown
    }
}