// FUNC_NAME: ScriptVM::popAndExecuteOp
// Address: 0x00519c40
// Pops an 8-byte value from the internal stack (aligned to 4-byte boundary) and calls a function pointer from param_2 with the low and high DWORDs.

void ScriptVM::popAndExecuteOp(void* thisPtr, void* funcPtr) {
    // Stack pointer stored at offset 0x18 (aligned to 4-byte boundary)
    uint64_t* stackPtr = (uint64_t*)((*(int*)((char*)thisPtr + 0x18) + 3) & 0xFFFFFFFC);
    *(uint64_t**)((char*)thisPtr + 0x18) = stackPtr;

    // Read 8-byte value from stack
    uint64_t value = *stackPtr;
    *(uint64_t**)((char*)thisPtr + 0x18) = stackPtr + 1;

    // Split into two 32-bit parts
    uint32_t low = (uint32_t)value;
    uint32_t high = (uint32_t)(value >> 32);

    // Call the function pointer obtained from param_2
    ((void(__cdecl*)(uint32_t, uint32_t))funcPtr)(low, high);
}