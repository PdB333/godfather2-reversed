// FUNC_NAME: EARSArray::insertSlot
// Function address: 0x004f1690
// Role: Inserts a new empty slot at a given index into the global array of 8-byte elements.
//        Returns a pointer to the allocated slot; the caller is expected to fill it immediately.
//        If index == count, the slot is appended at the end.
//        Otherwise, elements from index to count-1 are shifted right by one, preserving the original
//        element at index (which will be overwritten by the caller).
// Global state:
//   s_pBuffer   (DAT_01218f28) – base pointer of the element array
//   s_count     (DAT_01218f2c) – number of used slots
//   s_capacity  (DAT_01218f30) – total allocated capacity (in elements)
// Called function: growArray() (0x004f1460) expands the capacity when needed.

#include <cstdint>

// Static globals representing the array state (extracted from Ghidra addresses)
static uint8_t* s_pBuffer;   // DAT_01218f28
static uint32_t s_count;     // DAT_01218f2c
static uint32_t s_capacity;  // DAT_01218f30

// Forward declaration of the capacity-growth helper
static void growArray();

void* EARSArray::insertSlot(uint32_t index)   // index is passed in ESI
{
    // Ensure there is room for a new element
    if (s_count == s_capacity) {
        growArray();
    }

    if (index != s_count) {
        // ---------- Shift elements to make a hole at 'index' ----------
        // 1) Save the last element to the end of the array to avoid data loss during the shift
        uint32_t* pDest = reinterpret_cast<uint32_t*>(s_pBuffer + s_count * 8);
        uint32_t* pSrc  = reinterpret_cast<uint32_t*>(s_pBuffer + (s_count - 1) * 8);
        pDest[0] = pSrc[0];
        pDest[1] = pSrc[1];

        // 2) Shift elements from s_count-1 down to index+1 right by one slot
        for (uint32_t i = s_count - 1; i > index; i--) {
            uint32_t* pCur = reinterpret_cast<uint32_t*>(s_pBuffer + i * 8);
            uint32_t* pPrev = reinterpret_cast<uint32_t*>(s_pBuffer + (i - 1) * 8);
            pCur[0] = pPrev[0];
            pCur[1] = pPrev[1];
        }
        // Slot at 'index' now contains its original data; caller will overwrite it.
    }

    // Increase the element count and return a pointer to the allocated slot
    s_count++;
    return reinterpret_cast<void*>(s_pBuffer + index * 8);
}