// FUNC_NAME: FixedSizeVector::push_back
// Address: 0x004ae6f0
// Role: Adds a 20-byte element to a dynamic array (vector) with growth on capacity overflow.
// The element is passed via EDI (register) and copied into the array.

class FixedSizeVector {
public:
    // +0x00: void* m_pArray;      // pointer to allocated element buffer
    // +0x04: int   m_nSize;       // current number of elements
    // +0x08: int   m_nCapacity;   // allocated capacity (number of elements)

    // __thiscall, this in EAX, element pointer in EDI
    void push_back(void* pElement);
};

void FixedSizeVector::push_back(void* pElement) {
    // Check if need to grow
    if (m_nSize == m_nCapacity) {
        int newCapacity;
        if (m_nCapacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = m_nCapacity * 2;
        }
        // Reallocate buffer (function at 0x004aea20)
        FUN_004aea20(newCapacity);
    }

    // Copy element into the next slot (each element is 0x14 bytes)
    // Use char* for byte-level access
    char* dest = static_cast<char*>(m_pArray) + m_nSize * 0x14;
    char* src = static_cast<char*>(pElement);

    // Copy first 8 bytes
    *reinterpret_cast<unsigned long long*>(dest) = *reinterpret_cast<unsigned long long*>(src);
    // Copy next 8 bytes
    *reinterpret_cast<unsigned long long*>(dest + 8) = *reinterpret_cast<unsigned long long*>(src + 8);
    // Copy last 4 bytes
    *reinterpret_cast<int*>(dest + 16) = *reinterpret_cast<int*>(src + 16);

    // Increment size
    m_nSize++;
}