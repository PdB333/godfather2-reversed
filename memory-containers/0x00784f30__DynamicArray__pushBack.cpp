// FUNC_NAME: DynamicArray::pushBack
// Address: 0x00784f30
// Role: Adds an element to the end of a dynamic array, resizing the internal buffer if capacity is full.

class DynamicArray {
    uint32_t* m_data;      // +0x00: pointer to allocated array of 4-byte elements
    int       m_size;      // +0x04: number of elements currently in use
    int       m_capacity;  // +0x08: total allocated element slots

    // Resize the internal buffer to at least newCapacity elements (0x007848a0)
    void setCapacity(int newCapacity);

public:
    void pushBack(const uint32_t& value) {
        // Grow if full
        if (m_size == m_capacity) {
            int newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
            setCapacity(newCapacity);
        }
        // Write the element and advance the size
        m_data[m_size] = value;
        ++m_size;
    }
};