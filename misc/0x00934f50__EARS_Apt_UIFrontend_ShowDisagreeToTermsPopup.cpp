// Xbox PDB: EARS_Apt_UIFrontend_ShowDisagreeToTermsPopup
// FUNC_NAME: OnlineManager::handleTermsOfServiceResponse

void OnlineManager::handleTermsOfServiceResponse(bool accepted) {
    int screenObj;

    if (accepted) {
        acceptOnlineTerms();
        return;
    }

    // Player disagreed or terms not yet shown
    if (*(char*)(g_pOnlineManager + 0x58) == '\0') {
        // Terms not yet agreed to; player explicitly disagreed
        g_onlineFlags |= 0x80; // Mark that terms were rejected
        setOnlineInterfaceState(0); // Disable online interface
        showLoadingScreen(0); // Hide loading
        acceptOnlineTerms(); // Still call accept? Possibly to dismiss dialog

        // Allocate a screen object (size 0xF0)
        screenObj = (int)operatorNew(0xF0);
        if (screenObj == 0) {
            screenObj = 0;
        } else {
            // Initialize a "disagreed to terms" screen
            screenObj = (int)constructTermsScreen(0);
        }

        setDisplayMessage("$mp_online_disagreed_to_terms");
        *(int*)(screenObj + 0x0C) = 0xB; // Screen type or state
        displayScreen(1); // Show the screen
        *(void**)(screenObj + 0x14) = &LAB_00932770; // Set vtable or callback table
        updateScreenUI();
        return;
    }

    // Terms already agreed (or being processed), enable online
    setOnlineInterfaceState(1);
    int connectionState = *(int*)(g_pOnlineManager + 0x54);

    switch (connectionState) {
        case 1:
            startConnection(1);
            break;
        case 2:
            startMatchmaking(1);
            break;
        case 3:
            startConnection(1);
            startMatchmaking(1);
            break;
        default:
            break;
    }

    // Set up a timer or transition state
    g_pUIManager = g_pOnlineManager; // Possibly reassign
    g_someGlobal = 0xC; // Timer value
    *(int*)(g_pUIManager + 0x60) = 0; // Clear some field

    // Register a callback for when terms are accepted
    if ((g_onlineFlags & 1) == 0) {
        registerCallback((void*)(screenObj + 0x14), &LAB_00931e00, 0);
        g_onlineFlags |= 1;
    }
}