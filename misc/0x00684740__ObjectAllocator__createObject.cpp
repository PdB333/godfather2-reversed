// FUNC_NAME: ObjectAllocator::createObject
int ObjectAllocator::createObject(int param_1, int param_2) {
    // Allocation parameters: (size, alignment, flags)
    struct AllocParams {
        int flags;   // +0x00: allocation flags (2 = maybe zero-fill?)
        int align;   // +0x04: alignment (0x10 = 16 bytes)
        int unknown; // +0x08: reserved (0)
    };
    AllocParams params;
    params.flags = 2;
    params.align = 0x10;
    params.unknown = 0;

    int handle = allocateMemory(0x130, &params, param_2); // allocate 0x130 bytes with alignment 16
    if (handle != 0) {
        // Success: initialize the object using the provided parameter
        return initializeObject(param_1);
    }
    return 0; // allocation failed
}