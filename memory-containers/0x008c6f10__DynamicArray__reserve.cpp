// FUNC_NAME: DynamicArray::reserve
// Address: 0x008c6f10
// Role: Ensures the dynamic array has at least the specified capacity, reallocating and copying existing elements if necessary.

void __thiscall DynamicArray::reserve(int* this, uint newCapacity)
{
    // this[0] = data pointer
    // this[1] = count (number of elements)
    // this[2] = capacity (allocated slots)

    if ((uint)this[2] < newCapacity)
    {
        // Allocate new block of newCapacity * 4 bytes (each element is 4 bytes)
        int* newData = (int*)allocate(newCapacity * 4);

        if (this[0] != 0)
        {
            uint i = 0;
            int* dest = newData;
            if (this[1] != 0)
            {
                do
                {
                    // Copy element if destination is valid (safety check)
                    if (dest != (int*)0x0)
                    {
                        *dest = *(int*)(this[0] + i * 4);
                    }
                    i = i + 1;
                    dest = dest + 1;
                } while (i < (uint)this[1]);
            }
            // Free old memory
            deallocate(this[0]);
        }

        // Update pointer and capacity
        this[0] = (int)newData;
        this[2] = newCapacity;
    }
    return;
}