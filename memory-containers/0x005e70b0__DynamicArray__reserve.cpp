// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(uint newCapacity) {
    // struct DynamicArray {
    //     int* data;     // +0x00
    //     int size;      // +0x04
    //     int capacity;  // +0x08
    // };
    if (capacity < newCapacity) {
        int* newData = (int*)FUN_009c8e80(newCapacity * 8); // allocate space for newCapacity elements (8 bytes each)
        if (data != 0) {
            uint i = 0;
            int* dst = newData;
            if (size != 0) {
                do {
                    if (dst != 0) { // always true if allocation succeeded
                        *dst = *(int*)((int)data + i * 8);
                        *(dst + 1) = *(int*)((int)data + 4 + i * 8);
                    }
                    i++;
                    dst += 2;
                } while (i < (uint)size);
            }
            FUN_009c8f10(data); // free old buffer
        }
        data = newData;
        capacity = newCapacity;
    }
    return;
}