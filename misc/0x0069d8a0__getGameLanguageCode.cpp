// FUNC_NAME: getGameLanguageCode
#include <Windows.h>

int getGameLanguageCode()
{
    LANGID sysLangId = GetUserDefaultLangID();
    
    // Extract primary language ID (low 10 bits)
    switch (sysLangId & 0x3ff)
    {
    case 0x05: // LANG_GERMAN (German)
        return 1;
    case 0x07: // LANG_FRENCH (French)
        return 3;
    case 0x0A: // LANG_SPANISH (Spanish)
        return 7;
    case 0x0C: // LANG_FRENCH (French? Actually LANG_FRENCH = 0x0C)
        return 2;
    case 0x10: // LANG_ITALIAN (Italian)
        return 4;
    case 0x13: // LANG_DUTCH (Dutch)
        return 8;
    case 0x15: // LANG_POLISH (Polish)
        return 5;
    case 0x19: // LANG_RUSSIAN (Russian)
        return 6;
    default:
        return 0; // Default fallback (likely English)
    }
}