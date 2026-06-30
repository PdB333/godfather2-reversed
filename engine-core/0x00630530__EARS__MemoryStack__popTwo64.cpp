// FUNC_NAME: EARS::MemoryStack::popTwo64
void __thiscall EARS::MemoryStack::popTwo64(void) {
    // +0x08: current stack pointer (top of stack)
    int* stackPtr = *(int**)(this + 8);

    // First pop: get destination for the 64-bit value
    undefined4* dest = (undefined4*)getStackWritePointer();
    if (dest == &DAT_00e2a93c) {
        dest = (undefined4*)getFallbackStackWritePointer();
    }
    // Write two 32-bit halves from the stack (stack grows downward)
    *dest = *(undefined4*)(stackPtr - 8);
    dest[1] = *(undefined4*)(stackPtr - 4);
    *(int*)(this + 8) = stackPtr - 8; // advance stack pointer

    // Second pop (same pattern)
    stackPtr = *(int**)(this + 8);
    dest = (undefined4*)getStackWritePointer();
    if (dest == &DAT_00e2a93c) {
        dest = (undefined4*)getFallbackStackWritePointer();
    }
    *dest = *(undefined4*)(stackPtr - 8);
    dest[1] = *(undefined4*)(stackPtr - 4);
    *(int*)(this + 8) = stackPtr - 8;
    return;
}