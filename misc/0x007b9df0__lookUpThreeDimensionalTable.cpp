// FUNC_NAME: lookUpThreeDimensionalTable
// Function address: 0x007b9df0
// Role: Accesses a 60x5x5 table of int32 values at global address DAT_00d6c430.
// Returns the value at (param_1, param_2, param_3) if indices are within bounds, otherwise 0.
// The table is likely used for some game logic (e.g., crime severity, reputation, etc.)

#include <cstdint>

static int32_t lookUpThreeDimensionalTable(uint8_t index1, uint8_t index2, uint32_t index3) {
    // Bounds check: index1 < 60, index2 < 5, index3 < 5
    if (index1 >= 0x3C || index2 >= 5 || index3 >= 5) {
        return 0;
    }

    // Flattened index calculation:
    // index = index3 + 5 * (index2 + 5 * index1)
    // Each element is 4 bytes (int32)
    uint32_t flatIndex = index3 + 5 * (index2 + 5 * index1);
    int32_t* table = reinterpret_cast<int32_t*>(0x00d6c430); // Global table base
    return table[flatIndex];
}