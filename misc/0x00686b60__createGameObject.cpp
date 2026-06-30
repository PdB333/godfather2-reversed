// FUNC_NAME: createGameObject

// Allocates an object from a memory pool and initializes it.
// param_1: pointer to memory for object (may be pre-allocated or stack)
// param_2: allocation tag or context identifier
// Returns 0 on failure, otherwise result of initialization.
int __cdecl createGameObject(void *objectMemory, int allocTag) {
    int allocResult;
    int initResult;
    // Allocation flags: [2 = heap?, 0x10 = some flag, 0 = alignment?]
    int allocFlags[3] = {2, 0x10, 0};

    // Request memory block of size 0xf0 (240 bytes) from pool
    allocResult = MemAlloc(0xf0, allocFlags, allocTag);
    if (allocResult != 0) {
        // Construct/initialize the object at the given memory location
        initResult = InitGameObject(objectMemory);
        return initResult;
    }
    return 0;
}