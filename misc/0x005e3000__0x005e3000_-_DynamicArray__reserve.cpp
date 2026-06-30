// FUNC_NAME: 0x005e3000 - DynamicArray::reserve

void DynamicArray::reserve(uint newCapacity)
{
    // Only grow, never shrink
    if (newCapacity > this->capacity)
    {
        // Each element is 8 bytes (e.g., two 4-byte fields)
        int* newBuffer = (int*)allocateMemory(newCapacity * 8);
        if (this->buffer != nullptr)
        {
            uint i = 0;
            int* src = this->buffer;   // +0x00
            int* dst = newBuffer;
            while (i < this->count)    // +0x04: current element count
            {
                *dst = *src;
                *(dst + 1) = *(src + 1);
                i++;
                src += 2; // advance 8 bytes
                dst += 2;
            }
            freeMemory(this->buffer);
        }
        this->buffer = newBuffer;    // +0x00
        this->capacity = newCapacity; // +0x08
    }
}