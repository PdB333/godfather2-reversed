// FUNC_NAME: SortedArray::findKeyIndex
// Function at 0x006b0150: Binary search in a sorted array of uint keys (8-byte elements, key at offset 0).
// Returns index if found, -1 otherwise.
int __thiscall SortedArray::findKeyIndex(uint key) const {
    int count = this->count;      // param_1[1], number of elements
    int low = -1;
    int high = -1;                // Note: high initially same as low, but later reassigned

    high = low;                   // iVar6 = -1 redundant, but keeps logic
    if (count != 0) {
        int currentHigh = count;   // iVar4
        do {
            int mid = (currentHigh + high) >> 1;   // mid = (low + high) >> 1
            int temp = mid;                        // iVar5
            // Compare first uint of element at index mid (8 bytes per element)
            if (this->data[mid * 2] < key) {       // *(uint*)(*param_1 + mid*8)
                temp = currentHigh;                // update low bound
                high = mid;                        // iVar6
            }
            currentHigh = temp;
        } while (high + 1 != currentHigh);         // while low + 1 < high

        if ((currentHigh < count) && (this->data[currentHigh * 2] == key)) {
            return currentHigh;                    // found
        }
    }
    return -1;
}