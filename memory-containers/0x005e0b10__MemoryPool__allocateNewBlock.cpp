// FUNC_NAME: MemoryPool::allocateNewBlock

void* __fastcall MemoryPool::allocateNewBlock(MemoryPool* this) {
    // Offsets: +4 -> pointer to allocation function (vtable?), +8 -> free list head
    void* allocFuncPtr = *(void**)(this + 4);  // e.g., a function pointer table or direct allocator
    void* freeListHead = *(void**)(this + 8);   // head of free list (or null)

    // Local dummy node if free list is empty (e.g., used as a sentinel)
    struct {
        uint32_t dummy1;
        uint32_t dummy2;
        uint32_t dummy3;
    } fallbackNode = {0, 0, 0};
    void* arg2 = (freeListHead != NULL) ? freeListHead : &fallbackNode;

    // Call the allocation function: size=0x18 (24 bytes), arg2 likely a 'previous' pointer or output context
    void* block = (*(void* (*)(int, void*))(*(uint32_t*)allocFuncPtr))(0x18, arg2);
    if (block != NULL) {
        *(uint32_t*)block = 0;          // +0x00: first dword
    }
    if ((uint32_t*)block + 1 != NULL) {
        *((uint32_t*)block + 1) = 0;    // +0x04: second dword
    }
    if ((uint32_t*)block + 2 != NULL) {
        *((uint32_t*)block + 2) = 0;    // +0x08: third dword
    }
    *((uint8_t*)block + 0x15) = 0;      // +0x15: byte field
    *((uint8_t*)block + 0x14) = 1;      // +0x14: byte field (likely flags)

    return block;
}