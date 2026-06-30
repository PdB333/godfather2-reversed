// FUNC_NAME: EARSArray::reserve
// Function at 0x004554a0: Grow dynamic array capacity if needed, copying existing elements.
// EA EARS engine dynamic array class (likely 3 fields: data pointer, size, capacity).
// +0x00: data pointer (int*)
// +0x04: size (int, number of elements)
// +0x08: capacity (int, allocated slots)

void EARSArray::reserve(uint newCapacity)
{
    // If new capacity is larger than current capacity
    if (newCapacity > this->capacity)
    {
        // Allocate new memory block (4 bytes per element)
        int* newData = (int*)heapAllocate(newCapacity * 4);

        // Copy existing elements if any
        if (this->data != nullptr)
        {
            uint i = 0;
            int* dst = newData;
            if (this->size > 0)
            {
                do
                {
                    if (dst != nullptr)
                    {
                        *dst = *(int*)(this->data + i);
                    }
                    i++;
                    dst++;
                } while (i < (uint)this->size);
            }
            // Free old memory
            heapFree(this->data);
        }

        // Update pointers and capacity
        this->data = newData;
        this->capacity = newCapacity;
    }
}