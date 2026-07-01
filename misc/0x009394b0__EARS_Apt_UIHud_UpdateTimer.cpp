// Xbox PDB: EARS_Apt_UIHud_UpdateTimer
// FUNC_NAME: TimerDisplay::showTimerText
// Function address: 0x009394b0
// Role: Updates the on-screen timer display text and visibility based on provided string and timer enable flag.

void __thiscall TimerDisplay::showTimerText(char* text, char* defaultText)
{
    // +0x48: m_bTimerEnabled (bool) - indicates if the timer is active/enabled
    if (!m_bTimerEnabled) {
        return;
    }

    // +0x6c: m_pTimerText (char*) - stores the current timer text string
    m_pTimerText = text;

    if (text != NULL && *text != '\0') {
        // Use default text if none provided (defaultText typically points to a global string constant)
        if (defaultText == NULL) {
            defaultText = (char*)0x00e2f044; // &DAT_00e2f044: default timer text
        }

        // Show timer via UI event system
        // Parameters: event name "ShowTimer", unknown flags, event type constant (0x00d8a64c), visibility flag (1), and the text
        FUN_005a04a0("ShowTimer", 0, (void*)0x00d8a64c, 1, defaultText);

        m_pTimerText = NULL;
        return;
    }

    // Hide timer when text is empty or null
    FUN_005a04a0("HideTimer", 0, (void*)0x00d8a64c, 0);// Hide with visibility 0

    m_pTimerText = NULL;
}