// FUNC_NAME: DynamicArray::insert
// Address: 0x006bee40
// Reconstructed C++ for a dynamic array (pointer vector) insert method.
// Structure offsets: [0] buffer (pointer to array), [4] size, [8] capacity.

#include <cstdint>

class DynamicArray {
public:
    uint32_t* buffer;    // +0x00
    uint32_t size;       // +0x04
    uint32_t capacity;   // +0x08

    // Internal reallocation helper (assumed from callee at 0x006b1e10)
    void reallocate(uint32_t newCapacity);

    // Insert a slot at the given index and return pointer to it.
    // If index == size, appends. Otherwise shifts elements to make room.
    uint32_t* insert(uint32_t index) {
        uint32_t cap = capacity;
        if (size == cap) {
            // Double capacity if non-zero, else set to 1.
            cap = (cap == 0) ? 1 : cap * 2;
            reallocate(cap);  // Grow buffer
        }

        // Pointer to the slot one past the last element.
        uint32_t* lastSlot = buffer + size;

        if (index == size) {
            // Appending: just increment size and return that slot.
            ++size;
            return lastSlot;
        }

        // Shift elements to the right to free up index.
        // First, duplicate the last element into the next slot (since we will shift).
        if (lastSlot != nullptr) {  // Buffer exists (already checked via size/cap)
            *lastSlot = *(lastSlot - 1);
        }

        uint32_t currentSize = size;
        // Start from the second-to-last element downward.
        while (--currentSize > index) {
            *(buffer + currentSize) = *(buffer + currentSize - 1);
        }

        ++size;  // Account for the new slot
        return buffer + index;  // Return pointer to the now-empty slot
    }
};

// Note: The reallocate function is assumed to update buffer, capacity, and preserve existing elements.