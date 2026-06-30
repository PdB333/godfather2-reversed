// FUNC_NAME: GenericArray::reserveCapacity
// Address: 0x0061a830
// Role: Reserves capacity for a 20-byte element dynamic array (like vector reserve)

void GenericArray::reserveCapacity(uint newCapacity)
{
    if (newCapacity > capacity) {
        // Allocate new block for newCapacity elements (each 0x14 bytes)
        int* newData = (int*)allocateMemory(newCapacity * 20);
        // Copy existing elements if present
        if (data != 0 && size != 0) {
            int* src = data;
            int* dst = newData;
            for (uint i = 0; i < size; i++) {
                // Copy 20-byte element: 8 bytes + 8 bytes + 4 bytes
                *(undefined8*)dst = *(undefined8*)src;
                *(undefined8*)(dst + 2) = *(undefined8*)(src + 2); // +8 bytes offset
                *(undefined4*)(dst + 4) = *(undefined4*)(src + 4); // +16 bytes offset
                src = (int*)((char*)src + 20);
                dst = (int*)((char*)dst + 20);
            }
        }
        // Free old memory
        freeMemory(data);
        // Update members
        data = newData;
        capacity = newCapacity;
    }
}