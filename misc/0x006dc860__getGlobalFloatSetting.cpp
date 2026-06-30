// FUNC_NAME: getGlobalFloatSetting
// Function address: 0x006dc860
// Role: Returns a global float value from a fixed memory address.
// This may be a game-wide parameter (e.g., time scale, difficulty multiplier).
float getGlobalFloatSetting(void)
{
    // Read 4-byte floating-point value from global data at 0x00d5ef88
    return *(float*)0x00d5ef88;
}