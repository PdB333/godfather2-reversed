// FUNC_NAME: ResourceManager::initializeHandle
// Address: 0x006af760
// Initializes a local resource handle with a global value and zero fields,
// then calls an internal initialization function (likely a constructor or reset).

#include <cstdint>

// Global data reference (type unknown, assumed uint32_t)
static uint32_t DAT_0112a640;

// Represents the 12-byte structure assembled on the stack
struct ResourceHandle {
    uint32_t field_0;   // +0x00: from global DAT_0112a640
    uint32_t field_4;   // +0x04: set to 0
    uint32_t field_8;   // +0x08: set to 0
};

// Forward declaration of callee
void FUN_00408a00(ResourceHandle* handle, int32_t flags);

void ResourceManager::initializeHandle(void) {
    ResourceHandle handle;
    handle.field_0 = DAT_0112a640;
    handle.field_4 = 0;
    handle.field_8 = 0;
    FUN_00408a00(&handle, 0);  // Internal init, flag = 0
    return;
}