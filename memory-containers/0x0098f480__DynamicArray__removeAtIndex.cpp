// FUNC_NAME: DynamicArray::removeAtIndex
void __thiscall DynamicArray::removeAtIndex(int *thisPtr, uint index)
{
    // thisPtr layout:
    // +0x00: pointer to element array (each element 8 bytes)
    // +0x04: number of elements (size)

    int *dataPtr = (int *)*thisPtr;          // array base
    uint size = thisPtr[1];                  // current element count

    // Shift all elements after the removed one left by one slot (8 bytes each)
    if (index < size - 1) {
        do {
            // Copy element at index+1 to index
            *(long long *)(dataPtr + index * 2) = *(long long *)(dataPtr + (index + 1) * 2);
            index++;
        } while (index < size - 1);
    }

    thisPtr[1] = size - 1;  // Decrease element count
}