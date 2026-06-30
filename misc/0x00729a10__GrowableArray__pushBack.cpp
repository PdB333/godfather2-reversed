// FUNC_NAME: GrowableArray::pushBack

void __thiscall GrowableArray::pushBack(void* this, void* value)
{
    // +0x0: data pointer
    // +0x4: current element count
    // +0x8: allocated capacity (in elements)
    int* dataPtr = *(int**)this;        // +0x0
    int count = *(int*)((char*)this + 4); // +0x4
    int capacity = *(int*)((char*)this + 8); // +0x8

    if (count == capacity)
    {
        // Grow capacity: double it, or set to 1 if currently 0
        int newCapacity;
        if (capacity == 0)
            newCapacity = 1;
        else
            newCapacity = capacity * 2;

        Reallocate(newCapacity);  // calls FUN_00728e80 - likely GrowableArray::reserveCapacity
    }

    // Write value at the end of the array
    void* dest = (char*)dataPtr + count * 4;
    *(int*)dest = *(int*)value;

    // Increment count
    *(int*)((char*)this + 4) = count + 1; // +0x4
}