// FUNC_NAME: DynamicArray::ensureCapacity

// Reconstructed C++ method for function at 0x005e1730
// This method ensures the dynamic array has a capacity of at least 8 elements.
// If the current capacity is less than 8, it allocates a new buffer of 8 elements
// (32 bytes total, each element 4 bytes), copies existing elements, frees the old buffer,
// and updates the data pointer and capacity.

void DynamicArray::ensureCapacity()
{
    // Structure offsets (relative to this):
    // +0x00: int* data        (pointer to element array)
    // +0x04: int  size        (number of valid elements)
    // +0x08: int  capacity    (allocated capacity in elements)

    int* data = this->data;
    int   size = this->size;
    int   capacity = this->capacity;

    if (capacity < 8)
    {
        // Allocate new buffer for 8 elements (32 bytes)
        int* newData = static_cast<int*>(::operator new(0x20));  // FUN_009c8e80

        if (data != nullptr)
        {
            // Copy existing elements if any
            int count = (size > 0) ? size : 0;
            for (int i = 0; i < count; ++i)
            {
                newData[i] = data[i];
            }

            // Free old buffer
            ::operator delete(data);  // FUN_009c8f10
        }

        // Update members
        this->data = newData;
        this->capacity = 8;
    }
}