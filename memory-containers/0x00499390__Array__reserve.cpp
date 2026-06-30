// FUNC_NAME: Array::reserve
void Array::reserve(uint newCapacity)
{
    // Check if current capacity is insufficient
    if (this->capacity < newCapacity)
    {
        // Allocate new block: each element is 4 bytes (likely int/uint/pointer)
        int* newData = (int*)operator new[](newCapacity * 4);
        
        // Copy existing elements if any
        if (this->data != 0)
        {
            uint i = 0;
            int* src = this->data;
            int* dst = newData;
            while (i < this->count)
            {
                *dst = *src;
                i++;
                src++;
                dst++;
            }
            // Free old block
            operator delete[](this->data);
        }
        
        // Update pointers and capacity
        this->data = newData;
        this->capacity = newCapacity;
    }
    // Note: count remains unchanged; new elements are uninitialized
}