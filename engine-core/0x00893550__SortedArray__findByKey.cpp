//FUNC_NAME: SortedArray::findByKey
int __thiscall SortedArray::findByKey(uint key) {
    // this+0x2c: pointer to container structure
    Container* container = *(Container**)(this + 0x2c);
    if (container == nullptr) {
        return 0;
    }
    // container+0x04: number of elements
    int count = *(int*)(container + 4);
    if (count == 0) {
        return 0;
    }
    // container+0x14: pointer to array of 0xc-byte elements
    uint* data = *(uint**)(container + 0x14);
    int low = -1;
    int high = count;
    do {
        int mid = (high + low) >> 1;  // integer division
        int newHigh = mid;
        if (data[mid * 3] < key) {  // each element is 0xc = 3 uint32s
            newHigh = high;
            low = mid;
        }
        high = newHigh;
    } while (low + 1 != high);
    if (high < count && data[high * 3] == key) {
        return (int)(data + high * 3);  // pointer to matching element
    }
    return 0;
}