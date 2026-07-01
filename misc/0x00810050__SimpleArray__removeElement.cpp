// FUNC_NAME: SimpleArray::removeElement
// Address: 0x00810050
// Removes the first occurrence of a given value from a dynamic array of ints.
// The array is stored as a pointer at +0x10 and count at +0x14.
void __thiscall SimpleArray::removeElement(int this, int valueToRemove)
{
    int* arrayPtr = *(int**)(this + 0x10);   // +0x10: pointer to array of ints
    int count = *(int*)(this + 0x14);        // +0x14: number of elements

    if (arrayPtr != arrayPtr + count) {
        int* endPtr = arrayPtr + count;
        int* current = arrayPtr;

        // Find the element to remove
        while (*current != valueToRemove) {
            current++;
            if (current == endPtr) {
                return; // Not found
            }
        }

        // Shift remaining elements left
        int* shiftSrc = current + 1;
        int* shiftDst = current;
        int elementsToMove = (endPtr - shiftSrc); // number of elements after the removed one
        for (int i = 0; i < elementsToMove; i++) {
            *shiftDst = *shiftSrc;
            shiftDst++;
            shiftSrc++;
        }

        // Decrement count
        *(int*)(this + 0x14) = count - 1;
    }
}