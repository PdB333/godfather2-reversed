// FUNC_NAME: DynamicIntArray::remove
void __thiscall DynamicIntArray::remove(int value) {
    // +0x98: count (number of elements)
    // +0x94: arr (pointer to array of ints)
    uint count = *(uint *)(this + 0x98);
    uint i = 0;
    uint foundIndex = 0xFFFFFFFF; // -1

    if (count != 0) {
        int *arr = *(int **)(this + 0x94);
        do {
            foundIndex = i;
            if (arr[i] == value) {
                break;
            }
            i++;
            foundIndex = 0xFFFFFFFF;
        } while (i < count);
    }

    // If found and not the last element, replace with the last element
    if (foundIndex != count - 1) {
        int *arr = *(int **)(this + 0x94);
        arr[foundIndex] = arr[count - 1];
    }

    // Decrement count
    *(int *)(this + 0x98) = count - 1;
}