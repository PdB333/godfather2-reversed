// FUNC_NAME: TutorialUI::handleButtonClick
bool __thiscall TutorialUI::handleButtonClick(const char* buttonId)
{
    // Check if buttonId matches the rollover button path
    if (strcmp(buttonId, "/tuto/buttons/button_2/button") == 0) {
        // Fire rollover button event
        triggerUIEvent("RollOverButton", 0, (void*)0x00d91b68, 1, (void*)0x00d796d4);
        // Send notification with some global data
        undefined4 local4c = g_notificationData; // DAT_011302b0
        undefined4 local48 = 0;
        undefined1  local44 = 0;
        sendNotification(&local4c, 0);
        return true;
    }

    // Look through menu items for a match
    for (int i = 0; i < m_itemCount; i++) {
        char itemPath[64];
        formatString(itemPath, sizeof(itemPath), "/tuto/mainmenu/menu/item_%d/menu_item/item", i);
        if (strcmp(itemPath, buttonId) == 0) {
            // Build the switch item path
            char switchPath[64];
            formatString(switchPath, sizeof(switchPath), (const char*)0x00e3266c, i);
            // Fire switch item event
            triggerUIEvent("SwitchItem", 0, (void*)0x00d91b68, 1, switchPath);
            // Send notification
            undefined4 local4c = g_notificationData; // DAT_011302b0
            undefined4 local48 = 0;
            undefined1  local44 = 0;
            sendNotification(&local4c, 0);
            return true;
        }
    }
    return false;
}