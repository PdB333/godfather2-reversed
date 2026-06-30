// FUNC_NAME: EntityFactory::createObject496
// Function address: 0x00685170
// Allocates an object of size 0x1F0 (496 bytes) using a custom allocator, then constructs it.
// The allocator parameters: heap type = 2, alignment = 0x10, flags = 0.
// Returns pointer to constructed object, or 0 on allocation failure.

struct AllocParams {
    int32_t heapType;   // +0x00 (value 2)
    int32_t alignment;  // +0x04 (value 0x10)
    int32_t flags;      // +0x08 (value 0)
};

// Custom allocator and constructor functions (stubs, real names unknown)
void* __cdecl allocatorAllocate(int32_t size, AllocParams* params, uint32_t heapHandle);
void* __cdecl objectConstructor(uint32_t owner);

uint32_t __cdecl createObject496(uint32_t owner, uint32_t heapHandle) {
    AllocParams allocParams;
    allocParams.heapType = 2;
    allocParams.alignment = 0x10;
    allocParams.flags = 0;

    void* allocatedMemory = allocatorAllocate(0x1F0, &allocParams, heapHandle);
    if (allocatedMemory != nullptr) {
        return (uint32_t)objectConstructor(owner);
    }
    return 0;
}