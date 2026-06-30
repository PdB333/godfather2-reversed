// FUNC_NAME: SortedKeyValueArray::binarySearch
// Function address: 0x00617920
// Performs binary search on a sorted array of 8-byte key-value pairs.
// Each entry is 8 bytes: uint key + uint value (or maybe uint key + another field).
// Returns index if key found, else -1.

int SortedKeyValueArray::binarySearch(uint key) {
    int count = m_count;         // this+0x04: number of elements
    int low = 0;
    int high = count - 1;
    int index = -1;

    if (count != 0) {
        int currentLow = low;
        do {
            int mid = (currentLow + high) >> 1;  // mid = (currentLow + high) / 2
            int newLow = mid;
            uint midKey = m_pArray[mid].key;     // m_pArray is this+0x00, each element is 8 bytes
            if (midKey < key) {
                newLow = currentLow;
                high = mid;
            }
            currentLow = newLow;
        } while (high + 1 != newLow);

        if ((newLow < count) && (m_pArray[newLow].key == key)) {
            index = newLow;
        }
    }
    return index;
}