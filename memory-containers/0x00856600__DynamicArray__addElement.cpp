// FUNC_NAME: DynamicArray::addElement
// Function address: 0x00856600
// Purpose: Add an element of size 0x70 bytes to a dynamic array. 
// The array structure at param_1 (this) has:
//   [0] = pointer to element data (mData)
//   [1] = current count (mCount)
//   [2] = capacity with flags in top 2 bits (mCapacityAndFlags)
// Element structure (size 0x70):
//   +0x00: unknown (possibly header or reserved, not copied from source)
//   +0x04: some integer
//   +0x10: sub-object (size? copied via function at 0x008542d0)
//   +0x60: some integer

void __thiscall DynamicArray::addElement(int* thisPtr, int* sourceElement)
{
    int* data      = (int*)thisPtr[0];                 // mData
    int   count    = thisPtr[1];                       // mCount
    int   capacity = thisPtr[2] & 0x3FFFFFFF;          // mask out flags

    // If array is full, grow it (element size 0x70)
    if (count == capacity) {
        // FUN_00aa4190 - likely growArray(this, elementSize)
        growArray(thisPtr, 0x70);
        data = (int*)thisPtr[0]; // re-fetch after possible reallocation
    }

    // Compute address of new slot
    char* newSlot = (char*)data + count * 0x70;

    // Increment count
    thisPtr[1] = count + 1;

    // Copy fields from source element
    // Skip first 4 bytes (offset 0x00)
    *(int*)(newSlot + 4) = *(int*)((char*)sourceElement + 4);   // copy int at offset 4
    // Copy sub-object starting at offset 0x10 (function handles size and assignment)
    copySubObject((void*)(newSlot + 0x10), (void*)((char*)sourceElement + 0x10));
    // Copy int at offset 0x60
    *(int*)(newSlot + 0x60) = *(int*)((char*)sourceElement + 0x60);
}