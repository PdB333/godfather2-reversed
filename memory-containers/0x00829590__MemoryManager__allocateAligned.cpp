// FUNC_NAME: MemoryManager::allocateAligned
// Address: 0x00829590
// Allocates a block of memory with custom alignment/flags, returns a handle or pointer.
// The function obtains a singleton MemoryManager, calls a virtual method with size 0x420
// and a parameter struct (alignment=2, some size=0x10, flags=0). On success, returns
// the result of a post-processing call (likely retrieving the allocated block).

// Forward declaration of the global memory manager singleton getter
static void* GetMemoryManager();

// Parameter structure for the allocation virtual call
struct MemAllocParams {
    int alignment;  // +0x00 (alignment requirement)
    int subSize;    // +0x04 (internal size or alignment type)
    int flags;      // +0x08 (flags: 0 = default)
};

// Virtual function table layout for MemoryManager
// vtable[0] = AllocateFunction (void* manager, int size, MemAllocParams* params) -> int

// The function itself (__cdecl, no this)
int MemoryManager_allocateAligned() {
    // Get the singleton memory manager
    void* manager = GetMemoryManager();  // resolves to FUN_009c8f80
    
    // Build allocation parameters
    MemAllocParams params;
    params.alignment = 2;      // align to 2 bytes? (unusual, but as seen)
    params.subSize   = 0x10;   // might be an internal check or alignment granularity
    params.flags     = 0;      // no special flags
    
    // Call virtual function [0] on manager with (0x420, &params)
    // 0x420 is the requested allocation size (1056 bytes)
    int status = (*(int (*)(void*, int, MemAllocParams*))*(void**)manager)(manager, 0x420, &params);
    
    if (status != 0) {
        // Success – finalize and return the allocated handle/pointer
        return FUN_009d6dd0();  // likely returns the memory address or handle
    }
    
    return 0;  // allocation failed
}