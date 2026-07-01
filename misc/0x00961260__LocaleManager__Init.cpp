// FUNC_NAME: LocaleManager::Init
// Address: 0x00961260
// Role: Initializes locale-related config variables and reads system locale string.

void __fastcall LocaleManager::Init(int thisPtr)
{
    // Initialize base subsystem (likely part of a larger framework)
    InitSubsystem();

    // Register various integer config settings with their keys and default values
    // Offsets relative to thisPtr: +0x58, +0x5c, +0x50, +0x54, +0x64, +0x68, +0x6c, +0x70
    RegisterConfigVar(&g_localeKey1, (int*)(thisPtr + 0x58), 1, 0, 0, 0);
    RegisterConfigVar(&g_localeKey2, (int*)(thisPtr + 0x5c), 1, 0, 0, 0);
    RegisterConfigVar(&g_localeKey3, (int*)(thisPtr + 0x50), 1, 0, 0, 0);
    RegisterConfigVar(&g_localeKey4, (int*)(thisPtr + 0x54), 1, 0, 0, 0);
    RegisterConfigVar(&g_localeKey5, (int*)(thisPtr + 100), 1, 0, 0, 0);    // +0x64
    RegisterConfigVar(&g_localeKey6, (int*)(thisPtr + 0x68), 1, 0, 0, 0);
    RegisterConfigVar(&g_localeKey7, (int*)(thisPtr + 0x6c), 1, 0, 0, 0);
    RegisterConfigVar(&g_localeKey8, (int*)(thisPtr + 0x70), 1, 0, 0, 0);

    // Query system locale for time format string (LOCALE_STIMEFORMAT = 0x5A)
    // LOCALE_USER_DEFAULT = 0x400
    CHAR localeBuffer[16];
    int result = GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_STIMEFORMAT, localeBuffer, sizeof(localeBuffer));
    if (result > 0)
    {
        // Copy the locale format string into the object (offset +0x74)
        strncpy((char*)(thisPtr + 0x74), localeBuffer, sizeof(localeBuffer));
    }
    else
    {
        // Set to empty string if query fails
        *(char*)(thisPtr + 0x74) = '\0';
    }
}