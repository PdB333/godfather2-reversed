// FUNC_NAME: UnorderedArray::removeIndex
void UnorderedArray::removeIndex(void* this, int index) {
    // Structure layout:
    // +0x00: int* data (pointer to dynamic array of 32-bit elements)
    // +0x04: int size (current number of elements)
    int** thisPtr = (int**)this; // treat as pointer to int* for data
    int* data = *thisPtr;        // offset 0
    int size = *(int*)((char*)this + 4); // offset 4

    if (index != size - 1) {
        // Move the last element into the slot being removed (fast unordered removal)
        data[index] = data[size - 1];
    }
    // Decrease count
    *(int*)((char*)this + 4) = size - 1;
}