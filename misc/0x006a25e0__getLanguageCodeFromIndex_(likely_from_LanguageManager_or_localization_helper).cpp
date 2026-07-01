// FUNC_NAME: getLanguageCodeFromIndex (likely from LanguageManager or localization helper)
wchar_t* __cdecl getLanguageCodeFromIndex(int languageIndex) {
    // Array of 9 language code strings (index 0-8)
    // Index 0-2: en-us, cz, fr-fr
    // Index 3-8: pointers to additional language strings stored at data addresses
    wchar_t* languageTable[] = {
        L"en-us",
        L"cz",
        L"fr-fr",
        // The following 6 entries are retrieved from static data pointers:
        (wchar_t*)0x00d5d4ac,  // PTR_DAT_00d5d4ac
        (wchar_t*)0x00d5d4a4,  // DAT_00d5d4a4
        (wchar_t*)0x00d5d49c,  // DAT_00d5d49c
        (wchar_t*)0x00d5d494,  // DAT_00d5d494
        (wchar_t*)0x00d5d48c,  // DAT_00d5d48c
        (wchar_t*)0x00d5d484   // DAT_00d5d484
    };
    return languageTable[languageIndex];
}