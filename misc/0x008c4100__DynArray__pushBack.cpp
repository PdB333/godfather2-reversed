// FUNC_NAME: DynArray::pushBack

#include <cstddef> // for size_t

// Global variable used to initialize new elements
extern int g_ItemDefaultValue;

// Forward declaration of internal functions
void* DynArray_grow(int newCapacity); // FUN_008c2080
void DynArray_clearElement(void* element); // FUN_009c8f10: releases resources if non-null

class DynArray {
public:
    // +0x00: pointer to dynamically allocated array of elements (each 0x1c bytes)
    void* m_pData;
    // +0x04: number of elements currently in array
    int m_nCount;
    // +0x08: capacity of allocated array (number of elements that fit)
    int m_nCapacity;
    
    /**
     * Appends a new default-initialized element to the end of the array.
     * Grows the array if necessary.
     * @return Pointer to the newly added element.
     */
    void* pushBack() {
        // Check if we need to grow
        if (m_nCount == m_nCapacity) {
            int newCapacity = (m_nCapacity == 0) ? 1 : (m_nCapacity * 2);
            DynArray_grow(newCapacity);
        }
        
        // Calculate pointer to the new element slot
        void* newElement = static_cast<char*>(m_pData) + m_nCount * 0x1C;
        
        // Initialize the new element (fields at given offsets)
        int* fields = static_cast<int*>(newElement);
        fields[0] = g_ItemDefaultValue;       // +0x00: type/ID
        fields[1] = 0;                        // +0x04: field1
        fields[2] = 0;                        // +0x08: field2
        *reinterpret_cast<unsigned char*>(fields + 3) = 0; // +0x0C: byte field3
        fields[4] = 0;                        // +0x10: field4 (pointer?)
        fields[5] = 0;                        // +0x14: field5
        fields[6] = 0;                        // +0x18: field6
        
        // Release any old resources that might have been in field4 (null-safe)
        DynArray_clearElement(reinterpret_cast<void*>(fields[4]));
        fields[4] = 0; // reset again (redundant)
        fields[6] = 0; // reset again (redundant)
        
        // Increment count
        int oldCount = m_nCount;
        m_nCount = oldCount + 1;
        
        // Return pointer to the new element
        return static_cast<char*>(m_pData) + oldCount * 0x1C;
    }
};