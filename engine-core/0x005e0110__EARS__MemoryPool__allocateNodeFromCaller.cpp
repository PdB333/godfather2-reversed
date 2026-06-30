// FUNC_NAME: EARS::MemoryPool::allocateNodeFromCaller

void __thiscall EARS::MemoryPool::allocateNodeFromCaller(unsigned int userData) {
    // This function allocates a 24-byte block (0x18) and initializes it using
    // the call context. It expects:
    //   - ECX (this) to point to a MemoryPool with:
    //        +0x00: vtable? (unused here)
    //        +0x04: pointer to allocation function (size_t, void* fallback) -> void*
    //        +0x08: pointer to a pre-allocated fallback buffer (or null)
    //   - ESI to point to a two-dword source structure (e.g., parent object data)
    //   - Stack contains return address and param_2 (userData)
    //
    // The allocated block layout (24 bytes):
    //   +0x00: always 0 (from stack fallback)
    //   +0x04: return address (caller's return address)
    //   +0x08: userData parameter
    //   +0x0C: first dword from ESI source
    //   +0x10: second dword from ESI source
    //   +0x14: zero byte
    //   +0x15: zero byte

    // Get fallback buffer pointer from this+0x08
    void* fallback = *(void**)((unsigned char*)this + 8);
    unsigned int stackBuf[3] = {0, 0, 0};            // local fallback (if fallback==null)
    if (fallback == nullptr) {
        fallback = stackBuf;
    }

    // Call allocation function via function pointer at this+0x04
    auto allocFunc = *(void* (*)(int, void*))((unsigned char*)this + 4);
    unsigned int* block = (unsigned int*)allocFunc(0x18, fallback);
    if (block != nullptr) {
        block[0] = stackBuf[2];                    // = 0
        block[1] = (unsigned int)__builtin_return_address(0); // return address
        block[2] = userData;
        // sourcePtr from ESI register (implicit parameter)
        unsigned int* sourcePtr;                     // actual value assumed in ESI
        __asm__("mov %%esi, %0" : "=r"(sourcePtr)); // get ESI
        block[3] = sourcePtr[0];
        block[4] = sourcePtr[1];
        // Zero the trailing two bytes
        ((unsigned char*)block)[0x14] = 0;
        ((unsigned char*)block)[0x15] = 0;
    }
    // Block is not returned; presumably registered elsewhere (e.g., a linked list)
}