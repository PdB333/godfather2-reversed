// FUNC_NAME: Array::resize
// Function address: 0x00944280
// Role: Resizes the array to a new logical size. If the new size is larger than current, it grows the capacity via reallocation.
// Field at +0x04: m_size (uint) - current logical size of the array.

class Array {
private:
    uint m_size; // +0x04

    // Helper to grow internal capacity (likely reallocates or allocates new buffer)
    void growCapacity(uint newCapacity); // Address: 0x00941b90

public:
    void resize(uint newSize) {
        if (m_size < newSize) {
            // Need to grow capacity to accommodate new size
            growCapacity(newSize);
            m_size = newSize;
        } else if (newSize < m_size) {
            // Shrinking: just update logical size, no reallocation
            m_size = newSize;
        }
        // If equal, do nothing
    }
};