// FUNC_NAME: Collection12::growCapacity
void __thiscall Collection12::growCapacity(unsigned int newCapacity)
{
    // if current capacity is insufficient
    if (this->capacity < newCapacity)
    {
        // allocate new buffer: each element is 12 bytes
        void* newBuffer = heapAllocate(newCapacity * 12); // +0x8 offset unknown

        if (this->buffer != 0)
        {
            unsigned int i = 0;
            if (this->count != 0)
            {
                int srcOffset = 0;
                char* dest = (char*)newBuffer;
                do {
                    // copy 12-byte element
                    *(unsigned long long*)dest = *(unsigned long long*)((char*)this->buffer + srcOffset);
                    *(unsigned int*)(dest + 8) = *(unsigned int*)((char*)this->buffer + srcOffset + 8);
                    i++;
                    srcOffset += 12;
                    dest += 12;
                } while (i < (unsigned int)this->count);
            }
            heapFree(this->buffer);
        }
        this->buffer = newBuffer;
        this->capacity = newCapacity;
    }
}