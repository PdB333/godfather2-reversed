// FUNC_NAME: GrowableArray::pushBack

// Function address: 0x00849f40
// Reconstructed push_back for a dynamic array (likely GrowableArray<T>).
// Structure layout:
//   +0x00: T* data          (pointer to allocated array)
//   +0x04: unsigned int size (number of elements stored)
//   +0x08: unsigned int capacity (allocated capacity)

void __thiscall GrowableArray::pushBack(void* this, const void* element)
{
    unsigned int* size = static_cast<unsigned int*>(this) + 1;   // offset 0x04
    unsigned int* capacity = static_cast<unsigned int*>(this) + 2; // offset 0x08
    void** data = static_cast<void**>(this);                      // offset 0x00

    // Check if we need to grow
    if (*size == *capacity)
    {
        unsigned int newCapacity;
        if (*capacity == 0)
        {
            newCapacity = 1;
        }
        else
        {
            newCapacity = *capacity * 2;
        }
        // Reallocate the internal buffer (FUN_00849880 handles the reallocation)
        GrowableArray::grow(newCapacity);
    }

    // Write the new element at the next position
    void* slot = *data + (*size) * 4;  // assuming elements are 4 bytes (uint32)
    if (slot != nullptr)
    {
        *static_cast<unsigned int*>(slot) = *static_cast<const unsigned int*>(element);
    }
    ++(*size);
}