// FUNC_NAME: GameSettings::getOptionByIndex
// Address: 0x005e5700
// Role: Retrieves a uint value from a global game settings structure using an index (always 0 in this case).
// Calls GetSettingByIndex (0x005f0600) with a global pointer and a reference to a byte index.
// Returns the first uint if pointer is valid, otherwise 0.

#include <cstdint>

uint32_t GameSettings::getOptionByIndex(void)
{
    uint32_t *pSetting;
    uint8_t index = 0;

    // DAT_01223514 is likely a global pointer to the game settings manager or array.
    // FUN_005f0600 is GetSettingByIndex which returns a pointer to the setting value.
    pSetting = (uint32_t *)GetSettingByIndex(g_pGameSettings, &index);

    if (pSetting != nullptr)
    {
        return *pSetting;
    }
    return 0;
}