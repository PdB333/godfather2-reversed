// Xbox PDB: EARS_Apt_LobbyParams_PrintShortDonModeOn
// FUNC_NAME: OnlineMenuOption::setShortYesNoText

// Function address: 0x0095c2e0
// Role: Sets a short yes/no localized string on a UI element based on a boolean flag at +0x4c.

class OnlineMenuOption {
public:
    // +0x4c: bool m_isOnlineEnabled; // Whether online play is enabled

    // __thiscall
    void setShortYesNoText(UIElement *element) {
        const char *key;
        if (m_isOnlineEnabled) {
            key = "$mp_online_menu_short_yes";
        } else {
            key = "$mp_online_menu_short_no";
        }
        // Set localized text on the UI element
        SetLocalizedString(element, key, 0x80, 0); // maxLen=0x80, flags=0
    }
};