// FUNC_NAME: Array::reserve
// Address: 0x00667740
// Role: Grow internal buffer capacity to at least desiredCount elements (each 4 bytes).
// Returns 0 on success, -2 on realloc failure.
// Struct layout (Array<int>):
//   +0x00: elementSize (int, always 4)
//   +0x04: capacity (int, current allocated element count)
//   +0x08: unused/padding? (not accessed here)
//   +0x0C: data (int*, pointer to allocated memory)

int __thiscall Array::reserve(int desiredCount) {
    int* newBuffer;
    int oldCapacity;
    int newCapacity;

    // Check if current capacity (<this+0x04>) is already sufficient
    if (capacity < desiredCount) {
        // Round desiredCount up to next multiple of 64 (0x40) for cache alignment
        unsigned int mask = desiredCount & 0x8000003F;
        if ((int)mask < 0) {
            mask = (mask - 1 | 0xFFFFFFC0) + 1;
        }
        newCapacity = desiredCount + (0x80 - mask);

        // Reallocate buffer at <this+0x0C> to hold newCapacity * 4 bytes
        newBuffer = (int*)_realloc(data, newCapacity * 4);
        if (newBuffer == nullptr) {
            return -2; // alloca failure
        }
        data = newBuffer;

        // Zero-initialize the newly allocated portion
        oldCapacity = capacity;
        capacity = newCapacity;
        for (int i = oldCapacity; i < capacity; i++) {
            data[i] = 0;
        }
    }
    return 0;
}