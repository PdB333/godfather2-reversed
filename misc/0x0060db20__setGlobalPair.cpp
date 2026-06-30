// FUNC_NAME: setGlobalPair
// Function address: 0x0060db20
// Role: Sets a pair of values in a global array at index param1, saving old values and calling update function with them.
// The global array is at 0x011f38f0, each entry is 8 bytes (two 32-bit values). param1 is the entry index.
// Called from many places to modify global state and propagate changes (e.g., audio, controller, or game settings).

void setGlobalPair(int index, int32_t newValue1, int32_t newValue2)
{
    // Global array of pairs. Offsets: index*8 +0 (value1), +4 (value2)
    // Using int32_t as placeholder; actual type may be float, uint32_t, etc.
    extern int32_t g_globalPairArray[]; // at 0x011f38f0

    // Save old values
    int32_t oldValue1 = g_globalPairArray[index * 2];
    int32_t oldValue2 = g_globalPairArray[index * 2 + 1];

    // Set new values
    g_globalPairArray[index * 2] = newValue1;
    g_globalPairArray[index * 2 + 1] = newValue2;

    // Call update/notify with index and old values
    FUN_00609340(index, oldValue1, oldValue2);
    // FUN_00609340 likely handles side effects or updates dependent systems.
}