// FUNC_NAME: MultiplayerOnlineMenu::setYesNoText
// Function address: 0x0095c310
// Role: Sets the localized text on a UI element based on a boolean flag (likely "yes"/"no" for online multiplayer menu).
void __thiscall MultiplayerOnlineMenu::setYesNoText(void *uiTextElement) {
    // +0x4c: bool m_isOnline - flag indicating online state
    char *textString;
    
    if (*(char *)(this + 0x4c) == '\0') {
        textString = "$mp_online_menu_no";
    } else {
        textString = "$mp_online_menu_yes";
    }
    
    // Sets the text on the given UI control (likely a text field or label)
    // Parameters: uiTextElement, string, maxLength=0x80, flags=0
    setLocalizedText(uiTextElement, textString, 0x80, 0);
}