// FUNC_NAME: Array::reserve

void __thiscall Array::reserve(unsigned int newCapacity)
{
    // +0x00: data pointer, +0x04: count, +0x08: capacity
    if (this->capacity < newCapacity)
    {
        // Allocate new buffer for newCapacity elements, each 8 bytes (two 32-bit values)
        undefined4* newData = (undefined4*)allocateMemory(newCapacity * 8);
        if (this->data != 0)
        {
            unsigned int i = 0;
            undefined4* dest = newData;
            if (this->count != 0)
            {
                do
                {
                    if (newData != 0) // Safe check (likely always true after allocation)
                    {
                        int oldData = this->data;
                        *dest = *(undefined4*)(oldData + i * 8);
                        dest[1] = *(undefined4*)(oldData + 4 + i * 8);
                    }
                    i++;
                    dest += 2; // Advance by 2 undefined4 (8 bytes)
                } while (i < this->count);
            }
            freeMemory(this->data);
        }
        this->data = (int*)newData;
        this->capacity = newCapacity;
    }
}