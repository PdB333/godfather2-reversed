// FUNC_NAME: Buffer::reserve
void __thiscall Buffer::reserve(int thisPtr, int newSize) {
    // Offsets: +0x20 capacity (number of elements of 8 bytes each)
    int oldCapacity = *(int*)(thisPtr + 0x20);
    int newCapacity;
    if (oldCapacity < newSize) {
        // Growth formula: old + 20 + new
        newCapacity = oldCapacity + 0x14 + newSize;
    } else {
        // Double the capacity if already enough
        newCapacity = oldCapacity * 2;
    }
    // Reallocate memory: old size = oldCapacity * 8, new size = newCapacity * 8
    int* newData = (int*)FUN_006279a0(oldCapacity * 8, newCapacity * 8);
    // +0x1c: raw data pointer
    *(int*)(thisPtr + 0x1c) = (int)newData;
    // +0x20: new capacity
    *(int*)(thisPtr + 0x20) = newCapacity;
    // +0x18: "begin" pointer, adjusted by header size (0xA8) and element offset
    *(int*)(thisPtr + 0x18) = (int)newData - 0xa8 + newSize * 8;
    FUN_00635b50(); // likely buffer initialization/clear
}