// FUNC_NAME: setGlobalIndexedValue
extern unsigned char g_gameMode; // 0x011a0f28, flags for input mode? (0x04 = something)
extern int g_indexedValueArray[]; // 0x011d912c, array of values indexed by some ID

void __cdecl setGlobalIndexedValue(unsigned int value, int index)
{
    // Clamp -1 to 0xFFF (4095) - likely an invalid/uninitialized sentinel
    if (value == 0xFFFFFFFF) {
        value = 0xFFF;
    }
    // If value is 0 and the global mode is not 4, allow it anyway (seems both paths do the same)
    if (value == 0) {
        if (g_gameMode != 0x04) {
            goto storeValue;
        }
    } else if (value > 0xFFF) {
        // Values above 4095 are also allowed (no clamp) - seems like a bug or intentional passthrough
        goto storeValue;
    }
    // Call helper (possibly a lock/check function)
    FUN_00618d40();
    g_indexedValueArray[index] = value;
    return;

storeValue:
    FUN_00618d40();
    g_indexedValueArray[index] = value;
    return;
}