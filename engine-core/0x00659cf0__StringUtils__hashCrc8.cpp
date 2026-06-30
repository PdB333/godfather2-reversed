// FUNC_NAME: StringUtils::hashCrc8
// Address: 0x00659cf0
// This function computes an 8-bit CRC-like hash of a string with a maximum length limit.
// It uses a precomputed table at DAT_01203640, initialized by FUN_00659c80 if the global flag DAT_00f0ccb7 is set.

#include <cstdint>

namespace StringUtils {

// Global flag indicating whether the CRC table has been initialized (DAT_00f0ccb7)
static bool s_tableInitialized = false;

// Precomputed CRC table (256 bytes, DAT_01203640)
static uint8_t s_crcTable[256];

// Initialization routine for the CRC table (FUN_00659c80, not shown)
static void initCrcTable() {
    // Implemented elsewhere; fills s_crcTable with values for a custom CRC-8 polynomial.
}

/**
 * Compute a CRC-like hash of the given string, processing at most 'maxLen' characters.
 * 
 * @param maxLen Maximum number of characters to hash (0 disables early termination).
 * @param str    Null-terminated input string.
 * @return       32-bit hash value.
 */
uint32_t __fastcall hashCrc8(int maxLen, const char* str) {
    // One-time table initialization
    if (!s_tableInitialized) {
        initCrcTable();
        s_tableInitialized = true;
    }

    uint32_t hash = 0;
    char c = *str;

    while (c != '\0') {
        str++; // Advance past the current character

        if (maxLen == 0) {
            break; // Stop if the maximum length has been consumed (maxLen was decremented after processing)
        }

        // hash = hash * 2 XOR table[current character]
        hash = (hash << 1) ^ s_crcTable[static_cast<uint8_t>(c)];

        // Read the next character and decrement the length counter
        c = *str;
        maxLen--;
    }

    return hash;
}

} // namespace StringUtils