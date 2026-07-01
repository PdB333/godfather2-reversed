// FUNC_NAME: DynamicArray::pushBack
// Function address: 0x008fd2c0
// Role: Push a 4-byte value onto a dynamic array. Grows capacity if full (doubles, or sets to 1 if empty).
// Struct layout (this):
//   +0x00: int* data        (pointer to array of ints)
//   +0x04: int size         (number of elements currently stored)
//   +0x08: int capacity     (allocated capacity)
void __thiscall DynamicArray::pushBack(int* dataArray, int* valuePtr)
{
    int capacity = dataArray[2];       // +0x08
    int size = dataArray[1];           // +0x04

    if (size == capacity)
    {
        // Grow capacity: double it, or set to 1 if currently 0
        int newCapacity = (capacity == 0) ? 1 : (capacity * 2);
        // Call internal reallocate function (likely handles memory allocation)
        reallocate(newCapacity);        // FUN_008fc8f0
        // Note: after reallocation, dataArray[0] (data pointer) may have changed
    }

    int* slot = (int*)(dataArray[0] + size * 4);   // +0x00 pointer + offset
    dataArray[1] = size + 1;                       // increment size

    if (slot != nullptr)
    {
        *slot = *valuePtr;                         // copy the 4-byte value
    }

    return;
}