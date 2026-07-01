// FUNC_NAME: CSAButton::checkAndHideButton
// Function address: 0x00983ef0
// Role: Checks if a given button name matches the CSA button string, and if so, hides the CSA button and clears its internal handle.

// Global pointer to CSA system data (e.g., a singleton managing context-sensitive actions)
extern void* g_pCSASystem; // DAT_01130010

// External string constant: "scrb_csa_button_button"
extern const char* g_szCSAButtonName; // PTR_s__scrb_csa_button_button_00e575ec

// Forward declarations of helper functions
void FUN_005bf350(uint32_t handle); // Hides/releases the CSA button (likely button hide or release)
void FUN_005a04a0(const char* eventName, int32_t param2, uint32_t param3, int32_t param4); // Sends "HideCSAButton" event

bool __thiscall CSAButton::checkAndHideButton(byte* buttonName)
{
    bool bMatch = false;
    const char* pszTarget = g_szCSAButtonName;

    // Only proceed if CSA is globally enabled (offset +100 of global CSA data is zero)
    if (*(char*)((uint8_t*)g_pCSASystem + 0x64) == '\0')
    {
        // Compare buttonName against the known CSA button string
        do
        {
            byte c1 = *buttonName;
            byte c2 = *pszTarget;
            if (c1 != c2) goto compare_result;
            if (c1 == '\0') break;
            c1 = buttonName[1];
            c2 = pszTarget[1];
            if (c1 != c2) goto compare_result;
            buttonName += 2;
            pszTarget += 2;
        } while (c1 != '\0');

        // Strings are equal; set match flag
        bMatch = true;
        goto check_match;

    compare_result:
        // Determine which string is greater (not needed for equality check)
        // The code originally computed a comparison result but only uses it for equality.
        // For clarity, we skip the comparison and just detect inequality.
        bMatch = false;

    check_match:
        if (bMatch)
        {
            // Hide the CSA button using its stored handle (offset +0x108 from this)
            FUN_005bf350(*(uint32_t*)((uint8_t*)this + 0x108)); // +0x108: m_hCSAButtonHandle (handle to CSA button)

            // Send "HideCSAButton" message to hide the button
            FUN_005a04a0("HideCSAButton", 0, &DAT_00d77dc0, 0);

            // Reset the handle to invalid (-1)
            *(uint32_t*)((uint8_t*)this + 0x108) = 0xFFFFFFFF;
        }
    }

    return bMatch;
}