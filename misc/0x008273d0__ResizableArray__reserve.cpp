// FUNC_NAME: ResizableArray::reserve
void __thiscall ResizableArray::reserve(int newCapacity)
{
    // Check if current capacity is less than requested
    if (this->capacity < newCapacity)
    {
        // Allocate new memory block: each element is 8 bytes
        int* newData = (int*)FUN_009c8e80(newCapacity * 8);
        
        // Copy existing elements if any
        if (this->data != 0)
        {
            int i = 0;
            int* src = this->data;
            int* dst = newData;
            if (this->count != 0)
            {
                do
                {
                    // Copy 8-byte element (two ints)
                    *dst = *src;
                    dst[1] = src[1];
                    i++;
                    src += 2;
                    dst += 2;
                } while (i < this->count);
            }
            // Free old memory
            FUN_009c8f10(this->data);
        }
        // Update pointer and capacity
        this->data = newData;
        this->capacity = newCapacity;
    }
}