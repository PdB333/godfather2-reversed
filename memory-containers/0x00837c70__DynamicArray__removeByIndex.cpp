// FUNC_NAME: DynamicArray::removeByIndex
// Address: 0x00837c70
// Role: Removes an element from a dynamic array by index, swapping with the last element to maintain O(1) removal.
// Structure: Assuming DynamicArray has members: int* data (offset 0x00) and int size (offset 0x04).

void __thiscall DynamicArray::removeByIndex(int* thisPtr, int index)
{
    int* data = (int*)thisPtr[0]; // +0x00: pointer to array data
    int& size = thisPtr[1];       // +0x04: current number of elements

    // Only copy last element if index is not the last one
    if (index != size - 1)
    {
        data[index] = data[size - 1];
    }
    size--;
}