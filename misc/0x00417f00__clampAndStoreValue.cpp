// FUNC_NAME: clampAndStoreValue
// Function at 0x00417f00: Clamps two global thresholds and stores a 4-byte combined value.
void clampAndStoreValue(byte param_4, byte param_1, byte param_2, byte param_3)
{
    // Clamp g_minThreshold to at least 0xC1 (193)
    if (g_minThreshold < 0xC1) {
        g_minThreshold = 0xC1;
    }

    // Combine four bytes into a 32-bit value: param_4 (MSB), param_1, param_2, param_3 (LSB)
    g_combinedValue = ((uint32_t)param_4 << 24) | ((uint32_t)param_1 << 16) | ((uint32_t)param_2 << 8) | param_3;

    // Clamp g_maxThreshold to at most 0xC1 (if it exceeds 0xC0)
    if (g_maxThreshold > 0xC0) {
        g_maxThreshold = 0xC1;
    }
}