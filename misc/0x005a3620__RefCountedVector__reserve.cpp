// FUNC_NAME: RefCountedVector::reserve
// Address: 0x005a3620
// Reserves capacity for at least newCapacity elements.
// The container stores pointers to reference‑counted objects (0x30 bytes each).
// Structure offsets: +0x00: size (number of used elements), +0x04: capacity,
// +0x08: data pointer, +0x0C: inline buffer start (for small object optimisation).

void RefCountedVector::reserve(int newCapacity) {
    int* self = this; // in_EAX
    int capacity = self[1]; // offset +0x04
    if (capacity >= newCapacity) {
        return;
    }
    // If new capacity is tiny just update the stored capacity without reallocation.
    if (newCapacity < 2) {
        self[1] = newCapacity;
        return;
    }

    // Allocate new data block (each slot is an int*).
    int* newData = (int*)allocate(newCapacity * 4); // FUN_005a1580(0)

    // Copy existing elements from old data to new block.
    // The source pointer is old_data + size * 4 (end of used region).
    // This may be a memmove that also initialises the unused tail.
    int size = self[0]; // offset +0x00
    copyElements(self[2] + size * 4, newData); // FUN_005a32d0

    self[1] = newCapacity; // update capacity

    // Free old data if it wasn't the inline buffer.
    if (self[2] != (int*)(self + 3)) { // inline buffer starts at &self[3]
        free((void*)self[2]); // FUN_005a1580 (used as free)
    }
    self[2] = newData; // update data pointer

    // The slot immediately past the last used element (newData + size * 4)
    // is examined and cleared if it contained a previous pointer.
    int* endSlot = newData + size * 4;
    if ((int)endSlot != newCapacity) { // address comparison with parameter (may be a null/stack check)
        int* ptr = (int*)*endSlot;
        if (ptr) {
            (*ptr)--; // decrement reference count
            if (*ptr == 0) {
                refCountDestroy(ptr); // FUN_005a1b40
                operator delete(ptr, 0x30); // (*DAT_0119caf8)
            }
        }
        *endSlot = 0; // clear the slot
    }
}