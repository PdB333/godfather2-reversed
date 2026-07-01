// FUNC_NAME: DynamicArray::reserve
void DynamicArray::reserve(uint newCapacity)
{
    // +0x00: int* data (pointer to element array)
    // +0x04: int size (number of elements)
    // +0x08: int capacity (allocated element count)
    if (this->capacity < newCapacity)
    {
        // Allocate new block (4 bytes per element)
        int* newData = (int*)allocateMemory(newCapacity * 4);
        if (this->data != nullptr)
        {
            // Copy existing elements
            for (uint i = 0; i < this->size; i++)
            {
                if (newData != nullptr)
                {
                    newData[i] = this->data[i];
                }
            }
            // Free old block
            freeMemory(this->data);
        }
        this->data = newData;
        this->capacity = newCapacity;
    }
}