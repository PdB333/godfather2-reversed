// FUNC_NAME: DynamicArray::reserve
void __thiscall DynamicArray::reserve(int* this, uint newCapacity)
{
    // +0x00: int* data   (pointer to array elements)
    // +0x04: uint count   (number of elements currently stored)
    // +0x08: uint capacity (allocated capacity in number of elements)
    if ((uint)this[2] < newCapacity) {
        // Allocate new memory block (each element is 4 bytes)
        int* newData = (int*)FUN_009c8e80(newCapacity * 4);
        if (this[0] != 0) {
            uint i = 0;
            int* dest = newData;
            if (this[1] != 0) {
                do {
                    if (dest != (int*)0x0) {
                        *dest = *(int*)(this[0] + i * 4);
                    }
                    i = i + 1;
                    dest = dest + 1;
                } while (i < (uint)this[1]);
            }
        }
        // Free old memory if any
        if (this[0] != 0) {
            FUN_009c8f10(this[0]);
        }
        // Update data pointer and capacity
        this[0] = (int)newData;
        this[2] = newCapacity;
    }
    return;
}