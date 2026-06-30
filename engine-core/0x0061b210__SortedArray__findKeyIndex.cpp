// FUNC_NAME: SortedArray::findKeyIndex
// Address: 0x0061b210
// Role: Binary search in a sorted array of 8-byte records (key uint32 at offset 0, data at offset 4).
// This returns the index of the element matching *key, or -1 if not found.
// class layout:
//   +0x00: uint8* m_pArray;   // pointer to contiguous array of 8-byte entries
//   +0x04: int32  m_count;    // number of elements in the array

int __thiscall SortedArray::findKeyIndex(SortedArray* this, const uint32_t* key) {
    int32_t count = this->m_count;
    int32_t result = -1;
    int32_t low = -1;   // lower bound (exclusive)
    int32_t high = count; // upper bound (exclusive)

    if (count != 0) {
        do {
            int32_t mid = (high + low) >> 1; // floor((low+high)/2)
            int32_t newHigh = mid;
            uint32_t midKey = *(uint32_t*)(this->m_pArray + mid * 8);
            if (midKey < *key) {
                low = mid;         // key is in right half
                newHigh = high;    // keep original high
            }
            high = newHigh;
        } while (low + 1 != high); // while range not collapsed

        // After loop, 'high' is the insertion point
        if (high < count) {
            uint32_t candidateKey = *(uint32_t*)(this->m_pArray + high * 8);
            if (candidateKey == *key) {
                result = high;
            }
        }
    }
    return result;
}