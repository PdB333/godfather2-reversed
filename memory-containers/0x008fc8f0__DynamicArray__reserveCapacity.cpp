// FUNC_NAME: DynamicArray::reserveCapacity
void __thiscall DynamicArray::reserveCapacity(int* this, uint newCapacity)
{
    // this[0] = data pointer
    // this[1] = size (number of elements)
    // this[2] = capacity (allocated slots)
    if ((uint)this[2] < newCapacity)
    {
        // Allocate new block of uint32 elements
        undefined4* newData = (undefined4*)FUN_009c8e80(newCapacity * 4);
        if (this[0] != 0)
        {
            // Copy existing elements
            uint i = 0;
            undefined4* dest = newData;
            if (this[1] != 0)
            {
                do {
                    if (dest != (undefined4*)0x0)
                    {
                        *dest = *(undefined4*)(this[0] + i * 4);
                    }
                    i = i + 1;
                    dest = dest + 1;
                } while (i < (uint)this[1]);
            }
            // Free old data
            FUN_009c8f10(this[0]);
        }
        // Update pointer and capacity
        this[0] = (int)newData;
        this[2] = newCapacity;
    }
    return;
}