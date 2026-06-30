// FUN_004ab0a0: mapInputIndexToActionCode
// Returns a predefined action code based on an input index (0-4).
// The index is passed in EAX; if out of range ( >4 ), defaults to 0.
// Action codes: 0xC003, 0xC001, 0xC002, 0x4003, 0x8003
// Likely used to map controller input types (e.g., button combos) to internal action flags.
uint32_t mapInputIndexToActionCode(uint32_t index)
{
    static const uint32_t actionTable[5] = {
        0xC003, // index 0
        0xC001, // index 1
        0xC002, // index 2
        0x4003, // index 3
        0x8003  // index 4
    };
    if (index > 4) {
        index = 0;
    }
    return actionTable[index];
}