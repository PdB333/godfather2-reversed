// FUNC_NAME: removeElementFromArray
void __thiscall SomeArray::removeValue(int value)
{
    unsigned int currentCount = *(unsigned int*)(this + 0x14); // +0x14: number of elements
    unsigned int index = 0;

    if (currentCount != 0) {
        int* arrayPtr = *(int**)(this + 0x10); // +0x10: pointer to array of ints
        // Linear search for the value
        while (*arrayPtr != value) {
            index++;
            arrayPtr++;
            if (currentCount <= index) {
                return; // Value not found
            }
        }
        // If found, remove by swapping with the last element (if not already last)
        if ((int)index >= 0) {
            if (index != currentCount - 1) {
                // Move last element into the removed slot
                *(int*)(*(int*)(this + 0x10) + index * 4) =
                    *(int*)(*(int*)(this + 0x10) + (currentCount - 1) * 4);
            }
            // Decrement count
            *(int*)(this + 0x14) = *(int*)(this + 0x14) - 1;
        }
    }
}