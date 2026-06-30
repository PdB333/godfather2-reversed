// FUNC_NAME: SortedArrayManager::findIndexByKey
int SortedArrayManager::findIndexByKey(uint32_t key, int numElements) {
    int low = -1;
    int high = numElements;
    while (low + 1 < high) {
        int mid = (low + high) / 2;
        uint32_t currentKey = *(uint32_t*)((uint8_t*)this + mid * 0x10); // first field at offset 0
        if (currentKey < key) {
            low = mid;
        } else {
            high = mid;
        }
    }
    if (high != numElements) {
        uint32_t foundKey = *(uint32_t*)((uint8_t*)this + high * 0x10);
        if (foundKey == key) {
            return high;
        }
    }
    return -1;
}