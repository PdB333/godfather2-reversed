// FUNC_NAME: SortedArray::insert
// Function address: 0x822a60
// Role: Insert an element into a sorted dynamic array, resizing if needed, and re-sort after insertion if more than one element.

#include <stdlib.h>

class SortedArray {
public:
    int* m_pBuffer;      // +0x08: pointer to array of ints
    int m_nCount;        // +0x0C: number of elements
    int m_nCapacity;     // +0x10: current capacity (max elements before reallocation)

    void insert(int value);
};

// External functions:
// Reallocates the buffer to new capacity (updates m_pBuffer and m_nCapacity)
void resizeArray(int newCapacity);
// Comparison function for qsort (ascending order of ints)
int compareInts(const void* a, const void* b);

void __thiscall SortedArray::insert(int value) {
    int newCap;
    int* pDest;

    // Check if we need to grow the array
    if (m_nCount == m_nCapacity) {
        if (m_nCapacity == 0) {
            newCap = 1;
        } else {
            newCap = m_nCapacity * 2;
        }
        resizeArray(newCap); // This should update m_pBuffer and m_nCapacity
    }

    // Write new element at end
    pDest = m_pBuffer + m_nCount * 4; // Actually int* already, so just m_pBuffer + m_nCount
    m_nCount++;
    if (pDest != nullptr) {
        *pDest = value;
    }

    // Sort if more than one element
    if (m_nCount > 1) {
        qsort(m_pBuffer, m_nCount, 4, compareInts);
    }
}