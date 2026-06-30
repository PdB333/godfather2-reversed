// FUNC_NAME: SmallObjectAllocator::allocateObject
void __thiscall SmallObjectAllocator::allocateObject(int this)
{
    // +0x4: vtable pointer?
    // +0x8: memory block pointer (pool or fallback)
    void* poolBlock = *(void**)(this + 8);
    void* allocatorFuncPtr = *(void**)(this + 4);
    void* (*allocFunc)(int size, void* block) = (*(void**(*)(int, void*))allocatorFuncPtr);
    void* object = nullptr;

    if (poolBlock == nullptr) {
        // If no pool, use local stack as temporary block
        int localFallback[3] = {0, 0, 0};
        object = allocFunc(0x18, &localFallback);
    } else {
        object = allocFunc(0x18, poolBlock);
    }

    // Initialize the 24-byte object to zero
    if (object != nullptr) {
        *(int*)object = 0;
        *(int*)((char*)object + 4) = 0;
        *(int*)((char*)object + 8) = 0;
    }

    // Set byte flags at offsets 0x15 and 0x14
    *(char*)((int)object + 0x15) = 0;
    *(char*)(object + 5) = 1;  // offset 0x14 (since object is int*, +5 gives 20 bytes)

    return;
}