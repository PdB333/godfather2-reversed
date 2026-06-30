// FUNC_NAME: GlobalObjectList::AppendEntry

// Function address: 0x005c9d50
// Appends an 8-byte entry to a sequential list managed by a global structure.
// The global pointer at 0x01206880 points to a structure whose field at offset +0x14
// is a write cursor (pointer to next free slot). Each entry consists of a vtable
// pointer (from PTR_LAB_011261d4) followed by a supplied 4-byte data value.

#include <cstdint>

// Global data pointer (0x01206880)
extern void* g_pGlobalStruct;

// Vtable address constant (0x011261d4)
extern void* g_Vtable;

// Description: Writes a vtable pointer and an integer data value into the next
//              slot of the global list and advances the cursor.
void AppendEntry(uint32_t data)
{
    // Pointer to the cursor field (offset +0x14 from the global structure)
    uint32_t* cursorFieldPtr = reinterpret_cast<uint32_t*>(
        static_cast<uint8_t*>(g_pGlobalStruct) + 0x14
    );

    // Dereference cursor to get the current write location
    uint32_t* writePtr = reinterpret_cast<uint32_t*>(*cursorFieldPtr);

    // Write vtable address
    *writePtr = reinterpret_cast<uint32_t>(&g_Vtable);

    // Advance cursor past the vtable pointer
    *cursorFieldPtr += sizeof(uint32_t);

    // Get new write location
    writePtr = reinterpret_cast<uint32_t*>(*cursorFieldPtr);

    // Write the data value
    *writePtr = data;

    // Advance cursor past the data
    *cursorFieldPtr += sizeof(uint32_t);
}