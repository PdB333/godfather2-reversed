// FUNC_NAME: DynamicArray::reserve

#include <cstdlib>

// Dynamic array with int elements (4 bytes each)
// Layout:
//   +0x00: int* m_pData
//   +0x04: int m_nSize
//   +0x08: int m_nCapacity
class DynamicArray {
public:
    int* m_pData;
    int m_nSize;
    int m_nCapacity;

    // Reserves at least 'newCapacity' slots, reallocating if necessary.
    // Assumes elements are 4 bytes (int). Preserves existing data.
    void reserve(int newCapacity) {
        if (m_nCapacity < newCapacity) {
            // Allocate new buffer
            int* pNewData = (int*)malloc(newCapacity * sizeof(int));
            if (m_pData != NULL) {
                // Copy existing elements
                int count = m_nSize;
                for (int i = 0; i < count; i++) {
                    if (pNewData != NULL) {
                        pNewData[i] = m_pData[i];
                    }
                }
                // Free old buffer
                free(m_pData);
            }
            // Update pointers and capacity
            m_pData = pNewData;
            m_nCapacity = newCapacity;
        }
    }
};