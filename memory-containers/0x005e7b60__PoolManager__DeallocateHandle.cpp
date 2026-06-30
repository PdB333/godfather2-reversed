// FUNC_NAME: PoolManager::DeallocateHandle
// Function address: 0x005e7b60
// Deallocates a handle from a small pool (max 256 entries) identified by XOR of handle value.
// Returns true if successful, false if handle invalid or already free.

#define POOL_HASH_CONSTANT 0xad103100

// Global pool manager (size unknown, offsets deduced)
struct PoolManager {
    char pad_0x00[0x18];      // +0x00: unknown
    char entryFlags[256];     // +0x18: array of flags (1=used, 0=free)
    byte maxEntries;          // +0x1C: max number of entries (should be <=255)
    byte currentCount;        // +0x1D: current number of allocated entries
};

// Global pool singleton
static PoolManager* gPoolManager = (PoolManager*)0x01223504;

bool __thiscall PoolManager::DeallocateHandle(uint* handlePtr)
{
    uint handle = *handlePtr;
    uint xorIndex = handle ^ POOL_HASH_CONSTANT;

    // Check if the index is within the valid range
    if (xorIndex >= (uint)gPoolManager->maxEntries)
        return false;

    byte index = (byte)(xorIndex & 0xFF);
    byte* entryPtr = &gPoolManager->entryFlags[index];

    // Check if the entry is actually allocated
    if (*entryPtr == '\0')
        return false;

    // Mark as free and decrement count
    gPoolManager->currentCount--;
    *entryPtr = 0;
    *handlePtr = 0;     // Clear the handle so it becomes invalid
    return true;
}