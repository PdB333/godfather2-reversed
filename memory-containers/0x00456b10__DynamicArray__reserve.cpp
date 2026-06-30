// FUNC_NAME: DynamicArray::reserve
// Function address: 0x00456b10
// Purpose: Ensures the array has capacity for at least 'newCapacity' elements (each element is 8 bytes).
// If current capacity is insufficient, allocates a new buffer, copies existing elements, frees old buffer.

void DynamicArray::reserve(unsigned int newCapacity)
{
    // unaff_ESI is this pointer.
    // this+0x00: buffer pointer (int*)
    // this+0x04: size (number of elements)
    // this+0x08: capacity (max elements)

    if (newCapacity > this->capacity)  // unaff_ESI[2]
    {
        // Allocate new buffer: newCapacity * elementSize (8)
        int* newBuffer = (int*)FUN_009c8e80(newCapacity * 8);  // presumably malloc

        if (this->buffer != nullptr)  // *unaff_ESI
        {
            unsigned int i = 0;
            int* dst = newBuffer;
            if (this->size != 0)  // unaff_ESI[1]
            {
                do
                {
                    if (newBuffer != nullptr)
                    {
                        // Copy 8 bytes per element (two ints)
                        int srcAddr = (int)this->buffer;
                        *dst = *(int*)(srcAddr + i * 8);
                        dst[1] = *(int*)(srcAddr + 4 + i * 8);
                    }
                    i++;
                    dst += 2;  // advance by 2 ints (8 bytes)
                } while (i < this->size);
            }
            // Free old buffer
            FUN_009c8f10(this->buffer);  // presumably free
        }
        this->buffer = newBuffer;
        this->capacity = newCapacity;
    }
}