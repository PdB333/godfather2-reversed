// FUNC_NAME: SomeClass::findThresholdEntry
// Function address: 0x00784e10
// Selects an entry from one of two threshold tables based on a computed scaling factor.
// param_1: this pointer (object with threshold tables at +0xa8 and +0xe4)
// param_2: input object with factor at +0x20 and flags at +0x2c
// Returns pointer to entry data (4 bytes after threshold) if found, otherwise 0.

void* __thiscall SomeClass::findThresholdEntry(int thisPtr, int inputObj)
{
    float computedScale;
    float* thresholds;
    int baseOffset;
    uint flags;

    // Compute max of two values at +0x58 and +0x5c
    float maxVal = *(float*)(thisPtr + 0x58);           // +0x58: first limit
    float secondVal = *(float*)(thisPtr + 0x5c);        // +0x5c: second limit
    if (maxVal <= secondVal)
        maxVal = secondVal;

    // Compute scaled value: (input factor / maxVal) * global constant
    float inputFactor = *(float*)(inputObj + 0x20);     // +0x20: some factor
    computedScale = (inputFactor / maxVal) * DAT_00d5e288;  // global scaling constant

    // Clamp computedScale to [0.0, DAT_00d5e288]
    if (computedScale > 0.0f) {
        if (computedScale >= DAT_00d5e288)
            computedScale = DAT_00d5e288;
    } else {
        computedScale = 0.0f;
    }

    // Check bit 1 of flags at +0x2c to select table A or B
    flags = *(uint*)(inputObj + 0x2c);                  // +0x2c: bitfield flag
    if ((flags >> 1) & 1) {
        // Table A: thresholds at +0xa8, data at +0xac, stride 0x14 (5 floats)
        thresholds = (float*)(thisPtr + 0xa8);
        baseOffset = 0xac;                              // +0xac: first data entry
        for (int i = 0; i < 3; i++) {
            if (computedScale <= thresholds[i * 5])     // each entry has 5 floats (0x14 bytes)
                return (void*)(thisPtr + baseOffset + i * 0x14);
        }
    } else {
        // Table B: thresholds at +0xe4, data at +0xe8, stride 0x14
        thresholds = (float*)(thisPtr + 0xe4);
        baseOffset = 0xe8;                              // +0xe8: first data entry
        for (int i = 0; i < 3; i++) {
            if (computedScale <= thresholds[i * 5])
                return (void*)(thisPtr + baseOffset + i * 0x14);
        }
    }

    return 0;  // No matching threshold found
}