// FUNC_NAME: EARS::Framework::ScratchAllocator::allocateAndExecute
void ScratchAllocator::allocateAndExecute() {
    // Bit manipulation on flags at +0x110
    flags_0x110 |= 0x4;                                       // Set bit 2

    // Conditionally set/clear bit 4 based on previous state of bit 3
    if ((flags_0x110 >> 3) & 1) {
        flags_0x110 |= 0x10;                                  // Bit 3 was set: set bit 4
    } else {
        flags_0x110 &= ~0x10;                                 // Bit 3 was clear: clear bit 4
    }
    flags_0x110 &= ~0x8;                                      // Clear bit 3

    field_0xd4 = 0;                                           // Reset a timer or counter

    // Obtain block size index from a sub-object (likely vtable or descriptor)
    // this+0x1c points to a class descriptor; +0x20 is the block index character
    char blockIndex = *(char*)(*(int*)(this + 0x1c) + 0x20);
    int size = blockIndex * 0x40 + 0x10;                      // Compute allocation size

    // Per‑thread memory manager (TLS)
    // g_tlsMemManager is a TLS index (DAT_01139810)
    MemoryManager* memMgr = (MemoryManager*)TlsGetValue(g_tlsMemManager);
    int stackTop = memMgr->stackPointer;                      // +0x08
    int newTop = stackTop + size;

    // Allocate from the local stack if space permits, else via heap callback
    int allocPtr;
    if ((uint)newTop > (uint)memMgr->stackLimit) {            // +0x2c (stack limit)
        // Stack overflow – call custom allocator via vtable
        allocPtr = memMgr->vtable->allocate(size);            // vtable+0x14
    } else {
        memMgr->stackPointer = newTop;
        allocPtr = stackTop;
    }

    this->allocBuffer_0x118 = allocPtr;                       // Store the allocated block

    // Perform the actual operation using the temporary buffer
    FUN_00560670();                                           // Likely processes or constructs within the buffer

    // Restore the stack pointer to effectively “free” the block
    memMgr = (MemoryManager*)TlsGetValue(g_tlsMemManager);
    memMgr->stackPointer = this->allocBuffer_0x118;

    // If the freed block happens to be the stack base, call the heap deallocator
    if (this->allocBuffer_0x118 == memMgr->stackBase) {       // +0x28 (stack base)
        memMgr->vtable->deallocate(this->allocBuffer_0x118); // vtable+0x18
    }

    this->allocBuffer_0x118 = 0;                              // Clear the pointer
}