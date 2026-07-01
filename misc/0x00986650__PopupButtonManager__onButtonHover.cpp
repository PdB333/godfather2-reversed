// FUNC_NAME: PopupButtonManager::onButtonHover

char PopupButtonManager::onButtonHover(const char* buttonPath) {
    char result = '\0';
    int buttonIndex = 0;
    char formattedPath[64];

    do {
        if (buttonIndex > 1) {
            return result;
        }

        // Build path like "/spop/popup_root/popup/button_0/button" or "_1"
        formatString(formattedPath, sizeof(formattedPath), "/spop/popup_root/popup/button_%d/button", buttonIndex);

        // Compare the incoming path with the formatted path
        if (strcmp(formattedPath, buttonPath) == 0) {
            // Construct the rollover button path as "popup/button_%d/state"
            formatString(formattedPath, sizeof(formattedPath), sPopupButtonRolloverPath, buttonIndex);

            // Create a RollOverButton with an ID based on the path
            createRollOverButton("RollOverButton", 0, sDefaultButtonStyle, 1, formattedPath);

            // Initialize some structure with the global data (likely input context)
            ButtonInitData initData;
            initData.field0 = gGlobalButtonContext;
            initData.field4 = 0;
            initData.flags = 0;
            initializeButton(&initData, 0);

            result = '\x01';
        }

        buttonIndex++;
        if (result != '\0') {
            return result;
        }
    } while (true);

    return result;
}