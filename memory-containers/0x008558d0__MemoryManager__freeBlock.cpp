// FUNC_NAME: MemoryManager::freeBlock
void __thiscall MemoryManager::freeBlock(void* block) {
    uint statusOrIndex = *(uint*)((char*)block + 8); // +0x08: reference count or chunk index
    if ((int)statusOrIndex >= 0) {
        TlsGetValue(DAT_01139810); // thread-local heap handle (not used here)
        // Deallocate: data pointer at +0x00, size = (extracted index & 0x3fffffff) * 0x70, flags = 0x17 (HEAP_NO_SERIALIZE?)
        FUN_00aa26e0(*(void**)block, (statusOrIndex & 0x3fffffff) * 0x70, 0x17);
    }
}