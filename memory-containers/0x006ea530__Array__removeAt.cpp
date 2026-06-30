// FUNC_NAME: Array::removeAt
void __thiscall Array::removeAt(int *this, uint index)
{
    // this[0] = pointer to array of 4-byte elements
    // this[1] = current number of elements (size)
    uint size = this[1];

    // Only shift if index is before the last element
    if (index < size - 1) {
        // Shift elements left by one starting from index
        do {
            // Copy element at (index+1) to index
            *(int *)(this[0] + index * 4) = *(int *)(this[0] + (index + 1) * 4);
            index = index + 1;
        } while (index < size - 1);
    }

    // Decrement size
    this[1] = size - 1;
}