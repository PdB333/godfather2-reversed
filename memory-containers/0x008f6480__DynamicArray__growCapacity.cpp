// FUNC_NAME: DynamicArray::growCapacity
void DynamicArray::growCapacity(unsigned int newCapacity)
{
    // param_1 is 'this' pointer with fields:
    // +0x00: data pointer (int*)
    // +0x04: size (int)
    // +0x08: capacity (int)

    if (this->capacity < newCapacity)
    {
        // Allocate new buffer (4 bytes per element)
        int* newData = (int*)allocateMemory(newCapacity * sizeof(int));

        // Copy existing elements from old buffer to new one
        if (this->data != nullptr)
        {
            for (unsigned int i = 0; i < this->size; ++i)
            {
                newData[i] = this->data[i];
            }
            // Free old buffer
            freeMemory(this->data);
        }

        // Update data pointer and capacity
        this->data = newData;
        this->capacity = newCapacity;
    }
}