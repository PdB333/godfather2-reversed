// FUNC_NAME: SortedArray::findIndexByKey
int __thiscall SortedArray::findIndexByKey(uint *keyPtr) {
    int low = -1;
    int high = this->count;           // +0x04: count of elements
    int mid;

    while (low + 1 != high) {
        mid = (low + high) >> 1;
        // +0x00: pointer to array of 0x10-byte structures
        uint *elementKey = (uint *)(this->array + mid * 0x10);
        if (*elementKey < *keyPtr) {
            low = mid;
        } else {
            high = mid;
        }
    }

    // high is the insertion point / first index where elementKey >= *keyPtr
    if (high < this->count) {
        uint *candidateKey = (uint *)(this->array + high * 0x10);
        if (*candidateKey == *keyPtr) {
            return high;
        }
    }
    return -1;
}