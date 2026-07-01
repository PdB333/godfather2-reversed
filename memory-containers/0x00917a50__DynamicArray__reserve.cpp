// FUNC_NAME: DynamicArray::reserve
// Function address: 0x00917a50
// Role: Reserves capacity for a dynamic array (reallocate if needed). Used in EARS engine.
// The object layout: +0x00 m_pData (int*), +0x04 m_nCount (uint), +0x08 m_nCapacity (uint)

class DynamicArray {
public:
    int* m_pData;      // +0x00
    uint m_nCount;     // +0x04
    uint m_nCapacity;  // +0x08

    void __thiscall reserve(uint newCapacity) {
        // Only resize if current capacity is insufficient
        if (m_nCapacity < newCapacity) {
            // Allocate new array (each element is 4 bytes)
            int* newData = (int*)heapAlloc(newCapacity * 4);  // FUN_009c8e80

            if (m_pData != nullptr) {
                // Copy existing elements
                uint i = 0;
                int* src = m_pData;
                int* dst = newData;
                if (m_nCount != 0) {
                    do {
                        // Guard against null destination (shouldn't happen)
                        if (dst != nullptr) {
                            *dst = *src;
                        }
                        i++;
                        src++;
                        dst++;
                    } while (i < m_nCount);
                }
                // Free old array
                heapFree(m_pData);  // FUN_009c8f10
            }

            // Update pointer and capacity
            m_pData = newData;
            m_nCapacity = newCapacity;
        }
        // Return; count unchanged
    }

private:
    // External heap functions (from EARS runtime)
    static void* heapAlloc(size_t size);   // FUN_009c8e80
    static void  heapFree(void* ptr);      // FUN_009c8f10
};