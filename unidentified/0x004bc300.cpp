// FUN_004bc300: HandleManager::allocateNewSlot

#include <cstdint>

// Class representing a pool of handle objects (size 0x34 each)
// Structure at this:
// +0x00: m_pElements (void*) - pointer to array of elements
// +0x04: m_count (int) - number of used slots
// +0x08: m_capacity (int) - total allocated capacity

class HandleManager {
public:
    void* m_pElements;   // +0x00
    int   m_count;       // +0x04
    int   m_capacity;    // +0x08
};

// Element structure (0x34 bytes)
struct HandleElement {
    int field_00;        // -1 on initialization
    int field_04;        // -1
    int field_08;        // -1
    int field_0C;        // 0
    int field_10;        // 0
    int field_14;        // 0
    int field_18;        // 0
    int field_1C;        // 0
    int field_20;        // 0
    int field_24;        // 0
    int field_28;        // 0
    int field_2C;        // 0
    int field_30;        // 0
};

// Forward declaration of reallocation function (called when growing the pool)
void HandleManager__grow(int newCapacity); // FUN_004bca00

// Acquire a new slot from the pool. Returns a pointer to the newly allocated element.
// This is a __thiscall member function.
void* HandleManager::allocateNewSlot() {
    // Check if we need to grow the pool
    if (m_count == m_capacity) {
        int newCapacity;
        if (m_capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = m_capacity * 2;
        }
        HandleManager__grow(newCapacity);
    }

    // Calculate pointer to the new element
    HandleElement* newElement = (HandleElement*)((uint8_t*)m_pElements + m_count * sizeof(HandleElement));
    
    if (newElement != nullptr) {
        // Initialize the element: first three fields to -1, rest to 0
        newElement->field_00 = -1;
        newElement->field_04 = -1;
        newElement->field_08 = -1;
        newElement->field_0C = 0;
        newElement->field_10 = 0;
        newElement->field_14 = 0;
        newElement->field_18 = 0;
        newElement->field_1C = 0;
        newElement->field_20 = 0;
        newElement->field_24 = 0;
        newElement->field_28 = 0;
        newElement->field_2C = 0;
        newElement->field_30 = 0;
    }

    // Return the old count (as index) and increment count
    int slotIndex = m_count;
    m_count++;
    return (void*)((uint8_t*)m_pElements + slotIndex * sizeof(HandleElement));
}