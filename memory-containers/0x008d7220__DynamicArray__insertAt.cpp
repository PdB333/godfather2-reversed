// FUNC_NAME: DynamicArray::insertAt
// Address: 0x008d7220
// This function inserts a new element at the given index, shifting subsequent elements to the right.
// Returns a pointer to the new element slot (for in-place construction).
// Element size is 0x18 (24 bytes).

class DynamicArray {
public:
    // +0x00: data pointer
    // +0x04: size (number of elements)
    // +0x08: capacity (allocated element count)
    void* data;         // offset 0x00
    uint32_t size;      // offset 0x04
    uint32_t capacity;  // offset 0x08

    // Element type: 24 bytes (three 8-byte fields)
    struct Element {
        uint64_t field0; // used as undefined8 (8 bytes)
        uint64_t field1; // +0x08
        uint64_t field2; // +0x10
    };

    // Grow the internal buffer to the new capacity (implemented elsewhere at 0x008d6f40)
    void grow(uint32_t newCapacity);

    // Insert an element at the specified index; returns pointer to the new slot.
    Element* insertAt(uint32_t index) {
        // If full, grow (double or 1 if currently empty)
        if (size == capacity) {
            uint32_t newCap = (capacity == 0) ? 1 : (capacity * 2);
            grow(newCap);
        }

        // If inserting at the end, just increment size and return the last slot.
        if (index == size) {
            size++;
            return &((Element*)data)[index];
        }

        // Shift elements to make room:
        // First, copy the last element one position beyond the current end (temporary overflow).
        Element* lastSlot = &((Element*)data)[size];
        if (lastSlot != nullptr) {
            // Copy 24 bytes from the previous element (size-1) into the overflow slot.
            // Using three 8-byte assignments to mimic the assembly.
            lastSlot->field0 = lastSlot[-1].field0;
            lastSlot->field1 = lastSlot[-1].field1;
            lastSlot->field2 = lastSlot[-1].field2;
        }

        // Shift all elements from (size-1) down to index one position to the right.
        uint32_t shiftCount = size - index - 1; // number of elements to move
        if (index < size - 1) {
            Element* src = &((Element*)data)[size - 1]; // start from last valid element
            for (uint32_t i = 0; i < shiftCount; i++) {
                // Move element at src-1 to src (right shift)
                // Since we already placed the last element at the overflow, we shift backwards.
                // Assembly does: copy src[-1] to src
                src->field0 = src[-1].field0;
                src->field1 = src[-1].field1;
                src->field2 = src[-1].field2;
                src--; // move left one slot
            }
        }

        // Update size and return pointer to the insertion slot.
        size++;
        return &((Element*)data)[index];
    }
};