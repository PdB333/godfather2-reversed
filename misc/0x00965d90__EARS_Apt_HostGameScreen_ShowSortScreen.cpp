// Xbox PDB: EARS_Apt_HostGameScreen_ShowSortScreen
// FUNC_NAME: DonLobbyScreen::setupLabelTexts
void DonLobbyScreen::setupLabelTexts(void)
{
    // Global pointer to DonLobbyScreen instance (singleton)
    int *pVtablePtr = DAT_01130048;  // pointer to vtable or class instance

    // Retrieve localized strings for the lobby UI elements
    char *sortMethodStr = getLocalizedText("$mp_online_sort_method");
    // The following call likely extracts a UI element ID from the string
    int uiElementId[3];
    convertStringToUIElement(sortMethodStr, uiElementId);
    if (uiElementId[0] != 0) {
        // If the element exists, call a function to set it (e.g., setSortMethod)
        // The function pointer is likely stored in a register or from a table
        // This is a workaround for the decompiler's jumptable issue.
        (*(void (*)(int)) (&uiElementId))(uiElementId[0]);  // Likely a callback
    }

    // Set default sort method index (7)
    setLobbySortMethod(7);

    // Set the four column titles
    char *statusStr = getLocalizedText("$mp_online_donlobby_title_status");
    setTitleLabel(0, statusStr);

    char *hostStr = getLocalizedText("$mp_online_donlobby_title_host");
    setTitleLabel(1, hostStr);

    char *matchesStr = getLocalizedText("$mp_online_donlobby_title_matches");
    setTitleLabel(2, matchesStr);

    char *respectStr = getLocalizedText("$mp_online_donlobby_title_respect");
    setTitleLabel(3, respectStr);

    // Call a virtual method (offset 0x28) to refresh/render the screen
    (*(void (**)(void))(*pVtablePtr + 0x28))();
}