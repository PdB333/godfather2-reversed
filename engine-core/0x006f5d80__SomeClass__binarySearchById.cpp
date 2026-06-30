// FUNC_NAME: SomeClass::binarySearchById
int SomeClass::binarySearchById(uint searchKey, int count) { // __thiscall, this points to the base of sorted array of 0x24-byte structs
    int low = -1;
    int high = count;
    while (low + 1 < high) {
        int mid = (low + high) / 2;
        uint key = *(uint *)((int)this + mid * 0x24); // Struct first field at +0x0 is the key
        if (key < searchKey) {
            low = mid;
        } else {
            high = mid;
        }
    }
    if (high < count) {
        uint key = *(uint *)((int)this + high * 0x24);
        if (key == searchKey) {
            return high; // Found at index high
        }
    }
    return -1;
}