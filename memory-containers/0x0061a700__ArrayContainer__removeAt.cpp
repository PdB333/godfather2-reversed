// FUNC_NAME: ArrayContainer::removeAt
// Function address: 0x0061a700
// Removes an element at a given index from a container storing 20-byte elements.
// Container layout:
//   +0x00: pointer to element array (char*)
//   +0x04: number of elements (unsigned int)
void __fastcall ArrayContainer::removeAt(void *this, unsigned int index) {
    unsigned int count = *(unsigned int*)((char*)this + 4); // +0x04

    if (index < count - 1) {
        char *array = *(char**)this; // +0x00
        // Shift elements left by 20 bytes (element size = 0x14)
        memmove(array + index * 0x14,
                array + (index + 1) * 0x14,
                0x14);
    }

    // Decrement the count
    *(unsigned int*)((char*)this + 4) = count - 1;
}