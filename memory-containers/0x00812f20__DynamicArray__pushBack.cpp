// FUNC_NAME: DynamicArray::pushBack

class DynamicArray {
public:
    uint32* data;       // +0x00: pointer to element array (each element = 16 bytes)
    uint32 count;        // +0x04: number of elements currently stored
    uint32 capacity;     // +0x08: maximum number of elements before reallocation

    // Insert a 16-byte element (passed as 4 × uint32) at the end.
    // This function grows the array if capacity is exhausted.
    void pushBack(const uint32* element) {
        uint32 newCapacity;

        // Check if array is full
        if (count == capacity) {
            if (capacity == 0) {
                newCapacity = 1;
            } else {
                newCapacity = capacity * 2;
            }
            // Resize internal buffer to newCapacity (calls FUN_00812790 internally)
            grow(newCapacity);
        }

        // Pointer to the new slot (after the last element)
        uint32* slot = reinterpret_cast<uint32*>(
            reinterpret_cast<uintptr_t>(data) + count * 16
        );

        // Copy 16 bytes (4 uint32) from source element
        slot[0] = element[0];
        slot[1] = element[1];
        slot[2] = element[2];
        slot[3] = element[3];

        // Increase element count
        count++;
    }

    // Helper: reallocate the internal buffer to hold newCapacity elements.
    // Implementation not shown; corresponds to FUN_00812790.
    void grow(uint32 newCapacity);
};