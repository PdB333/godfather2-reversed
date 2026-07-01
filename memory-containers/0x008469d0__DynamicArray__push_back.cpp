// FUNC_NAME: DynamicArray::push_back
// Address: 0x008469d0
// Role: Appends a 12-byte element to a dynamic array, resizing if necessary.

class DynamicArray {
public:
    int* m_pData;      // +0x00: pointer to array of 12-byte elements
    int m_nSize;       // +0x04: current number of elements
    int m_nCapacity;   // +0x08: allocated capacity (max elements before realloc)

    // External reallocation function (likely resizes internal buffer)
    void reallocate(int newCapacity); // FUN_00846550

    void push_back(const void* element) {
        // Check if we need to grow
        if (m_nSize == m_nCapacity) {
            int newCapacity = (m_nCapacity == 0) ? 1 : m_nCapacity * 2;
            reallocate(newCapacity);
        }

        // Calculate write position (base + size * elementSize)
        // elementSize = 0xC (12 bytes)
        char* dest = reinterpret_cast<char*>(m_pData) + m_nSize * 0xC;
        const char* src = reinterpret_cast<const char*>(element);

        // Copy first 8 bytes, then next 4 bytes (total 12)
        *reinterpret_cast<uint64_t*>(dest) = *reinterpret_cast<const uint64_t*>(src);
        *reinterpret_cast<uint32_t*>(dest + 8) = *reinterpret_cast<const uint32_t*>(src + 8);

        m_nSize++;
    }
};