// FUNC_NAME: DynamicArray::reserve
// Address: 0x008bc950
// Role: Resizes the internal buffer to accommodate at least 'newCapacity' elements of size 0x2c (44 bytes).
// This is a __thiscall member function of a dynamic array class (likely part of EA EARS engine).
// Fields: +0x00 = data pointer, +0x04 = element count, +0x08 = capacity

void __thiscall DynamicArray::reserve(uint newCapacity)
{
    int newBuffer;
    uint i;
    uint* src; // pointer to source element in old buffer
    uint* dst; // pointer to destination in new buffer (starts at newBuffer + 0x20, but adjusted)

    // Only grow if current capacity is insufficient
    if (this->capacity < newCapacity)
    {
        // Allocate new buffer: newCapacity * sizeof(element) = newCapacity * 0x2c
        newBuffer = allocate(newCapacity * 0x2c);

        if (this->data != 0)
        {
            i = 0;
            if (this->count != 0)
            {
                // dst starts at newBuffer + 0x20 (but copy writes to dst-8, effectively newBuffer)
                dst = (uint*)(newBuffer + 0x20);
                do
                {
                    // Calculate source pointer: old data + (dst - newBuffer - 0x20) = old data
                    src = (uint*)((int)dst + this->data + (-0x20 - newBuffer));

                    // Copy one element (0x2c bytes = 11 dwords)
                    *(uint64*)(dst - 8) = *(uint64*)src;          // bytes 0-7
                    *(uint64*)(dst - 6) = *(uint64*)(src + 2);    // bytes 8-15 (src+2 is 8 bytes offset)
                    *(uint64*)(dst - 4) = *(uint64*)(src + 4);    // bytes 16-23
                    dst[-2] = *(src + 6);                         // bytes 24-27
                    dst[-1] = *(src + 7);                         // bytes 28-31
                    *dst = *(src + 8);                            // bytes 32-35
                    dst[1] = *(src + 9);                          // bytes 36-39
                    *(byte*)(dst + 2) = *(byte*)(src + 10);       // byte 40
                    *(byte*)((int)dst + 9) = *(byte*)((int)src + 0x29); // byte 41 (offset 0x29 = 41)

                    i++;
                    dst += 0xb; // advance by 11 dwords = 44 bytes
                } while (i < this->count);
            }
            // Free old buffer
            deallocate(this->data);
        }

        // Update members
        this->data = newBuffer;
        this->capacity = newCapacity;
    }
}