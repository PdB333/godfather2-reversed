// FUNC_NAME: Array::reserve (capacity increase)
// Address: 0x005efc20
// Role: Ensures the dynamic array has at least the specified capacity. If current capacity is less, reallocates and copies existing elements.

#include <cstdlib> // For malloc, free (used via EA allocator in reality)

// Structure of the dynamic array (size: 12 bytes):
// +0x00: int* data;       // pointer to elements
// +0x04: uint32_t size;   // number of elements currently stored
// +0x08: uint32_t capacity; // allocated capacity (in elements)

void __thiscall Array::reserve(uint32_t newCapacity)
{
    // Check if we need to grow
    if (this->capacity < newCapacity)
    {
        // Allocate new block (each element is 4 bytes, so newCapacity * 4)
        int* newData = (int*)eaAlloc(newCapacity * 4); // FUN_009c8e80
        if (newData)
        {
            // Copy existing elements if any
            if (this->data != nullptr && this->size > 0)
            {
                for (uint32_t i = 0; i < this->size; i++)
                {
                    newData[i] = this->data[i];
                }
            }
        }
        // Free old block
        if (this->data)
        {
            eaFree(this->data); // FUN_009c8f10
        }
        // Update pointers and capacity
        this->data = newData;
        this->capacity = newCapacity;
    }
}