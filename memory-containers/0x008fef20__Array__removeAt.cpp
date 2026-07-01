// FUNC_NAME: Array::removeAt
// Function address: 0x008fef20
// Role: Removes an element from a dynamic array by shifting elements left.
// Class members: 
//   +0x00: int* m_data;    // pointer to element storage (4-byte each)
//   +0x04: uint32_t m_size; // current number of elements

class Array {
public:
    int* m_data;      // +0x00
    uint32_t m_size;  // +0x04

    // Removes element at index 'idx'. Valid if idx < m_size - 1.
    void __thiscall removeAt(uint32_t idx) {
        // Shift elements left from idx+1 to end-1
        if (idx < m_size - 1) {
            do {
                m_data[idx] = m_data[idx + 1];
                ++idx;
            } while (idx < m_size - 1);
        }
        // Decrease size
        --m_size;
    }
};