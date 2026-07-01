// FUNC_NAME: GameArray::pushBack
// Address: 0x008e6680
// Role: Adds an element to the end of a dynamic array (resizable buffer).
// This is a typical vector-like push_back implementation.
// Reallocation is performed when capacity is exhausted, doubling each time (with initial capacity 1 if starting from 0).

class GameArray {
public:
    // +0x00: base pointer to allocated buffer
    // +0x04: number of elements currently stored
    // +0x08: capacity (number of slots allocated)
    uint32_t* buffer;
    int size;
    int capacity;

    // Helper function (external, likely defined elsewhere)
    void reallocate(int newCapacity); // FUN_008e5cf0

    void pushBack(uint32_t value) {
        // Check if we need to grow the buffer
        if (size == capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            reallocate(newCapacity);
        }

        // Write the new element at the current end and increment size
        uint32_t* slot = buffer + size;
        size++;
        if (slot != nullptr) {
            *slot = value;
        }
    }
};