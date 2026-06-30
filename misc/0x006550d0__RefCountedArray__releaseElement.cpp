// FUNC_NAME: RefCountedArray::releaseElement
// Address: 0x006550d0
// Removes an element pointer from the internal array, decrements its reference count,
// and if it reaches zero, calls the element's destructor (via vtable index 2).
void __fastcall RefCountedArray::releaseElement(int *elementPtr)
{
    uint i = 0;
    if (0 < *(int *)(this + 0x24)) { // count > 0
        int **array = *(int ***)(this + 0x2c); // pointer to array of pointers
        while (array[i] != elementPtr) {
            i++;
            if (*(int *)(this + 0x24) <= i) {
                return;
            }
        }
        // Found element at index i
        elementPtr[2] = elementPtr[2] - 1; // decrement refCount at elementPtr+8
        if (elementPtr[2] == 0) {
            // Call destructor (vtable index 2)
            (**(code **)(*elementPtr + 8))();
        }
        // Shift remaining elements left to fill the hole
        if (i < *(int *)(this + 0x24) - 1U) {
            do {
                int **currentSlot = (int **)(*(int *)(this + 0x2c) + i * 4);
                *currentSlot = currentSlot[1];
                i++;
            } while (i < *(int *)(this + 0x24) - 1U);
        }
        // Decrement count
        *(int *)(this + 0x24) = *(int *)(this + 0x24) - 1;
    }
}