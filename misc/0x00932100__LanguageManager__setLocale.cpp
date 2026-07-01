// FUNC_NAME: LanguageManager::setLocale
void __cdecl LanguageManager::setLocale(const char* localeString)
{
    int languageIndex;
    int localeCode;
    int* globalA;
    int* globalB;
    int* globalC;

    globalA = DAT_012234a4; // some global state (maybe LanguageManager singleton)
    localeCode = FUN_00602e60(localeString); // convert locale string to internal code (e.g., hash or enum)
    languageIndex = FUN_00602ff0(localeCode); // get language index from code
    if (languageIndex >= 0) {
        FUN_00604540(languageIndex); // apply language index (load strings, fonts, etc.)
    }
    FUN_00604360(localeString); // set current locale string

    *(uint*)(globalA + 0x4c) |= 1; // set flag: language changed

    FUN_0069c150("Locale", localeCode); // log or broadcast locale change event
    FUN_00698790(); // refresh UI / text

    *(byte*)(DAT_01129a74 + 0x3a3) = 0; // clear some flag (maybe "needsReload" or "firstTime")
    FUN_005a04a0("SetLanguageCode", 0, &DAT_00d8963c, 1, localeCode); // call script function SetLanguageCode

    DAT_00e5672c = 2; // set global language enum to 2 (e.g., LANG_ENGLISH)

    globalB = DAT_01129928; // another global (maybe application state)
    *(int*)(globalB + 0x60) = 0; // reset some timer or state

    if ((DAT_01130590 & 1) == 0) { // if callback not registered yet
        FUN_005c0d50(globalB + 0x14, &LAB_00931e00, 0); // register a repeating callback (maybe "onLocaleChanged")
        DAT_01130590 |= 1; // mark registered
    }
}