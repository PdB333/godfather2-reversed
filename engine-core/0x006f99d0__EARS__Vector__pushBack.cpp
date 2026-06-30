// FUNC_NAME: EARS::Vector::pushBack

// Reconstructed from Ghidra at 0x006f99d0
// Vector container implementation for EA EARS engine (32-bit)

class Vector {
    uint32_t* buffer;      // +0x00: pointer to element array
    int size;              // +0x04: number of elements
    int capacity;          // +0x08: allocated capacity

    // Internal: grow capacity to at least newCap
    void reserve(int newCap) {
        // Calls FUN_006f9120 which handles memory allocation/reallocation
        // Implementation not shown here.
    }

public:
    void pushBack(const uint32_t& value) {
        // Check if we need to grow
        if (size == capacity) {
            int newCap = (capacity == 0) ? 1 : capacity * 2;
            reserve(newCap);
        }

        // Place the element at the end
        uint32_t* slot = buffer + size;
        size++;

        if (slot != nullptr) {
            *slot = value;
        }
    }
};