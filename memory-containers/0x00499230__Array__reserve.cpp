// FUNC_NAME: Array::reserve
// Address: 0x00499230
// Role: Reserves capacity for an array of 8-byte elements. If the requested capacity is larger than the current capacity, reallocates the internal buffer.

void Array::reserve(unsigned int newCapacity)
{
    // Check if we need to grow
    if (this->capacity < newCapacity)
    {
        // Allocate new buffer (each element is 8 bytes)
        void* newData = malloc(newCapacity * 8);
        if (this->data != nullptr)
        {
            unsigned int i = 0;
            int* dest = (int*)newData;
            if (this->count != 0)
            {
                do
                {
                    if (dest != nullptr) // defensive: newData should not be null
                    {
                        // Copy one 8-byte element (two ints)
                        dest[0] = this->data[i * 2];
                        dest[1] = this->data[i * 2 + 1];
                    }
                    i++;
                    dest += 2;
                } while (i < (unsigned int)this->count);
            }
            free(this->data);
        }
        this->data = (int*)newData;
        this->capacity = newCapacity;
    }
}