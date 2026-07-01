// FUNC_NAME: initializeLanguageInfo
wchar_t* __fastcall initializeLanguageInfo(wchar_t* localeBuffer)
{
    // Clear the language ID region (offsets 0x40 to 0x53 in wchar_t units)
    for (int i = 0; i < 20; i++) {
        localeBuffer[0x40 + i] = L'\0';
    }

    // Copy culture name (e.g., "godfather2_na") into offset 0x00 (size 0x20 wchar_t)
    _wcsncpy_s(localeBuffer, 0x20, L"godfather2_na", 0x20);
    // Copy locale (e.g., "en-us") into offset 0x20 (size 0x20 wchar_t)
    _wcsncpy_s(localeBuffer + 0x20, 0x20, L"en-us", 0x20);

    // Retrieve a 16-byte language identifier from an external function
    uint64_t languageId[2];
    uint64_t* langIdPtr = (uint64_t*)FUN_006a2490((wchar_t*)languageId); // called with a local buffer? Actually the decompiled shows local_10 [16] passed; the function likely returns a pointer to a static or another buffer.

    // Copy the two 8-byte values into the locale buffer at offset 0x40
    *(uint64_t*)(localeBuffer + 0x40) = langIdPtr[0];
    *(uint64_t*)(localeBuffer + 0x44) = langIdPtr[1];

    return localeBuffer;
}