// FUNC_NAME: initializeUnknownArray
// Function at 0x006142d0 initializes a global array of 12-byte structures.
// The array is located at g_arrayBase and spans up to g_endMarker2.
// Each iteration sets a pattern: zero at the previous 4-byte slot, a constant value (g_someValue)
// at the current slot, and zero at the first byte of the following 4-byte slot.
// After the loop, the last two 4-byte locations are set to -1 (0xFFFFFFFF).
// Likely this is an initialization of an array of controller slots, packet windows, or similar.

#include <cstdint>

// Global data pointers (addresses from analysis)
extern uint32_t g_someValue;       // DAT_00e2b1a4
extern uint32_t* g_arrayBase;      // DAT_011f6bbc (treated as start of array of uint32_t triplets)
extern uint32_t g_endMarker1;      // _DAT_011f6be8
extern uint32_t g_endMarker2;      // _DAT_011f6bec

void initializeUnknownArray()
{
    uint32_t* ptr = g_arrayBase;               // start of array
    uint32_t* endPtr = reinterpret_cast<uint32_t*>(0x11f6bec); // exclusive end address

    do {
        // Zero out the 4-byte slot immediately before current pointer
        ptr[-1] = 0;

        // Set current slot to the constant value
        *ptr = g_someValue;

        // Zero the first byte of the next 4-byte slot (purpose unclear)
        *reinterpret_cast<uint8_t*>(ptr + 1) = 0;

        // Advance by 12 bytes (3 uint32_t slots)
        ptr += 3;
    } while (reinterpret_cast<int32_t>(ptr) < reinterpret_cast<int32_t>(endPtr));

    // Overwrite the last two slots with -1 (sentinel values)
    g_endMarker1 = 0xFFFFFFFF;
    g_endMarker2 = 0xFFFFFFFF;
}