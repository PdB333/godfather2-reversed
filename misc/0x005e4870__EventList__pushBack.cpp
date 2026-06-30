// FUNC_NAME: EventList::pushBack
// Address: 0x005e4870
// Role: Adds an 8-byte element (type pointer + data) to a dynamic array, resizing if full.
// The array is a member at +0x602c in some large object.
// Returns a handle encoding the new element's address with a flag (0x01 as high byte).

#include <cstdint>

// Forward declaration of internal grow function
void growArray(int newCapacity); // 0x005e70b0

// External type marker (likely a vtable or type descriptor)
extern void* TYPE_MARKER; // at LAB_004c9720

// Structure representing the dynamic array embedded in the parent object
struct EventList {
    void** m_pElements; // +0x602c: pointer to array of 8-byte pairs
    int m_nSize;             // +0x6030: current number of elements
    int m_nCapacity;         // +0x6034: allocated capacity (number of slots)
};

// __fastcall: this passed in EDX, one explicit param in stack
uint32_t __fastcall EventList_pushBack(int dummyECX, EventList* pThis, void* data) {
    int capacity = pThis->m_nCapacity;
    if (pThis->m_nSize == capacity) {
        // Full: double capacity (or set to 1 if zero)
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        growArray(newCapacity);
    }

    // Compute address of new slot
    void** pNewSlot = pThis->m_pElements + pThis->m_nSize * 2; // each element is 2 pointers (8 bytes)
    pThis->m_nSize++;

    if (pNewSlot != nullptr) {
        pNewSlot[0] = &TYPE_MARKER;  // store type marker
        pNewSlot[1] = data;          // store user data
    }

    // Encode pointer as handle: top byte = 0x01, lower 3 bytes = shift of address
    return (reinterpret_cast<uint32_t>(pNewSlot) >> 8) | 0x01000000;
}