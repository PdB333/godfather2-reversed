// FUNC_NAME: EARSArray::grow
// Address: 0x005e18b0
// Reconstructs a member function that grows an internal array to a minimum capacity of 20 elements.
// This is likely part of a dynamic array container (EARSArray) with fields at:
//   +0x00: int* data
//   +0x04: int  size
//   +0x08: int  capacity
// The function ensures capacity >= 20 by reallocating if needed, copying existing elements.

void EARSArray::grow()
{
    // Check if capacity is less than 20
    if (this->capacity < 20)
    {
        // Allocate new buffer for 20 integers (0x50 bytes = 20 * 4)
        int* newData = (int*)operator new[](0x50);

        // If old data exists, copy existing elements to new buffer
        if (this->data != nullptr)
        {
            for (int i = 0; i < this->size; i++)
            {
                newData[i] = this->data[i];
            }
            // Free old buffer
            operator delete[](this->data);
        }

        // Update data pointer and new capacity
        this->data = newData;
        this->capacity = 20;
    }
    // Implicitly, if capacity already >= 20, do nothing
}