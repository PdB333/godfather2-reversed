// FUNC_NAME: StringTable::lookupEntry
// Address: 0x005bc0f0
// Role: Looks up a string in a hash table by category and returns a pointer to the matching entry (pair of pointers).
// The hash table uses a two-level indexing: a primary hash (from string) indexes into a short table; positive values are direct indices into a string table,
// negative values indicate a chain of entries to compare.

#include <cstdint>

// Forward declaration of hash function (likely computes a hash of the string)
extern uint32_t hashString(const char* str);

// Global tables (offsets from decompiled references)
// DAT_01129558: array of shorts (0x107 entries?) - hash index table
extern int16_t g_hashIndexTable[]; // each entry is 2 bytes
// PTR_DAT_011291d8: array of pointer pairs (8 bytes each) - string table
extern const char** g_stringTable; // actually an array of pairs of pointers

// Function: looks up a string in a table associated with a category (3-8)
// Returns pointer to the matching entry (pair of pointers) or nullptr if not found.
undefined** __fastcall StringTable::lookupEntry(char* str, int category)
{
    uint8_t c1;
    uint32_t hash;
    int16_t index;
    const char** entryPtr;
    const char** endPtr;
    const char* s1;
    const char* s2;
    bool less;

    // Category must be in range 3..8 (inclusive)
    if ((category - 3U < 6) && (hash = hashString(str), hash < 0x107)) {
        index = g_hashIndexTable[hash]; // read short at offset hash*2

        if (index < 0) {
            // Negative index: chain lookup
            if (index < -0x70) {
                // Compute base pointer from secondary index
                entryPtr = (const char**)(&g_hashIndexTable + g_hashIndexTable[-0x71 - index] * 8);
                // Compute end pointer using the second short of the pair
                endPtr = entryPtr + g_hashIndexTable[-0x71 - index + 1] * -2; // note: -2 multiplier for pointer step
                if (entryPtr < endPtr) {
                    do {
                        // Compare first byte
                        if (*str == **(const char**)entryPtr) {
                            s1 = *(const char**)entryPtr + 1;
                            s2 = str + 1;
                            do {
                                c1 = *s2;
                                less = c1 < *s1;
                                if (c1 != *s1) {
                                    index = (1 - (uint32_t)less) - (uint32_t)(less != 0);
                                    goto check_match;
                                }
                                if (c1 == 0) break;
                                c1 = s2[1];
                                less = c1 < s1[1];
                                if (c1 != s1[1]) {
                                    index = (1 - (uint32_t)less) - (uint32_t)(less != 0);
                                    goto check_match;
                                }
                                s2 += 2;
                                s1 += 2;
                            } while (c1 != 0);
                            index = 0;
check_match:
                            if (index == 0) {
                                return (undefined**)entryPtr;
                            }
                        }
                        entryPtr += 2; // move to next pair (8 bytes)
                        if (endPtr <= entryPtr) {
                            return nullptr;
                        }
                    } while (true);
                }
            }
        } else {
            // Positive index: direct lookup in string table
            // Compare first byte
            if (*str == *(g_stringTable + index * 2)) {
                s2 = str + 1;
                s1 = *(g_stringTable + index * 2) + 1;
                do {
                    c1 = *s2;
                    less = c1 < *s1;
                    if (c1 != *s1) {
                        index = (1 - (uint32_t)less) - (uint32_t)(less != 0);
                        goto check_direct;
                    }
                    if (c1 == 0) break;
                    c1 = s2[1];
                    less = c1 < s1[1];
                    if (c1 != s1[1]) {
                        index = (1 - (uint32_t)less) - (uint32_t)(less != 0);
                        goto check_direct;
                    }
                    s2 += 2;
                    s1 += 2;
                } while (c1 != 0);
                index = 0;
check_direct:
                if (index == 0) {
                    return (undefined**)(g_stringTable + index * 2);
                }
            }
        }
    }
    return nullptr;
}