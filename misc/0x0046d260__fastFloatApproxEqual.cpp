// FUNC_NAME: fastFloatApproxEqual
bool fastFloatApproxEqual(float a, float b)
{
    // Compare floats using integer bitmask to approximate within epsilon.
    // Mask is typically 0x7FFFFFFF for absolute value of difference bits.
    extern const uint32_t g_floatDiffMask;   // +0x00: bitmask for difference
    extern const float g_floatEpsilonThreshold; // +0x00: threshold (e.g., 0.0001f)

    uint32_t diff = reinterpret_cast<uint32_t>(a - b); // Get IEEE 754 bits of float difference
    return static_cast<float>(diff & g_floatDiffMask) <= g_floatEpsilonThreshold;
}