// FUNC_NAME: GrowingArray::pushBack
// Address: 0x00729ab0
// Role: Adds an integer (or pointer) to a dynamic array, doubling capacity if full

void __thiscall GrowingArray::pushBack(int value)
{
    // Check if array is full (size == capacity)
    if (this->size == this->capacity)
    {
        int newCapacity;
        if (this->capacity == 0)
        {
            newCapacity = 1;
        }
        else
        {
            newCapacity = this->capacity * 2;
        }
        // Reallocate buffer to new capacity (implemented in FUN_00728e80)
        this->grow(newCapacity);
    }

    // Write value at current end buffer[size], then increment size
    // +0x1c: buffer (int*), +0x20: size (int), +0x24: capacity (int)
    this->buffer[this->size] = value;
    this->size++;
}