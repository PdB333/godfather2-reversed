// FUNC_NAME: MemoryManager::allocateAlignedMemory
// Function address: 0x004e9000
// Role: Allocates memory with alignment and flags, then initializes a sub-block if a specific pool exists.
// Uses global memory manager singleton, checks for a pool of size 0x20, and if present, calls an initialization function.

#include <cstdint>

// Forward declarations of engine functions
class MemoryManager;
MemoryManager* getMemoryManager(); // FUN_009c8f80
bool checkPoolExists(uint32_t poolId); // FUN_009c8e50, returns non-zero if pool exists
void initializeMemoryBlock(void* ptr, uint32_t size, uint32_t alignment, uint32_t flags); // FUN_004abe90

struct AllocationParams {
    int32_t alignment; // +0x00: alignment requirement
    int32_t flags;     // +0x04: allocation flags (e.g., type tags)
    int32_t reserved;  // +0x08: reserved field, currently 0
};

class MemoryManager {
public:
    // Virtual function: Allocate(size, params)
    // vtable index 0
    virtual void* Allocate(uint32_t size, AllocationParams* params) = 0;
};

// allocateAlignedMemory : allocates a 0x6000-byte block with alignment 2 and flags 4.
// If the pool for allocation of size 0x20 exists, it initializes the first 0x30 bytes with alignment 4.
// Otherwise returns 0 (allocation failure?).
void* allocateAlignedMemory() {
    MemoryManager* memMgr = getMemoryManager(); // Get singleton memory manager
    
    AllocationParams params;
    params.alignment = 2;   // align to 2 bytes
    params.flags = 4;       // flags (e.g., from pool type)
    params.reserved = 0;    // unused
    
    // Call virtual allocate function with size 0x6000 (24KB) and parameters
    void* result = memMgr->Allocate(0x6000, &params);
    
    // Check if a specific pool (maybe for small blocks) is available
    if (checkPoolExists(0x20)) {
        // Initialize a sub-block: starting at result, size 0x6000, with alignment 0x30 ??, flags 4
        // This likely sets up some internal structure within the allocated memory
        initializeMemoryBlock(result, 0x6000, 0x30, 4);
        return result;
    }
    return 0; // Allocation failed or pool not available
}