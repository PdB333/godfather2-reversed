// FUNC_NAME: MemoryManager::allocateBlockWithLogging
void __thiscall MemoryManager::allocateBlockWithLogging(void* context) {
    // param_1: this (MemoryManager with vtable and fallback buffer pointer at offset 4)
    // context: pointer to user-provided data (first word stored in the block)
    void* buffer = *(void**)((char*)this + 4); // this->fallbackBuffer
    uint32_t fallback[3] = {0, 0, 0};          // stack-local temporary block (12 bytes)
    
    if (buffer == nullptr)
        buffer = &fallback;
    
    // Call virtual allocator (vtable[0]: allocateMemory(size, buffer))
    void* block = (*(void* (__thiscall**)(MemoryManager*, uint32_t, void*))*(void**)*this)(this, 0xC, buffer);
    
    if (block) {
        *(uint32_t*)block = fallback[2];               // block[0] = local_4 (0 in fallback case)
        *(void**)((char*)block + 4) = __builtin_return_address(0); // block[1] = caller's return address
        *(void**)((char*)block + 8) = *(void**)context;             // block[2] = first word of context
    }
    // No explicit return – result is used by caller via block pointer
}