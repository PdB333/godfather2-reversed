// FUNC_NAME: ObjectFactory::createWithAlloc
int __cdecl ObjectFactory::createWithAlloc(void* objectPtr, int allocTag) {
    // Allocator parameters: pool=2 (likely EARS memory pool), alignment=0x10 (16 bytes), flags=0
    int allocPool = 2;
    int allocAlignment = 16; // 0x10
    int allocFlags = 0;

    // Attempt to allocate 0x430 bytes of memory (size of some game object)
    void* allocatedMem = FUN_0043b980(0x430, &allocPool, allocTag);
    if (allocatedMem != nullptr) {
        // Success: call constructor/initializer on the provided object instance
        return FUN_00795720(objectPtr);
    }
    return 0; // Allocation failed
}