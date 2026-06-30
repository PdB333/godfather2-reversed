// FUNC_NAME: DynamicArray::removeElement
void __thiscall DynamicArray::removeElement(int value)
{
    uint count = *(uint *)(this + 0x44); // +0x44: number of elements
    uint i = 0;
    if (count != 0) {
        // Search for the element to remove
        while (*(int *)(this + 4 + i * 4) != value) { // +0x04: start of array
            i++;
            if (count <= i) {
                return; // Not found
            }
        }
        // If found and index is valid
        if ((i != 0xffffffff) && (i < count)) {
            // Shift elements left to fill the gap
            if (i < count - 1) {
                do {
                    *(int *)(this + 4 + i * 4) = *(int *)(this + 8 + i * 4); // shift left
                    i++;
                } while (i < *(int *)(this + 0x44) - 1);
            }
            // Decrement count
            *(int *)(this + 0x44) = *(int *)(this + 0x44) - 1;
        }
    }
    return;
}