// FUNC_NAME: MemoryManager::allocateBlockWithFlags
undefined4 MemoryManager::allocateBlockWithFlags(undefined4 param_1, undefined4 param_2) {
    // Allocation hint: pool ID = 2, alignment = 0x10, tag = 0
    struct PoolAllocHint {
        int poolId;       // +0x00
        int alignment;    // +0x04
        int tag;          // +0x08
    };
    PoolAllocHint hint;
    hint.poolId = 2;
    hint.alignment = 0x10;
    hint.tag = 0;

    // Allocate 0xF20 bytes from the specified pool (FUN_0043b980 is Heap::Allocate)
    int allocResult = Heap::Allocate(0xF20, &hint, param_2);
    if (allocResult != 0) {
        // Initialize the object using the allocated memory (param_1 is the object to init)
        return Object::Initialize(param_1);
    }
    return 0;
}