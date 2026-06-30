// FUN_00591CB0: DynamicArray::assign

class DynamicArray {
public:
    uint32_t* m_pData;       // +0x00
    uint32_t m_nCount;       // +0x04
    uint32_t m_nCapacity;    // +0x08

    // FUN_005822D0: reallocates internal buffer to at least 'newCapacity' elements
    void reserve(uint32_t newCapacity);

    // Copies all elements from 'other' into this array.
    void __thiscall assign(const DynamicArray& other)
    {
        if (this == &other)
            return;

        // Clear current element count.
        if (m_nCount != 0)
            m_nCount = 0;

        // Pre‑allocate sufficient capacity to avoid repeated growth.
        reserve(other.m_nCount);

        if (other.m_nCount != 0) {
            for (uint32_t i = 0; i < other.m_nCount; ++i) {
                // Grow array if it has reached its capacity.
                if (m_nCount == m_nCapacity) {
                    uint32_t newCap = (m_nCapacity == 0) ? 1 : m_nCapacity * 2;
                    reserve(newCap);
                }

                // Append element from source.
                m_pData[m_nCount] = other.m_pData[i];
                ++m_nCount;
            }
        }
    }
};