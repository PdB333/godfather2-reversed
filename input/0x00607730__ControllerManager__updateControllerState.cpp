// FUNC_NAME: ControllerManager::updateControllerState
// Address: 0x00607730
// Role: Updates the current controller input state and detects changes.

void __thiscall ControllerManager::updateControllerState(short inputValue, short param1, uint16_t param2, uint8_t param3, uint8_t param4)
{
    // Global state variables (likely in .data section)
    static short g_prevInputValue;   // DAT_0120587c
    static short g_prevParam1;       // DAT_01205880
    static int g_inputUnchanged;     // DAT_01205764 (flag, 0 = changed)
    static short g_currentInputValue; // DAT_011a0f24
    static short g_currentParam1;     // DAT_0119da5c
    static uint8_t g_currentParam3;   // DAT_0119474a
    static uint16_t g_currentParam2;  // DAT_011d97e8
    static uint8_t g_currentParam4;   // DAT_0119474b
    static int g_inputValid;          // DAT_01205763

    // Check if the primary input values have changed
    if (g_prevInputValue != inputValue || g_prevParam1 != param1) {
        g_inputUnchanged = 0;  // Clear the "unchanged" flag
        g_prevInputValue = inputValue;
        g_prevParam1 = param1;
    }
    // Store the current input state
    g_currentInputValue = inputValue;
    g_currentParam1 = param1;
    g_currentParam2 = param2;
    g_currentParam3 = param3;
    g_currentParam4 = param4;
    g_inputValid = 1;  // Mark input as valid
}