// FUNC_NAME: ObjectPool::releaseObject
// 00610ef0 - Release a pooled object by slot index (passed in EAX)
// Each slot is 0x38 bytes; the first 4 bytes are a pointer to the object.
// Global pool at g_objectPool (address 0x011a0f38), max 0x1000 entries.

struct PoolSlot {
    void* objectPointer; // +0x00
    // remaining 0x34 bytes unknown (possibly flags, ref count, etc.)
};

// Global pool table
static PoolSlot g_objectPool[0x1000]; // at 0x011a0f38

// Forward declarations of called functions
static void preCleanupSlot();       // FUN_00616c30
static void destroyObject(void*);   // FUN_00611090
static void updatePoolAfterRelease(); // FUN_00610af0

static int releaseObject(uint slotIndex) {
    // Validate index range
    if (slotIndex >= 0x1000) {
        return 0;
    }

    int offset = slotIndex * sizeof(PoolSlot);
    // Additional safety check (original: iVar2 != -0x11a0f28)
    // This is a sentinel to prevent underflow; offset is always positive.
    if (offset == (int)(-0x011a0f38)) { // Equivalent to &g_objectPool + offset == 0
        return 0;
    }

    PoolSlot* slot = &g_objectPool[slotIndex];
    void* object = slot->objectPointer;
    if (object != nullptr) {
        preCleanupSlot();
        slot->objectPointer = nullptr;
        destroyObject(object);
        updatePoolAfterRelease();
        return 1;
    }
    return 0;
}