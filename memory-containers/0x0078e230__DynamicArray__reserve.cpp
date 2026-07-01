// FUNC_NAME: DynamicArray::reserve
#include <cstdlib>

class DynamicArray {
    int* m_data;       // +0x00: pointer to allocated memory
    int m_count;       // +0x04: number of elements currently stored
    int m_capacity;    // +0x08: allocated capacity (in elements)

public:
    // Grow capacity if needed; preserves existing elements
    void reserve(int newCapacity) {
        if (m_capacity < newCapacity) {
            int* newData = (int*)malloc(newCapacity * sizeof(int));
            if (m_data != nullptr) {
                int i = 0;
                int* src = m_data;
                int* dst = newData;
                while (i < m_count) {
                    if (newData != nullptr) {
                        *dst = *src;
                    }
                    i++;
                    dst++;
                    src++;
                }
                free(m_data);
            }
            m_data = newData;
            m_capacity = newCapacity;
        }
    }
};