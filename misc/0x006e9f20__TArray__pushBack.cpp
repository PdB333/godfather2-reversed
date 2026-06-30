// FUNC_NAME: TArray::pushBack

// Reconstructed from 0x006e9f20: EA EARS dynamic array push_back implementation.
// Container layout: +0x00 data (T*), +0x04 size (int), +0x08 capacity (int)
void __thiscall TArray::pushBack(void *this, void *value)
{
    int *data = *(int **)this;          // +0x00: pointer to allocated array
    int &size = *(int *)((char *)this + 4);   // +0x04: number of elements
    int &capacity = *(int *)((char *)this + 8); // +0x08: capacity

    // If full, grow the array
    if (size == capacity)
    {
        int newCapacity;
        if (capacity == 0)
            newCapacity = 1;
        else
            newCapacity = capacity * 2;
        // Grow function (FUN_006e9220)
        reallocateMemory(this, newCapacity);
    }

    // Write value at next slot
    void *slot = (char *)data + size * 4; // assuming 4-byte elements
    if (slot != nullptr)
        *(int *)slot = *(int *)value;

    size++;
}