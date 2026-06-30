// FUNC_NAME: Vector<uint32_t>::reserve
// Function address: 0x005e6ff0
// Role: Ensure dynamic array capacity; reallocates if needed.
// Class layout: this+0: uint32_t* data (array pointer)
//              this+4: uint32_t size  (current number of elements)
//              this+8: uint32_t capacity (allocated element count)

void __thiscall Vector::reserve(uint32_t newCapacity)
{
    uint32_t* oldData;
    uint32_t* newData;
    uint32_t oldSize;

    // Only reallocate if new capacity is larger than current
    if (newCapacity <= this->capacity)
        return;

    // Allocate new memory (FUN_009c8e80 likely allocates raw bytes)
    newData = (uint32_t*)FUN_009c8e80(newCapacity * sizeof(uint32_t));
    oldData = this->data;
    oldSize = this->size;

    if (oldData != nullptr)
    {
        // Copy existing elements
        for (uint32_t i = 0; i < oldSize; i++)
        {
            if (newData != nullptr)
            {
                newData[i] = oldData[i];
            }
        }
        // Free old memory (FUN_009c8f10 likely frees allocation)
        FUN_009c8f10(oldData);
    }

    // Update pointers and capacity
    this->data = newData;
    this->capacity = newCapacity;
}