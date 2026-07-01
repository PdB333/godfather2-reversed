// FUNC_NAME: removeElementAtIndex
// Function address: 0x0093a120
// Role: Removes an element at a given index from a dynamic array of 8-byte elements.
// The array is stored as a pointer (offset 0) and a count (offset 4).
// Elements are shifted left to fill the gap, then count is decremented.

void __thiscall removeElementAtIndex(int* this, uint index)
{
    // Only shift if the element is not the last one
    if (index < this[1] - 1U) {
        do {
            // Shift element at (index+1) to position index
            uint* src = (uint*)(this[0] + (index + 1) * 8);
            uint* dst = (uint*)(this[0] + index * 8);
            dst[0] = src[0];
            dst[1] = src[1];
            index++;
        } while (index < this[1] - 1U);
    }
    // Decrement the element count
    this[1] = this[1] - 1;
    return;
}