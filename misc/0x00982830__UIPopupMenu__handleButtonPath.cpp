// FUNC_NAME: UIPopupMenu::handleButtonPath
bool __thiscall UIPopupMenu::handleButtonPath(int this, const char* pathStr) {
    char buffer[64];
    bool matched = true;
    int i;

    // Check if the path is exactly the default button path
    const char* defaultPath = "/ppop/button/button";
    for (i = 0x14; i > 0; i--) {
        if (*defaultPath != *pathStr) {
            matched = false;
            break;
        }
        if (*defaultPath == '\0') break;
        defaultPath++;
        pathStr++;
    }
    if (matched) {
        // Roll out the default button
        UI::applyAction("RollOutDefaultButton", 0, gUIContext, 0);
    }

    unsigned int buttonIndex = 0;
    if (!matched) {
        do {
            if (buttonIndex > 3) {
                return matched;
            }
            // Build the path for a specific popup button: /ppop/popup_root/popup_%d/button_%d/button
            UI::formatString(buffer, "/ppop/popup_root/popup_%d/button_%d/button",
                             *(int*)(this + 0x6c) - 1, buttonIndex);
            // Compare the constructed path with the given path
            int cmp = strcmp(buffer, pathStr);
            if (cmp == 0) {
                // Build a shorter path (without trailing /button) for the roll-out action
                UI::formatString(buffer, "/ppop/popup_root/popup_%d/button_%d", buttonIndex);
                UI::applyAction("RollOutButton", 0, gUIContext, 1, buffer);
                matched = true;
            }
            buttonIndex++;
        } while (!matched);
    }
    return matched;
}