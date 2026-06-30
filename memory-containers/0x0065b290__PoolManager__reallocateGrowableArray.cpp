// FUNC_NAME: PoolManager::reallocateGrowableArray
// Address: 0x65b290
// Reallocates the global pool buffer to hold at least requestedElementCount elements of 8 bytes each.
// Capacity is rounded up to the next multiple of 16 elements.
// Called from FUN_0065a940 (likely a method that adds elements to the pool).
#include <cstdlib>
#include <cstring>

// Global variables: pool capacity (number of 8-byte slots) and pointer to buffer
static unsigned int g_poolCapacity = 0;      // DAT_01223350
static void* g_poolBuffer = nullptr;         // DAT_01223354

// Helper: copies old data to new buffer (size = oldCapacity * 8 bytes)
static void copyPoolData(void* dest, const void* src, unsigned int count) {
    if (src) {
        memcpy(dest, src, count * 8);
    }
}

void reallocatePool(unsigned int requestedElementCount) {
    if (g_poolCapacity >= requestedElementCount) {
        return;
    }

    // Round up to next multiple of 16 elements
    unsigned int newCapacity = (requestedElementCount + 0xF) & ~0xF;

    // Allocate new buffer: each element is 8 bytes
    void* newBuffer = malloc(newCapacity * 8);
    void* oldBuffer = g_poolBuffer;

    // Temporary swap: set global buffer to new before calling copy function
    g_poolBuffer = newBuffer;

    // Copy old data into new buffer (FUN_0065b3c0 does this)
    copyPoolData(newBuffer, oldBuffer, g_poolCapacity);

    // Restore old buffer pointer for freeing
    g_poolBuffer = oldBuffer;
    free(oldBuffer);

    // Commit new capacity and buffer
    g_poolCapacity = newCapacity;
    g_poolBuffer = newBuffer;
}