// FUNC_NAME: AllocateAndConstructSomething  
// Address: 0x008837a0  
// Allocates memory (0x120 bytes) with alignment parameters, then calls a constructor or initializer.  
// param_1 – likely a 'this' pointer for the object being constructed  
// param_2 – additional argument passed to the constructor  
// Returns the result of the constructor, or 0 if allocation fails.

int AllocateAndConstructSomething(int param_1, int param_2)
{
    // Local struct likely describes allocation requirements (alignment, size hint, flags)
    struct AllocParams {
        int alignment;  // +0x00
        int sizeHint;   // +0x04
        int flags;      // +0x08
    } allocParams;

    allocParams.alignment = 2;
    allocParams.sizeHint = 0x10;   // perhaps a hint for the allocator
    allocParams.flags = 0;

    int* allocatedMemory = (int*)FUN_009c8ed0(0x120, &allocParams);  // allocate 288 bytes
    if (allocatedMemory != 0) {
        // Note: allocatedMemory is not passed to the constructor; only the check is used.
        // Possibly the allocation ensures a global heap is ready, or the object uses internal memory.
        int result = FUN_008834d0(param_1, param_2);   // constructor/initializer
        return result;
    }
    return 0;
}