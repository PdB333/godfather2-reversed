// FUNC_NAME: getEngineDataFromTLS
#include <intrin.h>
#pragma intrinsic(__readfsdword)

// Reads a DWORD from a per-thread engine data structure.
// FS:[0x2C] is the thread-local storage (TLS) pointer to an array of pointers.
// The first pointer in that array (double dereference) gives the base address of
// the engine instance. Then offset 0x28 is read and returned.
uint32_t getEngineDataFromTLS(void)
{
    uint32_t tlsSlot = __readfsdword(0x2C);               // FS segment offset
    uint32_t engineBase = *(uint32_t*)*(uint32_t**)tlsSlot; // double indirection
    return *(uint32_t*)(engineBase + 0x28);               // field at +0x28
}