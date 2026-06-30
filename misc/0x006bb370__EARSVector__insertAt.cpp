// FUNC_NAME: EARSVector::insertAt
// Address: 0x006bb370
// Role: Insert an element into a dynamic array at a specified index, shifting subsequent elements right.
// This is a member function of a custom vector class (EA EARS engine), likely equivalent to std::vector::insert.
// The vector structure has fields: m_pData (+0x00), m_capacity (+0x04), m_size (+0x08).

#include <cstdint>

// Forward declaration of growth function (FUN_006ba8b0)
void growCapacity(uint32_t newCapacity);

// Reconstructed vector class (simplified)
class EARSVector {
public:
    uint32_t* m_pData;      // +0x00: pointer to element array
    uint32_t  m_capacity;   // +0x04: allocated capacity (number of elements)
    uint32_t  m_size;       // +0x08: current number of elements

    // Insert at index, return pointer to the slot for the new element
    uint32_t* __thiscall insertAt(uint32_t index) {
        uint32_t currentSize = m_size;
        uint32_t currentCapacity = m_capacity;

        // If array is full, grow capacity
        if (currentSize == currentCapacity) {
            uint32_t newCapacity = (currentCapacity == 0) ? 1 : (currentCapacity * 2);
            growCapacity(newCapacity);   // FUN_006ba8b0
        }

        currentSize = m_size;
        // Address of the slot just past the last element (for push_back or shift)
        uint32_t* pNewEndSlot = &m_pData[currentSize];

        // If appending at the end, just increment size and return pointer to new slot
        if (index == currentSize) {
            m_size = currentSize + 1;
            return pNewEndSlot;
        }

        // Shift existing elements to the right by one to make room at 'index'
        // First, copy the last element to the new end slot (to avoid overwriting during shift)
        if (pNewEndSlot != nullptr) {
            *pNewEndSlot = *(pNewEndSlot - 1);   // duplicate last element to the new slot
        }

        // Shift elements from the end down to index+1: each element moves right by one
        // Loop from (currentSize-1) down to (index+1)
        uint32_t shiftPos = currentSize - 1;
        while (index < shiftPos) {
            m_pData[shiftPos] = m_pData[shiftPos - 1];   // copy element to the next slot
            shiftPos--;
        }

        // Update size and return pointer to the insertion slot
        m_size = currentSize + 1;
        return &m_pData[index];
    }
};