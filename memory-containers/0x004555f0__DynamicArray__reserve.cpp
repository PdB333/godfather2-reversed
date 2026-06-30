// FUNC_NAME: DynamicArray::reserve
void DynamicArray::reserve(uint newCapacity)
{
    // Structure layout:
    // +0x00: void* data;          // pointer to array of 8-byte elements
    // +0x04: uint count;          // number of elements currently stored
    // +0x08: uint capacity;       // maximum number of elements without reallocation

    if (newCapacity > this->capacity)
    {
        void* newData = memAlloc(newCapacity * 8);   // allocate new block of elements
        if (this->data != 0)
        {
            uint i = 0;
            uint* src = (uint*)this->data;           // source as uint pairs
            uint* dst = (uint*)newData;              // destination as uint pairs
            while (i < this->count)
            {
                // copy a pair of uint32 (8 bytes)
                *dst = *src;
                dst[1] = src[1];
                src += 2;
                dst += 2;
                i++;
            }
            memFree(this->data);                     // free old block
        }
        this->data = newData;
        this->capacity = newCapacity;
    }
}