// FUNC_NAME: DebugUtils::logEntryHashes
// Function address: 0x006b6da0
// Purpose: Iterates over an array of hash entries, computes a rolling hash using base 33 seeds,
//          and logs each resulting hash via the engine's debug output system.
// Struct layout:
//   HashData - offset 0x00: count (uint32)
//               offset 0x04: seedA (uint32) - first global seed
//               offset 0x08: seedB (uint32) - second global seed
//               offset 0x0C: entries[] - array of HashDataEntry (each 20 bytes)
//   HashDataEntry - offset 0x00: field1 (uint32)
//                    offset 0x04: field2 (uint32)
//                    offset 0x08: field3 (uint32) - unused in hash
//                    offset 0x0C: field4 (uint32) - unused
//                    offset 0x10: field5 (uint32) - unused

#pragma pack(push, 4)
struct HashDataEntry {
    uint32_t field1; // +0x00
    uint32_t field2; // +0x04
    uint32_t field3; // +0x08 (unused)
    uint32_t field4; // +0x0C (unused)
    uint32_t field5; // +0x10 (unused)
};

struct HashData {
    uint32_t count;               // +0x00
    uint32_t seedA;               // +0x04
    uint32_t seedB;               // +0x08
    HashDataEntry entries[1];     // +0x0C (variable length)
};
#pragma pack(pop)

// Forward declaration of the debug output function (at 0x008142f0)
extern void __cdecl debugLogHash(uint32_t unusedParam1, uint32_t hashValue, uint32_t param3, uint32_t param4);

void __fastcall logEntryHashes(HashData* pData) {
    uint32_t count = pData->count;
    if (count == 0) {
        return;
    }

    uint32_t seedA = pData->seedA;
    uint32_t seedB = pData->seedB;

    // Pre-calculate the initial hash from the two seeds:
    // hash = (seedA * 33 + seedB) * 33
    uint64_t initialHash = (uint64_t)seedA * 33 + (uint64_t)seedB;
    initialHash *= 33;

    for (uint32_t i = 0; i < count; ++i) {
        HashDataEntry* entry = &pData->entries[i];
        uint32_t entryC = entry->field1; // +0x00
        uint32_t entryD = entry->field2; // +0x04

        // Complete the hash for this entry:
        // finalHash = (initialHash + entryC) * 33 + entryD
        uint64_t finalHash = (initialHash + (uint64_t)entryC) * 33 + (uint64_t)entryD;

        // Output the hash (likely for debugging/validation)
        // The first argument (2) may be a log priority/channel
        // The third and fourth arguments (1,1) might be flags
        debugLogHash(2, (uint32_t)finalHash, 1, 1);
    }
}