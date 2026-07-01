// FUNC_NAME: GrowableArray::addUnique
// Function address: 0x008f6ed0
// Role: Adds a unique integer value to a growable array. If the value already exists, returns an existing handle.
//       Returns a 32-bit value where the low byte indicates status (1=added, 0=exists) and upper bits may encode the index.
//       Fields of the GrowableArray struct:
//       +0x00: int* data (pointer to dynamic array)
//       +0x04: uint size (number of elements)
//       +0x08: uint capacity (allocated capacity)
//       +0x0C: void* overflowHandler (optional callback when size meets capacity)

struct GrowableArray {
    int* data;                    // +0x00
    unsigned int size;            // +0x04
    unsigned int capacity;        // +0x08
    void* overflowHandler;        // +0x0C (might be a function pointer for overflow handling)
};

// External functions (callees)
void FUN_008f66c0();   // Possibly overflow handler or logging
void FUN_008f6480(unsigned int newCapacity);   // Resize/grow internal array

unsigned int __thiscall GrowableArray::addUnique(GrowableArray* this, int value) {
    unsigned int currentSize = this->size;
    unsigned int idx = 0;

    // Search for existing element
    if (currentSize != 0) {
        int* curPtr = this->data;
        do {
            if (*curPtr == value) {
                // Value already present; return a handle with low byte 0
                // Note: The original code returns (in_EAX & 0xffffff00). This implies the caller expects EAX to hold some precomputed value (likely an index).
                // In practice, this is a sign that the function was meant to return a composite handle, but EAX is uninitialized here.
                return reinterpret_cast<unsigned int>(this) & 0xffffff00; // placeholder; actual intent unclear
            }
            idx++;
            curPtr++;
        } while (idx < currentSize);
    }

    // If capacity equals current size and overflow handler is set, call it.
    if ((this->capacity == currentSize) && (this->overflowHandler != nullptr)) {
        FUN_008f66c0();
    }

    // After possible overflow handling, check if resize is needed.
    unsigned int newCapacity = this->capacity;
    if (this->size == newCapacity) {
        if (newCapacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity *= 2;
        }
        FUN_008f6480(newCapacity);
    }

    // Append the new value
    int* dest = this->data + this->size;
    unsigned int newSize = this->size + 1;
    this->size = newSize;
    if (dest != nullptr) {
        *dest = value;
    }

    // Return composite: low byte = 1 (successful add), upper 24 bits = (newSize >> 8).
    // This encoding is unusual; the index of the new element would be newSize-1, but shift is applied to newSize.
    return ( (newSize >> 8) << 8 ) | 1; // equivalent to CONCAT31((int3)(newSize>>8), 1)
}