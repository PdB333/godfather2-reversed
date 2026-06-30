// FUNC_NAME: getGlobalObjectByTypeId

// Reconstructed C++ for function at 0x00556650
// Retrieves a global object (likely a singleton) identified by type ID 0x802.
// Calls FUN_004af8c0 to initialize a temporary buffer with object data, then returns the first DWORD.

#include <cstdint>

uint32_t getGlobalObjectByTypeId()
{
    uint32_t buffer[3]; // 12-byte buffer for global object data
    FUN_004af8c0(buffer, 0x802); // Initialize buffer for type 0x802
    return buffer[0]; // Return first element (likely pointer or handle)
}