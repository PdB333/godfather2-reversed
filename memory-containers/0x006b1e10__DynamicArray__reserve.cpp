// FUNC_NAME: DynamicArray::reserve
// Function address: 0x006b1e10
// Purpose: Resize a dynamic array's capacity to at least newCapacity, preserving existing elements.
// Structure: +0x00 data pointer, +0x04 count, +0x08 capacity
void __thiscall DynamicArray::reserve(uint newCapacity)
{
    // Only grow if new capacity is larger than current
    if (this->mCapacity < newCapacity)
    {
        // Allocate new buffer (4 bytes per element)
        int* newBuffer = (int*)FUN_009c8e80(newCapacity * 4);
        
        // Copy existing elements if any
        if (this->mData != 0)
        {
            uint idx = 0;
            int* dest = newBuffer;
            if (this->mCount != 0)
            {
                do
                {
                    if (dest != 0)
                    {
                        *dest = *(int*)(this->mData + idx * 4);
                    }
                    idx++;
                    dest++;
                } while (idx < (uint)this->mCount);
            }
            // Free old buffer
            FUN_009c8f10(this->mData);
        }
        // Update members
        this->mData = newBuffer;
        this->mCapacity = newCapacity;
    }
}