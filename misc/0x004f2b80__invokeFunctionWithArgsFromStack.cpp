// FUNC_NAME: invokeFunctionWithArgsFromStack
void __cdecl invokeFunctionWithArgsFromStack(void* context, void (* const* funcPtrPtr)()) {
    // context is an object with a stack pointer at offset +0x18.
    // Reads 6 arguments from the stack (with 8-byte alignment for a 64-bit value)
    // and calls the function pointed to by funcPtrPtr.

    // The stack is a buffer of 32-bit aligned data.
    // struct Context { ... char* stackPtr; // +0x18 }

    char*& stackPtr = *(char**)((char*)context + 0x18);   // +0x18

    // First argument: read the current stack pointer's value, then advance.
    uint32_t arg1 = *(uint32_t*)stackPtr;
    // Align to next 4-byte boundary (round up to multiple of 4)
    stackPtr = (char*)(((int)*(uint32_t**)((char*)context + 0x18) + 7) & 0xFFFFFFFC);
    // Actually the above line is complex; simplified: align stackPtr+7 then mask

    uint32_t arg2 = *(uint32_t*)stackPtr;
    stackPtr += 4;

    uint32_t arg3 = *(uint32_t*)stackPtr;
    stackPtr += 8; // skip an extra 4 bytes to reach puVar6+2? More precisely: from original code, it adds 8 bytes (two uint32_t) to skip.

    uint64_t arg45 = *(uint64_t*)stackPtr;
    stackPtr += 8;

    uint32_t arg6 = *(uint32_t*)stackPtr;
    stackPtr += 4;

    uint32_t arg4 = (uint32_t)(arg45);
    uint32_t arg5 = (uint32_t)(arg45 >> 32);

    // Call the function
    void (*targetFunc)() = *funcPtrPtr;
    targetFunc(arg1, arg2, arg3, arg4, arg5, arg6);
}