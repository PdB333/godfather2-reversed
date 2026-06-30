// FUNC_NAME: EARS::Framework::TArray::reserve
void TArray::reserve(uint newCapacity)
{
    // Check if new capacity is greater than current capacity
    if (this->capacity < newCapacity)
    {
        // Allocate memory for new array (each element is 8 bytes)
        void* newData = operator new(newCapacity * 8);
        
        // Copy existing elements if any
        if (this->data != nullptr)
        {
            uint i = 0;
            void* src = this->data;
            void* dst = newData;
            while (i < this->size)
            {
                // Copy 8 bytes per element
                *(uint64_t*)dst = *(uint64_t*)src;
                i++;
                src = (uint8_t*)src + 8;
                dst = (uint8_t*)dst + 8;
            }
        }
        
        // Free old data
        operator delete(this->data);
        
        // Update pointer and capacity
        this->data = newData;
        this->capacity = newCapacity;
    }
}