// FUNC_NAME: Array12::pushBack
// Address: 0x00846cc0
// Role: Appends a 12-byte element to a dynamically growing array.
// Fields (int* this): [0] data pointer, [4] size, [8] capacity
// Each element is 12 bytes (8+4). Reallocation done by FUN_00846550.

void __thiscall Array12::pushBack(int *this, const uint8_t *element) {
    int size = this[1];
    int capacity = this[2];
    if (size == capacity) {
        int newCapacity;
        if (capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }
        // Reallocate the internal array to newCapacity elements (12 bytes each)
        FUN_00846550(newCapacity);
        // After realloc, this[0] and this[2] are updated by the callee.
    }
    // Compute destination pointer: base + size * 12
    uint8_t *dest = (uint8_t *)this[0] + size * 12;
    // Increment size
    this[1] = size + 1;
    if (dest != nullptr) {
        *(uint64_t *)dest = *(uint64_t *)element;       // copy first 8 bytes
        *(uint32_t *)(dest + 8) = *(uint32_t *)(element + 8); // copy next 4 bytes
    }
}