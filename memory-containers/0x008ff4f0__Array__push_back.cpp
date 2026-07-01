// FUNC_NAME: Array::push_back

void __thiscall Array::push_back(int* thisPtr, int value) {
    int capacity = *(int*)(thisPtr + 0x18);  // +0x18 capacity
    int size = *(int*)(thisPtr + 0x14);     // +0x14 current size

    if (size == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        FUN_008be110(capacity * 4); // allocate or reallocate (size in bytes)
    }

    int* data = *(int**)(thisPtr + 0x10); // +0x10 data pointer
    data[size] = value;
    *(int*)(thisPtr + 0x14) = size + 1;   // increment size
}