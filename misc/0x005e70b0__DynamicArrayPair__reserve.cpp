// FUNC_NAME: DynamicArrayPair::reserve
// Function at 0x005e70b0: Ensures capacity for a dynamic array of 8-byte elements (pairs). Used by container with fields at +0x00 (data), +0x04 (size), +0x08 (capacity).
void DynamicArrayPair::reserve(uint newCapacity)
{
    // If new capacity is not larger than current capacity, do nothing.
    if (this->capacity < newCapacity)
    {
        // Allocate new buffer: newCapacity * elementSize (8 bytes per element)
        uint8_t* newData = reinterpret_cast<uint8_t*>(allocateMemory(newCapacity * 8));
        
        // Copy existing elements from old buffer to new buffer (up to current size)
        if (this->data != nullptr)
        {
            uint count = 0;
            uint8_t* src = this->data;
            uint8_t* dst = newData;
            if (this->size != 0)
            {
                do
                {
                    // Copy 8 bytes per element (two 4-byte values)
                    if (dst != nullptr)
                    {
                        *reinterpret_cast<uint32_t*>(dst) = *reinterpret_cast<uint32_t*>(src);
                        *reinterpret_cast<uint32_t*>(dst + 4) = *reinterpret_cast<uint32_t*>(src + 4);
                    }
                    count++;
                    src += 8;
                    dst += 8;
                } while (count < this->size);
            }
            // Free old buffer
            freeMemory(this->data);
        }
        
        // Update data pointer and capacity
        this->data = newData;
        this->capacity = newCapacity;
    }
}