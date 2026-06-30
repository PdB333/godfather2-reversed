// FUNC_NAME: Array::reserve
void Array::reserve(uint newCapacity)
{
    // If new capacity is larger than current capacity, reallocate
    if (newCapacity > this->capacity)
    {
        // Allocate new buffer with size = newCapacity * elementSize (4 bytes per element)
        int *newBuffer = (int *)allocateMemory(newCapacity * 4);

        // Copy existing elements if there are any
        if (this->data != nullptr)
        {
            uint count = this->count; // number of used elements
            int *src = this->data;
            int *dst = newBuffer;

            if (count != 0)
            {
                do
                {
                    *dst++ = *src++;
                    count--;
                } while (count > 0);
            }

            // Free old buffer
            freeMemory(this->data);
        }

        // Update pointers and capacity
        this->data = newBuffer;
        this->capacity = newCapacity;
    }
    // If new capacity <= old capacity, no change needed
}