// FUNC_NAME: DynamicArray::reserveCapacity
// Function address: 0x008dd700
// Role: Reserves capacity in a dynamic array, reallocating if needed.
// The class has members: data pointer (+0x00), count (+0x04), capacity (+0x08).
// The function checks if new capacity > current capacity, allocates new buffer,
// copies existing elements, frees old buffer, and updates members.

#include <cstdlib> // for malloc, free

void __thiscall DynamicArray::reserveCapacity(unsigned int newCapacity)
{
    // param_1 = this (int*)
    // param_2 = newCapacity (uint)

    // Check if current capacity is insufficient
    if (this->capacity < newCapacity)
    {
        // Allocate new buffer (size = newCapacity * sizeof(int))
        int* newBuffer = (int*)malloc(newCapacity * 4);

        // If there are existing elements, copy them
        if (this->data != nullptr && this->count > 0)
        {
            for (unsigned int i = 0; i < this->count; i++)
            {
                if (newBuffer != nullptr)
                {
                    newBuffer[i] = this->data[i];
                }
            }
        }

        // Free old buffer if it exists
        if (this->data != nullptr)
        {
            free(this->data);
        }

        // Update members
        this->data = newBuffer;
        this->capacity = newCapacity;
    }
}