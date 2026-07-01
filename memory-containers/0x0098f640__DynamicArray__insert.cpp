// FUNC_NAME: DynamicArray::insert
// Address: 0x0098f640
// Role: Insert an element at a given index in a dynamic array of 8-byte elements.
// Structure offsets:
//   +0x00: data (pointer to array of 8-byte elements)
//   +0x04: size (number of elements currently stored)
//   +0x08: capacity (allocated element count)

uint32_t* __thiscall DynamicArray::insert(uint32_t index)
{
    int* data = this->data;
    int size = this->size;
    int capacity = this->capacity;

    // Grow if full
    if (size == capacity)
    {
        int newCapacity;
        if (capacity == 0)
            newCapacity = 1;
        else
            newCapacity = capacity * 2;
        this->grow(newCapacity);  // FUN_0098f4c0
        data = this->data;        // data pointer may have changed after reallocation
    }

    // If inserting at the end, just append
    if (index == size)
    {
        this->size = size + 1;
        return (uint32_t*)(data + index * 2);  // each element is 2 uint32_t (8 bytes)
    }

    // Shift elements to the right to make room
    uint32_t* slot = (uint32_t*)(data + index * 2);
    if (slot != nullptr)
    {
        // Copy the element from the previous slot into the current slot
        slot[0] = slot[-2];
        slot[1] = slot[-1];
    }

    // Continue shifting from the end down to index+1
    uint32_t current = size;
    while (current--, index < current)
    {
        uint32_t* dest = (uint32_t*)(data + current * 2);
        dest[0] = *(uint32_t*)(data + (current - 1) * 2);
        dest[1] = dest[-1];
    }

    this->size = size + 1;
    return (uint32_t*)(data + index * 2);
}