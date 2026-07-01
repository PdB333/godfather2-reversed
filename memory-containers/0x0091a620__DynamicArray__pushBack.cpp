// FUNC_NAME: DynamicArray::pushBack
// Function address: 0x0091a620
// Dynamic array push_back implementation (EARS engine container)
// Internal layout: +0x00 data pointer, +0x04 size, +0x08 capacity

void __thiscall DynamicArray::pushBack(int *this, undefined4 *value)
{
    int currentSize = this[1];           // +0x04: current number of elements
    int capacity = this[2];              // +0x08: allocated capacity
    
    // Check if we need to grow
    if (currentSize == capacity)
    {
        int newCapacity;
        if (capacity == 0)
        {
            newCapacity = 1;
        }
        else
        {
            newCapacity = capacity * 2;
        }
        // Reallocate buffer (FUN_00917ab0 is DynamicArray::grow)
        this->grow(newCapacity);
    }
    
    // Write new element at the end of the buffer
    int *buffer = (int *)this[0];        // +0x00: pointer to element array
    int *destination = buffer + currentSize;
    this[1] = currentSize + 1;           // increment size
    
    if (destination != (int *)0x0)       // safety check (likely compiler relic)
    {
        *destination = *value;           // copy 4 bytes (undefined4)
    }
}