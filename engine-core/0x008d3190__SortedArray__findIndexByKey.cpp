// FUNC_NAME: SortedArray::findIndexByKey
// 0x008d3190
// Binary search in a sorted array of 24-byte elements with a 32-bit key at the start.

struct SortedArrayElement {
    uint32_t key;   // +0x00
    // +0x04..+0x17: other data (20 bytes)
};

struct SortedArray {
    SortedArrayElement* data; // +0x00
    int count;                // +0x04
};

int __thiscall SortedArray::findIndexByKey(const uint32_t* pKey) {
    int low = -1;
    int high = this->count;
    if (high != 0) {
        do {
            int mid = (low + high) >> 1;
            int newHigh = mid;
            if (this->data[mid].key < *pKey) {
                newHigh = high;
                low = mid;
            }
            high = newHigh;
        } while (low + 1 != newHigh);
        if (high < this->count && this->data[high].key == *pKey) {
            return high;
        }
    }
    return -1;
}