// FUNC_NAME: HandleManager::releaseHandle
// Address: 0x00610f90
// Releases a resource handle by index. Returns new reference count, or -1 on error, 0 if destroyed, 1 for sentinel.

#include <cstdint>

// Structure for each handle slot (size 0x38 = 56 bytes)
struct ResourceHandleSlot {
    int32_t refCount;      // +0x00: Reference count (1 = last reference)
    void*   resourcePtr;   // +0x04: Pointer to the actual resource
    int32_t state;         // +0x08: State (3 = ready to be destroyed?)
    // ... remaining fields (0x38 - 12 = 44 bytes) unused in this function
};

// Forward declaration for the resource destruction function
extern void destroyResource(void* resourcePtr, int32_t unkZero);

// Global array of handle slots (base address DAT_011a0f38)
extern ResourceHandleSlot g_handleSlots[0x1000]; // 4096 slots

// Release a handle. Returns new ref count, or -1 on invalid, 0 if destroyed, 1 for sentinel.
int32_t releaseHandle(uint32_t handleIndex)
{
    // Sentinel handle (0xFFFFFFFF) -> treat as already released
    if (handleIndex == 0xFFFFFFFF) {
        return 1;
    }

    // Validate handle index and slot pointer
    if (handleIndex > 0xFFF) {
        return -1;
    }

    // Check for overflow when calculating offset (the product should not wrap)
    // (Decompiled shows equality to -0x11a0f28, but likely a bounds check)
    if (handleIndex * 0x38 >= sizeof(g_handleSlots)) {
        return -1;
    }

    ResourceHandleSlot* slot = &g_handleSlots[handleIndex]; // piVar1
    if (slot == nullptr) {
        return -1;
    }

    if (slot->refCount != 1) {
        // Decrement reference count
        int32_t newRefCount = slot->refCount - 1;
        slot->refCount = newRefCount;
        return newRefCount;
    }

    // refCount == 1, so this is the last reference
    if (slot->state != 3) {
        // Not ready for destruction; bump back to 2 (prevents deletion)
        slot->refCount = 2;
        return 2;
    }

    // State is 3, destroy the resource and return 0
    destroyResource(slot->resourcePtr, 0);
    return 0;
}