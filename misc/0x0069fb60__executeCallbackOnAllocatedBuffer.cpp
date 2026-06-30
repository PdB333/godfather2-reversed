// FUNC_NAME: executeCallbackOnAllocatedBuffer
// Function at 0x0069fb60: Allocates 4 bytes (aligned to 4) and calls a callback function pointer with the allocated address.
// param_1 is unused in the decompiled body – may be a dummy 'this' or extra argument.

void executeCallbackOnAllocatedBuffer(int unusedThis, int** callbackTable) {
    int allocatedBuffer; // 4-byte buffer on stack (the allocation target)
    // Allocate 4 bytes with 4-byte alignment using internal allocator (likely EA EARS MemoryManager)
    FUN_0049c470(&allocatedBuffer, 4, 4);
    // Dereference the function pointer stored at *callbackTable and call it with the buffer address
    ((void (*)(int))(*callbackTable))(allocatedBuffer);
}