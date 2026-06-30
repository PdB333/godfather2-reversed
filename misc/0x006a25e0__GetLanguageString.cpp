// FUNC_NAME: GetLanguageString
// Function address: 0x006a25e0
// Returns a locale string based on an integer language ID (0 = en-us, 1 = cz, 2 = fr-fr)

wchar_t* GetLanguageString(int languageId)
{
    // Array of known language strings (3 entries)
    static wchar_t* localeNames[] = {
        L"en-us",
        L"cz",
        L"fr-fr"
    };

    // Additional data pointers (unused, possibly legacy or debug info)
    // These are not used in the logic but present in the original binary.
    // They may correspond to extended locale tables or debug markers.
    // The pointers are: D5D4AC, D5D4A4, D5D49C, D5D494, D5D48C, D5D484
    // (omitted for clarity)

    // Return the locale string for the given language ID.
    return localeNames[languageId];
}