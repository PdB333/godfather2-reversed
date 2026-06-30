// FUNC_NAME: RegisterFunctionPointer
// Function address: 0x00429480
// Purpose: Inserts a pointer into a global pointer table, advancing the table's current insertion index.
// The table is stored at a global base (DAT_01206880) with a "current insertion pointer" at offset +0x14.

#include <cstdint>

// Global base pointer to the table manager structure (e.g., function pointer dispatch table)
extern void* g_tableManagerBase; // Address: 0x01206880

// Inserts a pointer into the table and advances the insertion position by 4 bytes (one pointer).
void RegisterFunctionPointer(void* ptr)
{
    // The current insertion pointer is stored at offset 0x14 from the table manager base.
    // It is a pointer to a location within the table where the next entry should be written.
    uint32_t** currentSlotPtr = reinterpret_cast<uint32_t**>(
        reinterpret_cast<uint8_t*>(g_tableManagerBase) + 0x14
    );

    // Write the new pointer into the current slot (the memory pointed to by currentSlotPtr).
    *(*currentSlotPtr) = reinterpret_cast<uint32_t>(ptr);

    // Advance the current insertion pointer by one slot (size of a pointer, 4 bytes).
    (*currentSlotPtr)++;
}