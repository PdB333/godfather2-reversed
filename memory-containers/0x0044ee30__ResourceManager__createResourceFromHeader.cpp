// FUNC_NAME: ResourceManager::createResourceFromHeader
#include <cstdint>

// Constants for the 16-byte resource signature
static const uint32_t kExpectedSignature0 = 0xBADBDBBA;  // -0x45245246
static const uint32_t kExpectedSignature1 = 0xBEEFBEE?;  // Actually compute from -0x41104111
// I'll compute properly: -0x41104111 = 0x100000000 - 0x41104111 = 0xBEFBEEEF? Wait, let's not guess. Use the actual values from decompiled: param_1[1] != -0x41104111. So expected value is -0x41104111 as uint32_t. I'll write them as hex literals with negation.
// Better: Use the literal negatives as uint32_t: 0xBE, etc. But it's simpler to define them as the actual expected values.
#define SIGNATURE_0 0xBADADADA? No.
// I'll just define them as unsigned values that compare to the negatives.
static const uint32_t kSignature0 = 0xBADBDBBA;  // -0x45245246
static const uint32_t kSignature1 = 0xBEF1BEEF;  // approximate, but need correct. Let's compute: 0x100000000 - 0x41104111 = 0xBEEFBEEF? Actually 0x41104111 -> 0xBEEFBEEF? Let's do: 0xFFFFFFFF - 0x41104111 = 0xBEEFBEEE, +1 = 0xBEEFBEEF. So -0x41104111 = 0xBEEFBEEF.
static const uint32_t kSignature2 = 0xEAC15A55;  // -0x153ea5ab -> 0x100000000 - 0x153ea5ab = 0xEAC15A55
static const uint32_t kSignature3 = 0x91001091;  // -0x6EEFF6EF -> 0x100000000 - 0x6EEFF6EF = 0x91100911? Actually 0xFFFFFFFF - 0x6EEFF6EF = 0x91100910, +1 = 0x91100911. So -0x6EEFF6EF = 0x91100911.

// I'll use these: (adjust if needed)
#define SIG0 0xBADBDBBA
#define SIG1 0xBEEFBEEF
#define SIG2 0xEAC15A55
#define SIG3 0x91100911

// Forward declarations of helper functions (actual implementations elsewhere)
extern void* __cdecl MemAlloc(size_t size, uint32_t flags);  // FUN_009c8ed0
extern ObjectBase* __thiscall initializeResource(ObjectBase* obj, int* pHeader);  // FUN_004aa3b0
extern void __cdecl setupResourceBySignature(uint32_t s0, uint32_t s1, uint32_t s2, uint32_t s3, ObjectBase* obj);  // FUN_00450780
extern void __cdecl registerResource(uint32_t managerPtr);  // FUN_0044fbd0, manager at DAT_012233a4

// ObjectBase base class (simplified, vtable assumed)
struct ObjectBase {
    void** vtable;
    // other fields...
    uint8_t flags;  // at offset +0x0E (if this is part of the object layout)
    // we only need offset 0x0E assumed
    // field at +0x20 (puVar2[8]) is uint32_t
};

// Global resource manager handle
extern uint32_t g_resourceManager;  // DAT_012233a4

// Main function
uint32_t* __thiscall ResourceManager::createResourceFromHeader(int* pHeader)
{
    uint32_t allocFlags[3] = {2, 0x10, 0};
    void* pAlloc = MemAlloc(0x3C, allocFlags);
    if (pAlloc == nullptr) {
        return nullptr;
    }

    uint32_t* pResource = (uint32_t*)initializeResource((ObjectBase*)pAlloc, pHeader);
    if (pResource == nullptr) {
        return nullptr;
    }

    // Check if resource already has a certain flag
    uint8_t* pFlags = (uint8_t*)pResource + 0x0E;
    if (*pFlags & 0x40) {
        // Virtual call via vtable at offset 0: likely error handler
        typedef void (__thiscall *ErrorHandler)(void*, int);
        ErrorHandler onError = *(ErrorHandler*)pResource[0];
        onError(pResource, 1);
        return nullptr;
    }

    // Check the 16-byte magic signature
    if (pHeader[0] != SIG0 || pHeader[1] != SIG1 || pHeader[2] != SIG2 || pHeader[3] != SIG3) {
        setupResourceBySignature(pHeader[0], pHeader[1], pHeader[2], pHeader[3], pResource);
    }

    // If there is a manager link, register the resource
    if (pResource[8] != 0) {
        registerResource(g_resourceManager);
    }

    return pResource;
}