// FUNC_NAME: HashTable::insertEntry
#include <cstdint>

// Based on function at 0x005e7530 from The Godfather 2 (2008)
// This is a low-level hash table insertion that stores a key-value pair into a bucket.
// Key and value are both 3-uint32_t structures. The hash value is passed via EAX (in_EAX).
// The function applies an additional XOR (0xad103100) to the hash as part of a double hash scheme.
// The table is a fixed-size array of bucket pointers (at this+0x04) with a byte-sized count (this+0x1c).
// The bucket entry structure (size 0x60 bytes) stores expanded key parts (9 uint32s) and three copies of the value with sentinel markers (DAT_00e2b1a4).
// Returns a uint32 with LSB = 1 on success, LSB = 0 on failure.

class HashTable {
public:
    // +0x1c: number of buckets (1–255)
    uint8_t bucketCount;
    
    // +0x04: pointer to array of bucket pointers (each bucket is an array of entries)
    uint32_t** buckets;

    // Global sentinel value from DAT_00e2b1a4
    static const uint32_t SENTINEL = 0x00e2b1a4;  // placeholder, actual value unknown

    // Key expansion helper (FUN_0056b8a0) - fills a temp buffer with 9 parts from the input 3-uint key.
    // Returns a pointer to the expanded key (or bucket entry) for further processing.
    // In original code: puVar7 = FUN_0056b8a0(param_1[1], *param_1, param_1[2], &local_50)
    // param_1[0], [1], [2] are the 3 key uints; &local_50 is destination for expanded key parts.
    // We model it as returning a pointer to a preallocated entry or nullptr.
    uint32_t* expandKey(uint32_t key0, uint32_t key1, uint32_t key2, uint32_t* expandedOut);

    // Insert a key-value pair
    // hash: the precomputed hash (raw, before internal XOR)
    // key: pointer to 3 uint32_t key
    // value: pointer to 3 uint32_t value
    // Returns: low byte 0 = failure, 1 = success
    uint32_t insertEntry(uint32_t hash, const uint32_t* key, const uint32_t* value) {
        uint8_t count = bucketCount;
        uint32_t index = hash ^ 0xad103100;    // double hash

        // Quick sanity: index low byte should be < count
        // (Original code compared byte count to full uint; we interpret as mask check)
        if ((index & 0xFF) >= count) {
            return index & 0xFFFFFF00;         // failure indicator (clear low byte)
        }

        // Expand key into temporary structure (local_50..local_28 in original)
        uint32_t expanded[9]; // 9 parts: local_50, local_4c, local_48, local_40, local_3c, local_38, local_30, local_2c, local_28
        uint32_t* bucketOrEntry = expandKey(key[1], key[0], key[2], expanded);
        if (bucketOrEntry == nullptr) {
            return (uint32_t)bucketOrEntry & 0xFFFFFF00;
        }

        // Low byte of original hash used as tag
        uint8_t hashLow = (uint8_t)hash;
        // Combine tag with bucket pointer (original does: puVar7 = CONCAT31(high24, hashLow))
        uint32_t taggedPtr = ((uint32_t)bucketOrEntry & 0xFFFFFF00) | hashLow;
        bucketOrEntry = (uint32_t*)taggedPtr;

        if (count != 0) {
            // Use low byte of double-hashed index to select bucket pointer
            uint32_t* bucket = buckets[index & 0xFF];
            if (bucket != nullptr) {
                // Copy expanded key parts into bucket entry (order matches original)
                bucket[4] = expanded[1];  // local_4c
                bucket[5] = expanded[4];  // local_3c
                bucket[0] = expanded[0];  // local_50
                bucket[6] = expanded[7];  // local_2c
                bucket[1] = expanded[3];  // local_40
                bucket[8] = expanded[2];  // local_48
                bucket[2] = expanded[6];  // local_30
                bucket[9] = expanded[5];  // local_38

                // Zero out intermediate fields
                bucket[3]  = 0;
                bucket[7]  = 0;
                bucket[0xB] = 0;
                bucket[0xC] = 0;
                bucket[0xD] = 0;
                bucket[0xE] = 0;

                bucket[10] = expanded[8]; // local_28

                // Store value triple with sentinels
                uint32_t v0 = value[0];
                uint32_t v1 = value[1];
                uint32_t v2 = value[2];
                bucket[0xF] = SENTINEL;
                bucket[0x10] = v0;
                bucket[0x11] = v1;
                bucket[0x12] = v2;
                bucket[0x13] = SENTINEL;
                bucket[0x14] = v0;
                bucket[0x15] = v1;
                bucket[0x16] = v2;
                bucket[0x17] = SENTINEL;

                // Success: return pointer with LSB=1
                return ((uint32_t)bucket & 0xFFFFFF00) | 1;
            }
        }
        // Fallback failure path
        return (uint32_t)bucketOrEntry & 0xFFFFFF00;
    }
};