// FUNC_NAME: DynamicArray::pushBack
// Function at 0x008ca280: Adds an element to a dynamic array (vector-like structure)
// Structure layout: this[0] = data pointer, this[1] = current size, this[2] = capacity
// All elements are 4 bytes (likely int or pointer)

void __thiscall DynamicArray::pushBack(int* thisPtr, undefined4* valuePtr)
{
    int capacity = thisPtr[2];
    if (thisPtr[1] == capacity)
    {
        // Resize needed: double capacity (or set to 1 if currently 0)
        int newCapacity;
        if (capacity == 0)
        {
            newCapacity = 1;
        }
        else
        {
            newCapacity = capacity * 2;
        }
        // Reallocate internal buffer (FUN_008c9f90)
        FUN_008c9f90(newCapacity);
    }
    // Calculate pointer to new element slot
    undefined4* slot = (undefined4*)(thisPtr[0] + thisPtr[1] * 4);
    thisPtr[1] = thisPtr[1] + 1; // increment size
    if (slot != (undefined4*)0x0)
    {
        *slot = *valuePtr; // copy value
    }
    return;
}