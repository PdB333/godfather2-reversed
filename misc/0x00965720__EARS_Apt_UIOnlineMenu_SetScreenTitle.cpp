// Xbox PDB: EARS_Apt_UIOnlineMenu_SetScreenTitle
// FUNC_NAME: OnlineMenuManager::refreshUI
void __fastcall OnlineMenuManager::refreshUI(int thisPtr)
{
    int iVar1;
    char *pcVar2;
    undefined4 uVar3;
    int localeStringDest[3]; // +0x00: locale string buffer
    code *localeDestructor;   // +0x10: destructor for locale string
    int langStringDest[3];    // +0x00: language string buffer
    code *langDestructor;     // +0x10: destructor for language string

    // Hide online info panel
    FUN_005a04a0("HideOnlineInfo", 0, &DAT_00d8cdec, 0);

    switch (*(undefined4 *)(thisPtr + 0xdc)) // +0xdc: current online menu state
    {
    case 0: // Initial state – show language selection
        // Set title/label text using hash 0x738662cd
        FUN_005c4630(*(undefined4 *)(thisPtr + 0x2b0), 0x80, &PTR_LAB_00d78708, 0x738662cd);
        FUN_004d3bc0(&DAT_00e2f044); // Get current locale code
        // Build locale string (e.g., "fr_CA")
        pcVar2 = "fr_CA";
        FUN_0069be40(localeStringDest, "Locale", langStringDest, "fr_CA");
        iVar1 = FUN_004d4b70(pcVar2); // Check if French Canadian locale
        if (iVar1 == 0) {
            pcVar2 = "ntsc_en"; // Default to English
        }
        else {
            pcVar2 = (char *)FUN_006045b0(); // Get actual locale string
        }
        // Show online info with language string
        FUN_005a04a0("ShowOnlineInfo", 0, &DAT_00d8cdec, 1, pcVar2);
        // Clean up allocated strings
        if (langStringDest[0] != 0) {
            (*langDestructor)(langStringDest[0]);
        }
        if (localeStringDest[0] != 0) {
            (*localeDestructor)(localeStringDest[0]);
        }
        break;

    case 1: // Searching for games
        FUN_005c4630(*(undefined4 *)(thisPtr + 0x2b0), 0x80, &PTR_LAB_00d78708, 0x75e6b21c);
        break;

    case 2: // Connected to match?
    case 3:
        uVar3 = 0xe89837c4;
        goto LAB_009657fc;

    case 5: // In lobby?
        FUN_005c4630(*(undefined4 *)(thisPtr + 0x2b0), 0x80, &PTR_LAB_00d78708, 0x89ae7dc9);
        break;

    case 6: // Match ended?
        uVar3 = 0xcb7f789a;
LAB_009657fc:
        FUN_005c4630(*(undefined4 *)(thisPtr + 0x2b0), 0x80, &PTR_LAB_00d78708, uVar3);
        break;

    case 7: // Disconnected?
        FUN_005c4630(*(undefined4 *)(thisPtr + 0x2b0), 0x80, &PTR_LAB_00d78708, 0x89ae7dc9);
        break;

    case 9: // Custom match lobby
        // Set custom match title text
        FUN_005c4660(*(undefined4 *)(thisPtr + 0x2b0), "$mp_online_custom_match", 0x80, 0);
        *(undefined1 *)(*(int *)(thisPtr + 0x2b0) + 0x7f) = 0; // Null-terminate? +0x7f is likely end of string buffer
        break;
    }

    // Update window title
    FUN_005a04a0("SetTitle", 0, &DAT_00d8cdec, 0);
    return;
}