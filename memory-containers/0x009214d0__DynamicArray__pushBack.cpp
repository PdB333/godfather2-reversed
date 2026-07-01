// FUNC_NAME: DynamicArray::pushBack
// Address: 0x009214d0
// Reconstructed C++ for a dynamic array (vector) push_back operation.
// Structure layout:
//   +0x00: data pointer (int*)
//   +0x04: size (int)
//   +0x08: capacity (int)

void __thiscall DynamicArray::pushBack(int *thisPtr, int *valuePtr)
{
    int capacity = thisPtr[2]; // capacity at offset +0x08
    if (thisPtr[1] == capacity) // size == capacity
    {
        if (capacity == 0)
        {
            capacity = 1;
        }
        else
        {
            capacity = capacity * 2; // double the capacity
        }
        // Call resize function (likely reallocates and copies)
        FUN_00920b30(capacity); // address 0x00920b30: resize
    }
    // Write value at the current end
    int *writePos = (int *)(thisPtr[0] + thisPtr[1] * 4);
    thisPtr[1] = thisPtr[1] + 1; // increment size
    if (writePos != (int *)0x0)
    {
        *writePos = *valuePtr;
    }
    return;
}