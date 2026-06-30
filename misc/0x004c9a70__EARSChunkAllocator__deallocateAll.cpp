// FUNC_NAME: EARSChunkAllocator::deallocateAll
void __thiscall EARSChunkAllocator::deallocateAll(void) {
    // Stack buffer for temporary deallocation data (12 bytes)
    uint8_t stackBuf[12];

    // Low-level deallocation helper: passes size from first field of chunk at +0x1c
    // (size read via double indirection: *(int*)(*(int*)(this+0x1c)))
    FUN_004ca810(stackBuf, this, *(int*)*(int*)(this + 0x1c), this, *(int**)(this + 0x1c));

    // Release chunk at +0x1c using virtual method (vtable[1]) on the deallocator at +0x04
    // Second parameter is size 0x18 (24 bytes)
    ((void (*)(void*, int))((*(int**)(*(int*)(this + 4)))[1]))(*(void**)(this + 0x1c), 0x18);
    *(int*)(this + 0x1c) = 0;
    *(int*)(this + 0x20) = 0;

    // If second chunk at +0x18 exists, release it similarly
    if (*(int*)(this + 0x18) != 0) {
        ((void (*)(void*, int))((*(int**)(*(int*)(this + 0x14)))[1]))(*(void**)(this + 0x18), 0);
        *(int*)(this + 0x18) = 0;
    }

    // Call virtual method (vtable[3]) on deallocator at +0x14 (likely final cleanup)
    ((void (*)(void))((*(int**)(*(int*)(this + 0x14)))[3]))();

    // Global cleanup routine
    FUN_004ca0a0();
}