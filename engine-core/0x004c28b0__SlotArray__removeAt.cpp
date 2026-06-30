// FUNC_NAME: SlotArray::removeAt
// Removes an element at the given index from a fixed-size array of 8-byte elements.
// The array is stored inline at thisPtr+0x00, capacity 64 elements (0x200 bytes).
// Count is at thisPtr+0x200.
void __fastcall SlotArray::removeAt(int thisPtr, unsigned int index)
{
    int* countPtr = (int*)(thisPtr + 0x200); // +0x200: m_count
    int count = *countPtr;

    if (index >= (unsigned int)count) {
        return; // index out of bounds
    }

    if (index < (unsigned int)(count - 1)) {
        // Shift elements left to fill the gap
        int* element = (int*)(thisPtr + index * 8); // pointer to current element (two ints)
        do {
            element[0] = element[2]; // copy first int from next element
            element[1] = element[3]; // copy second int from next element
            index++;
            element += 2; // advance by 8 bytes (2 ints)
        } while (index < (unsigned int)(count - 1));
    }

    // Decrement count
    count--;
    *countPtr = count;

    // Zero out the now-unused last slot
    int* lastElement = (int*)(thisPtr + count * 8);
    if (lastElement != (int*)0x0) {
        lastElement[0] = 0;
        lastElement[1] = 0;
    }
}