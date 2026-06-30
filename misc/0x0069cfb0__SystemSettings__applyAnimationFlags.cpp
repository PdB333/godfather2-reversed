// FUNC_NAME: SystemSettings::applyAnimationFlags

void __cdecl applyAnimationFlags(void)
{
    // Global animation settings structure (24 bytes) stored at 0x00e50b54
    // Layout:
    // +0x00: uint64_t field_0 (lower 4 bytes at 0x00e50b54, upper 4 bytes at 0x00e50b58)
    // +0x08: uint64_t field_1 (0x00e50b5c)
    // +0x10: uint64_t field_2 (0x00e50b64)

    struct AnimationSettings {
        uint32_t lowPart;   // +0x00
        uint32_t highPart;  // +0x04
        uint64_t field_08;  // +0x08
        uint64_t field_10;  // +0x10
    };

    // Pointers to the global data (assumes they are defined externally)
    extern uint32_t g_animLow;
    extern uint32_t g_animHigh;
    extern uint64_t g_animField08;
    extern uint64_t g_animField10;

    AnimationSettings localBuf;
    localBuf.field_08 = g_animField08;
    localBuf.field_10 = g_animField10;

    // Check bit 0 of the high part of field_0 (initialization flag)
    if ((g_animHigh & 1) == 0)
    {
        // Combine low and high into a 64-bit value, then clear bits 2 and 3 of the upper 32 bits
        uint64_t combined = ((uint64_t)g_animHigh << 32) | g_animLow;
        combined &= 0xfffffff3ffffffffULL; // clears bits 34 and 35 (or bits 2 and 3 of high dword)

        localBuf.lowPart = (uint32_t)(combined & 0xFFFFFFFF);
        localBuf.highPart = (uint32_t)(combined >> 32);

        // Apply system-wide animation parameters via SystemParametersInfoA
        // Action 0x33 = SPI_SET?? (likely custom or game-specific animation action)
        // uiParam = 0x18 (24 bytes) = size of the data buffer
        SystemParametersInfoA(0x33, 0x18, &localBuf, 0);
    }
}