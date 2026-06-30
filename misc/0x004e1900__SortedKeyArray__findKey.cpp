// FUNC_NAME: SortedKeyArray::findKey
// Address: 0x004e1900
// Role: Binary search on a sorted array of 128-bit keys (4 uint32 fields).
// Elements have size 0x18 (24 bytes); first 16 bytes form the key.
// Comparison is lexicographic with field3 (offset 0xc) most significant,
// then field2 (offset 8), field1 (offset 4), field0 (offset 0).
// Returns index if found, -1 otherwise.

#include <cstdint>

struct Key128 {
    uint32_t field0; // offset 0x00
    uint32_t field1; // offset 0x04
    uint32_t field2; // offset 0x08
    uint32_t field3; // offset 0x0c
    // padding 8 bytes (0x10-0x17) for 0x18 total element size
};

class SortedKeyArray {
public:
    // +0x00: pointer to array of Key128 (each 0x18 bytes)
    // +0x04: number of elements
    int32_t* mData;   // actually points to start of array
    int32_t mCount;

    // Returns index of exact key, or -1 if not found.
    // key must point to 4 contiguous uint32_t.
    int __thiscall findKey(const uint32_t* key) const {
        int32_t low = -1;
        int32_t high = mCount;
        int32_t mid;

        do {
            mid = (low + high) >> 1;
            const uint8_t* base = reinterpret_cast<const uint8_t*>(mData);
            const Key128* elem = reinterpret_cast<const Key128*>(base + mid * 0x18);

            // Compare elem < key lexicographically (field3, field2, field1, field0)
            bool less = (elem->field3 < key[3]) ||
                        (elem->field3 == key[3] && elem->field2 < key[2]) ||
                        (elem->field3 == key[3] && elem->field2 == key[2] &&
                         elem->field1 <= key[1] &&
                         (elem->field1 < key[1] || elem->field0 < key[0]));

            if (less) {
                low = mid;
                mid = high; // adjust to maintain original loop structure
            }
            high = mid;
        } while (low + 1 != mid); // loop until interval converges

        // After loop, mid holds the candidate index (the insertion point)
        if (mid < mCount) {
            const uint8_t* base = reinterpret_cast<const uint8_t*>(mData);
            const Key128* elem = reinterpret_cast<const Key128*>(base + mid * 0x18);
            if (elem->field0 == key[0] &&
                elem->field1 == key[1] &&
                elem->field2 == key[2] &&
                elem->field3 == key[3]) {
                return mid;
            }
        }
        return -1;
    }
};