// FUNC_NAME: DynamicArray::reserve
// Address: 0x008f1820
// Role: Reserves capacity for a dynamic array, allocating new memory if needed and copying existing elements.

class DynamicArray {
public:
    int* m_pData;      // +0x00: pointer to element array
    unsigned int m_nCount;    // +0x04: number of elements currently stored
    unsigned int m_nCapacity; // +0x08: allocated capacity (number of elements)

    void reserve(unsigned int newCapacity) {
        // Only grow if new capacity exceeds current capacity
        if (m_nCapacity < newCapacity) {
            // Allocate new memory block (each element is 4 bytes)
            int* newData = (int*)allocateMemory(newCapacity * 4);
            if (m_pData != nullptr) {
                // Copy existing elements to new array
                unsigned int i = 0;
                int* dest = newData;
                if (m_nCount != 0) {
                    do {
                        if (dest != nullptr) {
                            *dest = m_pData[i];
                        }
                        i++;
                        dest++;
                    } while (i < m_nCount);
                }
                // Free old memory
                freeMemory(m_pData);
            }
            // Update pointer and capacity
            m_pData = newData;
            m_nCapacity = newCapacity;
        }
    }
};