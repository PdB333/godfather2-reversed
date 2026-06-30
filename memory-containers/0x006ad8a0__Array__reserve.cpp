// FUNC_NAME: Array::reserve
void __thiscall Array::reserve(uint newCapacity)
{
    // If current capacity (this[2]) is less than requested capacity
    if ((uint)this[2] < newCapacity)
    {
        // Allocate new buffer: newCapacity * sizeof(element) (4 bytes each)
        int* newBuffer = (int*)allocateMemory(newCapacity * 4);
        
        // If old buffer exists, copy existing elements
        if (this[0] != 0)
        {
            uint i = 0;
            int* dst = newBuffer;
            if (this[1] != 0) // size > 0
            {
                do
                {
                    if (dst != (int*)0x0)
                    {
                        *dst = *(int*)(this[0] + i * 4);
                    }
                    i++;
                    dst++;
                } while (i < (uint)this[1]); // copy up to current size
            }
            // Free old buffer
            deallocateMemory(this[0]);
        }
        // Update pointer and capacity
        this[0] = (int)newBuffer;
        this[2] = newCapacity;
    }
    // If new capacity <= current capacity, do nothing (no shrink)
}