// FUNC_NAME: clampSettingsAndStoreInput
void __cdecl clampSettingsAndStoreInput(uint8 inputValue)
{
    // DAT_012058d0: global minimum limit (enforced >= 27)
    if (g_minLimit < 27)
    {
        g_minLimit = 27;
    }

    // DAT_00f15988: global maximum cap (clamped to 27 if > 26)
    if (g_maxLimit > 26)
    {
        g_maxLimit = 27;
        // _DAT_011f3a44: stored input value
        g_storedInput = inputValue;
        return;
    }

    g_storedInput = inputValue;
}