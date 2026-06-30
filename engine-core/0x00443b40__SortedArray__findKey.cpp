// FUNC_NAME: SortedArray::findKey
int SortedArray::findKey(uint* key) {
    // Class structure: this[0] = m_pArray (pointer to base of 8-byte records), this[1] = m_nCount (number of valid entries)
    int count = m_nCount; // +0x04
    int high = count;     // exclusive upper bound
    int low = -1;         // inclusive lower bound
    int result = -1;      // default not found

    if (count != 0) {
        do {
            int mid = (high + low) >> 1;                // mid = (low + high) / 2
            uint midValue = *(uint*)(m_pArray + mid * 8); // compare only first 4 bytes of 8-byte record

            if (midValue < *key) {
                low = mid;       // key is in the upper half
            } else {
                high = mid;      // key is in the lower half
            }
        } while (low + 1 != high); // continue while range has more than 1 element

        // After loop, low+1 == high, so high is the first index >= key
        if (high < count && *(uint*)(m_pArray + high * 8) == *key) {
            result = high;
        }
    }

    return result; // returns index if found, otherwise -1
}