//FUNC_NAME: EARSArray::reserve
// Address: 0x008defe0
// Role: Resizes the internal buffer to accommodate at least newCapacity elements (each 16 bytes). Copies existing elements, frees old buffer.

class EARSArray {
public:
    int* m_pData;       // +0x00: pointer to element data
    uint m_count;       // +0x04: number of elements currently stored
    uint m_capacity;    // +0x08: allocated capacity (max elements before reallocation)

    void __thiscall reserve(uint newCapacity);
};

// External memory functions (likely custom allocator)
void* __cdecl allocateMemory(size_t size);   // FUN_009c8e80
void  __cdecl freeMemory(void* ptr);          // FUN_009c8f10

void __thiscall EARSArray::reserve(uint newCapacity) {
    // Only grow if requested capacity exceeds current capacity
    if (m_capacity < newCapacity) {
        // Allocate new buffer: each element is 16 bytes (4 ints)
        int* newData = (int*)allocateMemory(newCapacity * 16);
        if (m_pData != nullptr) {
            // Copy existing elements (16 bytes each)
            for (uint i = 0; i < m_count; i++) {
                newData[i * 4 + 0] = m_pData[i * 4 + 0];
                newData[i * 4 + 1] = m_pData[i * 4 + 1];
                newData[i * 4 + 2] = m_pData[i * 4 + 2];
                newData[i * 4 + 3] = m_pData[i * 4 + 3];
            }
            // Free old buffer
            freeMemory(m_pData);
        }
        // Update pointer and capacity
        m_pData = newData;
        m_capacity = newCapacity;
    }
}