// FUNC_NAME: DynamicArray::setCapacity
// Address: 0x0098f7d0
// Role: Sets the capacity of a dynamic buffer/array. If the new capacity is larger than the current, it calls an external reallocation function (growBuffer) and updates the stored capacity. If smaller, it simply stores the new capacity (no deallocation).

class DynamicArray {
public:
    // +0x00: Pointer to allocated data (not used in this method, but implied)
    void* m_pData;
    // +0x04: Current capacity (number of elements)
    unsigned int m_capacity;

    // External function that reallocates the buffer to the given new capacity.
    // Called only when expanding.
    static void growBuffer(unsigned int newCapacity); // defined elsewhere (0x0098f4c0)

    void setCapacity(unsigned int newCapacity) {
        if (m_capacity < newCapacity) {
            // Need to grow: reallocate the buffer
            growBuffer(newCapacity);
            m_capacity = newCapacity;
        } else if (newCapacity < m_capacity) {
            // Shrinking: just update the capacity, no reallocation
            m_capacity = newCapacity;
        }
        // If equal, do nothing
    }
};