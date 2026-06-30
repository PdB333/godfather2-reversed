// FUNC_NAME: UnknownClass::setCheckAgainstGlobalThreshold
void __thiscall UnknownClass::setCheckAgainstGlobalThreshold(float param_2, int param_3)
{
    // Global threshold value (float) at 0x00d577a0
    float globalThreshold = *(float*)0x00d577a0;  // _DAT_00d577a0

    // If the provided value exceeds the global threshold, set a flag at offset +0x3c
    // Flag bit 2 (0x4) likely indicates "exceeded limit" or "active highlight"
    if (globalThreshold < param_2)
    {
        *(unsigned short*)(this + 0x3c) |= 4;  // Set bit 2 in word at +0x3c
    }

    // Store the third parameter at offset +0x2c (likely an enum or handle)
    *(int*)(this + 0x2c) = param_3;

    return;
}