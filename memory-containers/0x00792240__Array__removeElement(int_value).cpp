// FUNC_NAME: Array::removeElement(int value)
// Address: 0x00792240
// Removes the first occurrence of 'value' from the dynamic integer array.
// The array is stored as: base pointer at +0x8, count at +0xC.
// If found and not the last element, the last element is moved to the vacated slot.
// The count is decremented unconditionally (assumes the value is always present).

void __thiscall Array::removeElement(void* this, int value) {
    uint count = *(uint*)((char*)this + 0xC); // current number of elements
    uint foundIndex = 0xFFFFFFFF; // sentinel for not found
    uint i = 0;

    if (count != 0) {
        int* array = *(int**)((char*)this + 0x8); // pointer to array of ints
        do {
            foundIndex = i; // tentative index
            if (array[i] == value) {
                break; // found
            }
            i++;
            foundIndex = 0xFFFFFFFF; // reset sentinel for next iteration
        } while (i < count);
    }

    // If the found element is not the last one, move the last element into its place.
    if (foundIndex != count - 1) {
        int* array = *(int**)((char*)this + 0x8);
        array[foundIndex] = array[count - 1];
    }

    // Decrease the element count (assumes the value was found).
    *(int*)((char*)this + 0xC) = count - 1;
}