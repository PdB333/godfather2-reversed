// FUNC_NAME: UISoundManager::handleButtonRollOut
// Address: 0x0092d880
// Checks if a button name (wide string) matches one of four special roll‑out button names.
// If a match is found, plays a UI sound event for the roll‑out action.

#include <cstdint>

// Global table of four wide‑string button names (offsets 0, 4, 8, 12 bytes)
extern const wchar_t* g_rollOutButtonNames[4];                            // +0x01130514

// Global variable used as parameter to the sound event function (unknown type)
extern void* g_soundRollOutParam;                                        // +0x00d88e88

// Forward declaration of UI sound event function
void UISoundManager::playUIEvent(const char* eventName, int param2, void* param3, int param4,
                                 const char* soundPath);

void __thiscall handleButtonRollOut(const wchar_t* buttonName)
{
    bool bSoundPlayed = false;
    int32_t byteOffset = 0;                                               // offset into table (4‑byte entries)

    while (true)
    {
        // Table has 4 entries, byte offsets 0,4,8,12.
        if (byteOffset > 12)
            return;

        // Fetch current special button name pointer
        const wchar_t* specialName = *(const wchar_t**)((int)&g_rollOutButtonNames + byteOffset);

        // Compare wide strings (2‑byte characters)
        const wchar_t* pSpecial = specialName;
        const wchar_t* pButton = buttonName;

        while (true)
        {
            wchar_t cSpecial = *pSpecial;
            wchar_t cButton = *pButton;

            if (cSpecial < cButton)
                break;                                                    // not equal
            if (cSpecial > cButton)
                break;                                                    // not equal
            if (cSpecial == L'\0')                                        // both strings ended
            {
                // Match found → play roll‑out sound
                UISoundManager::playUIEvent("RollOutButton",
                                            0,                           // unknown param
                                            &g_soundRollOutParam,
                                            1,                           // flag
                                            "finl_mcMain_button_0_button");
                bSoundPlayed = true;
                break;
            }
            pSpecial++;
            pButton++;
        }

        if (bSoundPlayed)
            return;

        byteOffset += 4;                                                  // next entry (4 bytes per pointer)
    }
}