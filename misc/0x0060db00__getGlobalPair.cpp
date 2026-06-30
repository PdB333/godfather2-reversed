// FUNC_NAME: getGlobalPair
// Address: 0x0060db00
// Role: Returns a pair of DWORDs from a global table indexed by parameter (param_1 * 2).
// The first value is returned directly; if param_2 is non-null, the second value is written there.

uint32_t getGlobalPair(int index, uint32_t *secondOut) {
    // Global arrays: each entry is 8 bytes (two DWORDs)
    // &DAT_011f38f0 is the base of the first array
    // &DAT_011f38f4 is the base of the second array (offset by 4)
    extern uint32_t globalTableFirst[];   // address 0x011f38f0
    extern uint32_t globalTableSecond[];  // address 0x011f38f4

    if (secondOut != nullptr) {
        *secondOut = globalTableSecond[index * 2];  // note: index*2 for each array? Actually both arrays are accessed with same index*2 offset.
        // The original C uses (&DAT_011f38f4)[param_1 * 2]; that implies DAT_011f38f4 is a pointer to a DWORD array, so it's indexing by (param_1*2) elements.
        // Similarly for the other.
    }
    return globalTableFirst[index * 2];
}