// FUNC_NAME: GameSettings::applyModeSettings
// Function address: 0x004ecc40
// Applies mode-specific limits and outputs a configuration value.
// Parameters are passed in registers (ESI = mode, EDI = outValue pointer).
void GameSettings::applyModeSettings(int mode, int* outValue)
{
    // Clamp global thresholds
    if (s_maxThreshold < 27) {
        s_maxThreshold = 27;
    }
    if (26 < s_minThreshold) {
        s_minThreshold = 27; // clamp to 27 if above 26
    }
    // Set flag based on mode (mode 3 sets false, others true)
    s_isMultiplayer = (uint)(mode != 3);
    // Call another initialization function (likely applies settings)
    applyConfig(); // FUN_004ec7a0
    // Output default value unless mode is 1 (override to 0)
    *outValue = s_defaultValue;
    if (mode == 1) {
        *outValue = 0;
    }
}