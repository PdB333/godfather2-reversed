// FUNC_NAME: DynamicArray8::reserve
void __thiscall DynamicArray8::reserve(uint newCapacity)
{
    // param_1 = this (struct with data pointer at +0x0, size at +0x4, capacity at +0x8)
    // Each element is 8 bytes (two int32s or a structure)
    if (capacity < newCapacity) {
        int* newData = (int*)allocateMemory(newCapacity * 8); // 8 bytes per element
        if (data != 0 && size != 0) {
            for (uint i = 0; i < size; i++) {
                // Copy 8 bytes per element: two dwords
                newData[i * 2] = data[i * 2];
                newData[i * 2 + 1] = data[i * 2 + 1];
            }
        }
        if (data != 0) {
            deallocateMemory(data);
        }
        data = newData;
        capacity = newCapacity;
    }
}