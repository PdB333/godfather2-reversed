// FUNC_NAME: DynamicArray::reserve
// Function address: 0x008b0020
// Role: Ensure the dynamic array has capacity for at least 'newCapacity' elements.
// All elements are 4-byte values (int/pointer size). If current capacity < newCapacity,
// reallocate memory, copy existing elements, and free old memory.

#include <cstdint>

// Forward declarations for memory allocation/deallocation functions.
// They are probably custom allocators in the EARS engine.
extern "C" void* memAlloc(uint32_t size);   // FUN_009c8e80
extern "C" void  memFree(void* ptr);        // FUN_009c8f10

// Dynamic array class (known pattern: pointer to data, element count, capacity)
// Offsets: +0x00 = m_pData (4-byte pointer), +0x04 = m_count (uint32), +0x08 = m_capacity (uint32)
class DynamicArray {
public:
    int*     m_pData;      // +0x00
    uint32_t m_count;      // +0x04
    uint32_t m_capacity;   // +0x08

    // Ensure capacity is at least newCapacity
    void __thiscall reserve(uint32_t newCapacity) {
        if (m_capacity < newCapacity) {
            // Allocate new buffer (newCapacity * 4 bytes)
            int* newData = (int*)memAlloc(newCapacity * sizeof(int));
            if (m_pData != nullptr) {
                // Copy existing elements
                uint32_t i = 0;
                int* dest = newData;
                if (m_count != 0) {
                    do {
                        if (dest != nullptr) {
                            *dest = m_pData[i];
                        }
                        i++;
                        dest++;
                    } while (i < m_count);
                }
                // Free old buffer
                memFree(m_pData);
            }
            // Update pointer and capacity
            m_pData = newData;
            m_capacity = newCapacity;
        }
    }
};