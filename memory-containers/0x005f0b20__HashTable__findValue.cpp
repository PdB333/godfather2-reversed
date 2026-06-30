// FUNC_NAME: HashTable::findValue
// Address: 0x005f0b20
// Role: Lookup a value by key using a two-level hash table structure.
// The 'this' pointer (in ESI) points to a HashTable object with:
//   +0x0c: pointer to an array of BucketEntry (8 bytes each)
//   +0x10: count of entries in that array
//   +0x34: context value passed to findBucket
//   +0x3c: guard count (must be >=1)
// The helper findBucket (0x005f0be0) returns a Range* with fields:
//   +0x04: rangeLow (initial sub-index)
//   +0x08: rangeHigh (initial bucket index)
// The final lookup reads from the bucket's base pointer at the clamped sub-index.
// A value of 0xDEADBEEF indicates an empty slot.

#include <cstdint>

struct Range {
    uint rangeLow;   // +0x04
    uint rangeHigh;  // +0x08
};

struct BucketEntry {
    uint limit;   // +0x00
    int* basePtr; // +0x04
};

// External helper: given a key and a hash context, returns a Range pointer
Range* __fastcall findBucket(uint key, uint hashContext);

class HashTable {
public:
    BucketEntry* bucketArray; // +0x0c
    uint        bucketCount;  // +0x10
    uint        hashContext;  // +0x34
    uint        guardCount;   // +0x3c (must be >=1)

    int __thiscall findValue(uint key) {
        if (key == 0 || this == nullptr || this->guardCount < 1)
            return 0;

        Range* range = findBucket(key, this->hashContext);
        if (range == nullptr)
            return 0;

        uint bucketIdx = range->rangeHigh; // +0x08
        uint subIdx    = range->rangeLow;  // +0x04

        // Clamp bucket index
        if (bucketIdx >= this->bucketCount)
            bucketIdx = this->bucketCount - 1;

        BucketEntry& entry = this->bucketArray[bucketIdx];

        // Clamp sub-index
        if (subIdx >= entry.limit)
            subIdx = entry.limit - 1;

        int value = entry.basePtr[subIdx];

        // Sentinel value for empty
        if (value == 0xDEADBEEF)
            return 0;

        return value;
    }
};