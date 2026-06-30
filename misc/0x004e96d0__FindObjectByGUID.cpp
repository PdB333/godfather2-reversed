// FUNC_NAME: FindObjectByGUID
// Address: 0x004e96d0
// Role: Looks up a pointer to an object managed by a singleton manager,
//       using a 16-byte GUID (4 x uint32) as the key.
//       Uses a hash/index function (FUN_004e1900) to locate an entry in a
//       global array of 0x18-byte structures; returns the first DWORD of that entry.

#include <cstdint>

// A GUID used throughout the EARS engine (e.g., for resources, objects).
struct GUID {
    uint32_t data[4];
};

// Internal function that maps a GUID to an index (or -1 if not found).
// FUN_004e1900
int __cdecl IndexFromGUID(const GUID* guid);

// Global pointer to the base of the manager's data.
// DATA_012054c0 holds the address of a DWORD that points to the actual data block.
extern uint32_t* g_pManagerBasePtr;

// Returns a pointer to the object associated with the given GUID, or nullptr.
// The calling convention is __cdecl (parameter passed in EAX via custom ABI).
void* __cdecl FindObjectByGUID(const GUID* pGuid) {
    GUID guidCopy = *pGuid;                     // Copy the 16 bytes locally
    int index = IndexFromGUID(&guidCopy);       // Get index in the object table

    if (index >= 0) {
        uint32_t baseAddr = *g_pManagerBasePtr; // Dereference to get the data block base
        if (baseAddr != 0) {
            // Each entry is 0x18 bytes; the object array starts at offset 0x10
            uint32_t entryOffset = 0x10 + index * 0x18;
            uint32_t* pEntry = (uint32_t*)(baseAddr + entryOffset);
            // The first DWORD of the entry is the object pointer
            return (void*)*pEntry;
        }
    }
    return nullptr;
}