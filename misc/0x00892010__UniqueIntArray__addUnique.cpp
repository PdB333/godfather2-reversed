// FUNC_NAME: UniqueIntArray::addUnique

void __thiscall UniqueIntArray::addUnique(int param_1, int param_2) // param_1: this (offset +0x8: array, +0xC: count, +0x10: capacity)
{
    uint currentCount = *(uint*)(param_1 + 0xC);
    uint index = 0;

    // Check if the value already exists in the array
    if (currentCount != 0) {
        int* arrayPtr = *(int**)(param_1 + 8);
        do {
            if (*arrayPtr == param_2) {
                // Duplicate found; return without adding
                // Note: The original condition (-1 < (int)uVar2) was always true, so this effectively returns unconditionally
                return;
            }
            index++;
            arrayPtr++;
        } while (index < currentCount);
    }

    // Value not found; prepare to add it
    uint capacity = *(uint*)(param_1 + 0x10);
    if (currentCount == capacity) {
        // Need to grow the array
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        // Call resize helper (likely reallocates internal array and updates capacity)
        FUN_00891ce0(newCapacity); // This function probably updates m_array and m_capacity
    }

    // Insert the new value at the end
    int* insertPos = (int*)(*(int*)(param_1 + 8) + currentCount * 4);
    *(uint*)(param_1 + 0xC) = currentCount + 1; // increment count
    if (insertPos != (int*)0x0) {
        *insertPos = param_2;
    }

    return;
}