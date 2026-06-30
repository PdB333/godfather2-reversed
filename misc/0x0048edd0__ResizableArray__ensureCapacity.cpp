// FUNC_NAME: ResizableArray::ensureCapacity
void ResizableArray::ensureCapacity(uint newCapacity) {
    int* thisPtr = (int*)this; // unaff_ESI
    uint* dataPtr = (uint*)this; // base for offsets
    int* currentData = (int*)*dataPtr; // offset +0x00
    uint size = *(uint*)(dataPtr + 1); // offset +0x04
    uint* capacityPtr = (uint*)(dataPtr + 2); // offset +0x08

    if (*capacityPtr < newCapacity) {
        int* newData = (int*)allocate(newCapacity * 4); // FUN_009c8e80
        if (currentData != 0) {
            uint i = 0;
            int* dst = newData;
            if (size != 0) {
                do {
                    if (dst != 0) {
                        *dst = *(int*)(currentData + i);
                    }
                    i++;
                    dst++;
                } while (i < size);
            }
            deallocate(currentData); // FUN_009c8f10
        }
        *dataPtr = (uint)newData; // store new pointer at offset +0x00
        *capacityPtr = newCapacity; // update capacity at offset +0x08
    }
}