// FUNC_NAME: createGameObject
// Address: 0x004b4230 - Likely a factory function that creates a game object or resource using a virtual allocator
// Calls a virtual function on a global allocator singleton, passing a resource ID (0x870) and a creation request structure.
// If successful, proceeds to call FUN_004b3b90 (presumably a constructor/init), else returns 0.

struct SAllocationRequest {
    uint32_t type;          // +0x00 - type of allocation (e.g., object type)
    uint32_t size;          // +0x04 - requested size in bytes
    uint32_t flags;         // +0x08 - allocation flags
};

IAllocator* GetAllocator(void); // FUN_009c8f80 - returns a pointer to a singleton allocator

void* CreateGameObject(void)
{
    IAllocator* pAllocator = GetAllocator();
    SAllocationRequest request;
    request.type  = 2;      // type 2 - maybe "game object"
    request.size  = 0x10;   // base size 0x10 (16 bytes)
    request.flags = 0;      // no special flags
    // Virtual call: pAllocator->vtable[0]?? with resource ID 0x870 and pointer to request
    int32_t result = pAllocator->Allocate(0x870, &request); // (*(code**)*pAllocator)(0x870, &request)
    if (result != 0) {
        // Allocation succeeded; now call initialization
        void* pObject = FUN_004b3b90(); // presumed constructor/initializer returning a valid pointer
        return pObject;
    }
    return 0;
}