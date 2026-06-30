// FUNC_NAME: MemoryPool::initialize

// 0x0064f120 - Static initializer for a memory pool (size 0x3ff8, descriptor at g_poolDesc)
// This function allocates a 12-byte descriptor and a buffer of size 0x3ff8.
// It is called during system startup by various managers.

#include <cstdint>

// Global pool descriptor pointer
static uint32_t* g_poolDesc = nullptr; // DAT_01223ca8
static uint32_t g_poolSize = 0x3ff8;   // _DAT_01223cac
static uint32_t g_poolFreeCount = 0;   // DAT_01223cb0 (likely a counter)
static uint32_t g_poolChunkSize = 0xc; // DAT_01223cb4
static uint32_t g_poolAllocFlags = 0;  // DAT_01223cb8

// Memory allocation functions (from EARS engine)
extern uint32_t* __cdecl _allocDescriptor(uint32_t size); // FUN_009c8e50
extern uint32_t __cdecl _allocBuffer(uint32_t size); // FUN_009c8e80

// Returns a pointer to the global pool descriptor pointer (handle)
uint32_t** MemoryPool::initialize()
{
    // Set the pool buffer size
    g_poolSize = 0x3ff8;

    // Allocate the pool descriptor (12 bytes)
    uint32_t* descriptor = _allocDescriptor(0xc);
    if (descriptor == nullptr) {
        g_poolDesc = nullptr;
        return &g_poolDesc;
    }

    // Allocate the actual buffer
    uint32_t buffer = _allocBuffer(0x3ff8);
    descriptor[1] = buffer; // +0x04: pointer to buffer

    // Store descriptor globally
    g_poolDesc = descriptor;

    // Initialize descriptor fields:
    descriptor[0] = 0;      // +0x00: free list head index or similar
    descriptor[2] = 0;      // +0x08: allocated count or flags

    // Initialize global state
    g_poolFreeCount = 0;
    g_poolChunkSize = 0xc;
    g_poolAllocFlags = 0;

    return &g_poolDesc;
}