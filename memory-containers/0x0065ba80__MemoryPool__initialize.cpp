// FUNC_NAME: MemoryPool::initialize
// Address: 0x0065ba80
// Initializes a fixed-block memory pool allocator with block size 0xC and pool size 0x1000

#include <cstdint>

// Global pool data
struct MemoryPool {
    int32_t freeHead;      // +0x00: index of first free block, -1 if none
    uint8_t* poolBuffer;   // +0x04: pointer to allocated pool memory
    int32_t freeCount;     // +0x08: number of free blocks
};

// Global state
extern MemoryPool* gPool;          // DAT_01223b90
extern int32_t gPoolBlockSize;     // DAT_01223b9c (0xC)
extern int32_t gPoolTotalSize;     // DAT_01223b94 (0x1000)
extern int32_t gPoolFreeBlocks;    // DAT_01223b98

// External allocation functions
extern "C" void* __cdecl allocMem(size_t size);              // FUN_009c8e50
extern "C" void* __cdecl allocAlignedMem(size_t size);       // FUN_009c8e80

void* MemoryPool::initialize() {
    gPoolTotalSize = 0x1000;
    
    // Allocate pool control block (12 bytes)
    MemoryPool* pool = (MemoryPool*)allocMem(sizeof(MemoryPool));
    if (pool == nullptr) {
        return nullptr;
    }
    
    // Allocate the actual pool memory buffer
    uint8_t* buffer = (uint8_t*)allocAlignedMem(0x1000);
    pool->poolBuffer = buffer;
    
    gPool = pool;
    pool->freeHead = 0;          // Initially all blocks free, first free is index 0
    pool->freeCount = 0;         // Will be calculated on first use? Actually set to 0
    
    gPoolFreeBlocks = 0;         // Global free count
    gPoolBlockSize = 0xC;        // Each block is 12 bytes
    // gPoolSize is already set, but there's also a global at DAT_01223ba0 set to 0 (unused?)
    
    return &gPool;               // Returns address of the global pointer (singleton pattern)
}