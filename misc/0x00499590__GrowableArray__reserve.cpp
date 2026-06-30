// FUNC_NAME: GrowableArray::reserve
void GrowableArray::reserve(uint newCapacity)
{
    // Structure fields (offsets relative to this):
    // +0x00: T* data (pointer to array of elements, each 12 bytes)
    // +0x04: uint count (number of elements currently stored)
    // +0x08: uint capacity (allocated capacity)

    if (this->capacity < newCapacity)
    {
        // Allocate new buffer: each element is 12 bytes
        T* newData = (T*)malloc(newCapacity * 12);

        if (this->data != nullptr)
        {
            uint i = 0;
            if (this->count != 0)
            {
                int srcOffset = 0;
                T* dest = newData;
                do
                {
                    // Copy 12-byte element: two assignments (8+4) to match decompiled
                    *(uint64*)dest = *(uint64*)((uint8*)this->data + srcOffset);
                    *(uint32*)((uint8*)dest + 8) = *(uint32*)((uint8*)this->data + srcOffset + 8);
                    i++;
                    srcOffset += 12;
                    dest = (T*)((uint8*)dest + 12);
                } while (i < this->count);
            }
            free(this->data);
        }

        this->data = newData;
        this->capacity = newCapacity;
    }
}