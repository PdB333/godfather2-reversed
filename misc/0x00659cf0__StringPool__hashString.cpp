// FUNC_NAME: StringPool::hashString
// Address: 0x00659cf0
// Role: Computes a hash of a string with a given maximum length, using a lookup table.
// The table at 0x01203640 is initialized by a call to initTable() if not already done.
// ecx (this) is unused — the function is a member but does not access instance data.
// edx = string pointer, eax = maximum length to process.

#include <cstdint>

// Global flag indicating if the hash table is initialized
extern bool g_hashTableInitialized; // DAT_00f0ccb7

// Initialization function for the hash table
extern void initHashTable(); // FUN_00659c80

// The 256-byte hash lookup table
extern const uint8_t g_hashTable[256]; // DAT_01203640

uint32_t StringPool::hashString(const char* str, int maxLength)
{
    // One-time initialization of the hash table
    if (g_hashTableInitialized)
    {
        initHashTable();
        str; // The call may modify str? (extraout_EDX) — likely a compiler artifact, ignore.
    }

    const char* p = str;
    char c = *p;
    uint32_t hash = 0;

    while (true)
    {
        if (c == '\0')
        {
            return hash;
        }
        p++;
        if (maxLength == 0)
        {
            break;
        }
        // hash = (hash * 2) XOR table[c]
        hash = (hash << 1) ^ static_cast<uint32_t>(g_hashTable[static_cast<uint8_t>(c)]);
        c = *p;
        maxLength--;
    }
    return hash;
}