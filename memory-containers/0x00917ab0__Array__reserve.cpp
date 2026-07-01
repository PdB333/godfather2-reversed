// FUNC_NAME: Array::reserve

void __thiscall Array::reserve(int* this, uint newCapacity)
{
    // this[0] = data pointer (offset 0x00)
    // this[1] = element count (offset 0x04)
    // this[2] = capacity (offset 0x08)

    if ((uint)this[2] < newCapacity)
    {
        // Allocate new block of newCapacity * sizeof(int) bytes
        int* newData = (int*)operator new(newCapacity * 4);

        if (this[0] != 0)
        {
            // Copy existing elements
            for (uint i = 0; i < (uint)this[1]; i++)
            {
                newData[i] = ((int*)this[0])[i];
            }
        }

        // Free old data
        operator delete((void*)this[0]);

        // Update pointer and capacity
        this[0] = (int)newData;
        this[2] = newCapacity;
    }
}