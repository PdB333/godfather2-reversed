// FUNC_NAME: DynamicArray::pushBack
// Address: 0x00953b80
// Role: Inserts an element at the end of a dynamic array (vector-style), doubling capacity if full.

void __thiscall DynamicArray::pushBack(int *this, int *element) // element pointed to by param_2
{
    int size = this[1];      // +0x04: current number of elements
    int capacity = this[2];  // +0x08: allocated capacity

    // If the array is full, grow the buffer 
    if (size == capacity)
    {
        int newCapacity;
        if (capacity == 0)
            newCapacity = 1;
        else
            newCapacity = capacity * 2;

        // Reallocate internal buffer to new capacity (member function)
        this->reallocate(newCapacity);
    }

    // Compute address of the new element slot and copy the value
    int *slot = (int *)(this[0] + size * 4); // +0x00: buffer pointer
    this[1] = size + 1; // increment size
    if (slot != nullptr)
    {
        *slot = *element;
    }
}