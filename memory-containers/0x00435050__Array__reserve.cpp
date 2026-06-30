// FUNC_NAME: Array::reserve
void Array::reserve(uint newCapacity)
{
    // unaff_ESI is the 'this' pointer.
    // Member layout:
    // +0x00: int* data   (pointer to element array)
    // +0x04: int  size    (current element count)
    // +0x08: int  capacity (allocated element capacity)

    if (newCapacity > this->capacity)
    {
        // Allocate new buffer (4 bytes per element)
        int* newData = (int*)FUN_009c8e80(newCapacity * 4);   // internal allocation

        if (this->data != 0)
        {
            // Copy existing elements
            uint count = 0;
            int* src = this->data;
            int* dst = newData;
            if (this->size != 0)
            {
                do
                {
                    *dst = *src;
                    count++;
                    dst++;
                    src++;
                } while (count < (uint)this->size);
            }
            // Free old buffer (internal deallocation)
            FUN_009c8f10(this->data);
        }

        // Update pointer and capacity
        this->data = newData;
        this->capacity = newCapacity;
    }
}