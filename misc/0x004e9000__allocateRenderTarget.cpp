// FUNC_NAME: allocateRenderTarget
// Function address: 0x004e9000
// Role: Allocates a render target or streaming buffer with given parameters.
//       Calls memory manager singleton to create a resource handle (size 0x6000),
//       then if the pool (type 0x20) is available, finalizes allocation with specific alignment.
//       Returns resource handle (or 0 on failure).

uint32 allocateRenderTarget(void)
{
    // Get the memory manager singleton
    MemoryManager* pMemMgr = MemoryManager::getInstance(); // calls FUN_009c8f80
    if (!pMemMgr)
        return 0;

    // Creation parameters: (width=2, height=4, unknownFlags=0)
    struct CreateParams {
        uint32 width;
        uint32 height;
        uint32 flags;
    } params;
    params.width = 2;
    params.height = 4;
    params.flags = 0;

    // Virtual call to create resource handle (e.g., allocate a render target or buffer of size 0x6000)
    uint32 hResource = pMemMgr->createResource(0x6000, &params); // via vtable

    // Check if the memory pool for type 0x20 is available (e.g., "staging heap")
    bool bPoolReady = MemoryManager::isPoolAvailable(0x20); // calls FUN_009c8e50
    if (bPoolReady)
    {
        // Finalize allocation: attach memory to handle with size 0x6000, alignment 0x30, and pool flags 4
        hResource = MemoryManager::allocateMemory(hResource, 0x6000, 0x30, 4); // calls FUN_004abe90
        return hResource;
    }

    return 0; // pool not ready, allocation failed
}