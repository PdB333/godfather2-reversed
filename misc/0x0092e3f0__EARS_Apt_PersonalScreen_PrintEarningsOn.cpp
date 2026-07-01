// Xbox PDB: EARS_Apt_PersonalScreen_PrintEarningsOn
// FUNC_NAME: MPOnlineDonLobbyScreen::populateTitleTexts
void __thiscall MPOnlineDonLobbyScreen::populateTitleTexts(int titleBuffer, int subtitleBuffer) {
    wchar_t* localizedString = nullptr; // +0x00 output from resource fetch
    int flag = 0;                       // +0x04 unknown flag
    int reserved = 0;                   // +0x08
    void (*deallocator)(wchar_t*) = nullptr; // +0x0c function pointer for freeing string

    // Fetch the localized string from resource manager; first argument is this->resourceId (at +0x00)
    // The function likely stores the allocated string in localizedString and the deallocator in deallocator.
    FUN_00604000(*(int*)this, &localizedString, 1);

    // Copy the fixed title key to output buffer 1 (titleBuffer is a char* of length 128)
    FUN_005c4660(titleBuffer, "$mp_online_donlobby_title_earnings", 0x80, 0);

    // Choose actual localized text or default fallback (address DAT_0120546e)
    const wchar_t* text = (localizedString != nullptr) ? localizedString : L"DefaultFallbackString";
    // Copy the text to output buffer 2 (subtitleBuffer)
    FUN_005c4660(subtitleBuffer, text, 0x80, 0);

    // Free the allocated string using the callback pointer (deallocator)
    if (localizedString != nullptr) {
        deallocator(localizedString);
    }
}