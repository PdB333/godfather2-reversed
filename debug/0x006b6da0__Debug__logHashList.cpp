// FUNC_NAME: Debug::logHashList
// Address: 0x006b6da0
// Role: Iterates over an array of entries (each 5 uint32s, first four used as hash input) and logs a 32-bit hash derived via polynomial base 33.

#include <cstdint>

// External logging function; parameters: logLevel (2), value, unknown1 (1), unknown2 (1)
void FUN_008142f0(int level, uint32_t value, int arg3, int arg4);

void __fastcall Debug::logHashList(uint* listHeader)
{
    uint32_t count = listHeader[0];
    if (count == 0)
        return;

    // listHeader: [count, entry0[5], entry1[5], ...]
    // entryPtr starts at listHeader+3, which points to the third uint32 (index 2) of the first entry.
    uint* entryPtr = listHeader + 3;

    for (uint32_t i = 0; i < count; i++)
    {
        // Each entry provides 4 uint32s (fields 0-3) for hashing. Field 4 is unused.
        uint32_t field0 = entryPtr[-2]; // entry at index 0
        uint32_t field1 = entryPtr[-1]; // index 1
        uint32_t field2 = entryPtr[0];  // index 2
        uint32_t field3 = entryPtr[1];  // index 3

        // Compute hash: ((field0 * 33 + field1) * 33 + field2) * 33 + field3
        uint64_t hash = (static_cast<uint64_t>(field0) * 33 + field1) * 33 + field2;
        hash = hash * 33 + field3;

        uint32_t finalHash = static_cast<uint32_t>(hash);

        // Log the result (truncated to 32 bits)
        FUN_008142f0(2, finalHash, 1, 1);

        // Advance to the next entry (each entry is 5 uint32s)
        entryPtr += 5;
    }
}