// FUNC_NAME: MemoryManager::registerAllocation
// Address: 0x006bf8f0
// Role: Registers a memory block with the global memory manager for tracking.
// The block is described by a small AllocationInfo structure (size=2, alignment=0x10, flags=0).

#include <cstdint>

// Forward declaration of the MemoryManager class (from EARS::Framework)
class MemoryManager;

// Returns a pointer to the global MemoryManager singleton (vtable pointer)
MemoryManager* GetMemoryManager(); // FUN_009c8f80

// Allocation descriptor used by the memory manager
struct AllocationInfo {
    uint32_t size;       // Size in bytes
    uint32_t alignment;  // Required alignment (e.g., 0x10 = 16 bytes)
    uint32_t flags;      // Additional flags (unused here)
};

void MemoryManager::registerAllocation(void* ptr) {
    MemoryManager* mgr = GetMemoryManager();
    AllocationInfo info = {2, 0x10, 0};
    
    // Call the first vtable entry (likely a virtual method registerBlock)
    (mgr->vtable->registerBlock)(ptr, &info);
}