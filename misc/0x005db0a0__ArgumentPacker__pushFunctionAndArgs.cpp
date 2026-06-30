// FUNC_NAME: ArgumentPacker::pushFunctionAndArgs
// Packs a function pointer and five arguments into a stack buffer.
// The stack buffer is managed by the object: *this is a pointer to the buffer base,
// and offset +0x14 holds the current stack pointer (write position).
// Alignment to 4 bytes is applied before writing the fourth argument.
void __thiscall ArgumentPacker::pushFunctionAndArgs(void* thisPtr, uint32 arg0, uint32 arg1, uint32 arg2, uint32 arg3, uint32 arg4)
{
    // Get the buffer base pointer from *this
    char* bufferBase = *(char**)thisPtr;
    // Get the current stack pointer stored at bufferBase + 0x14
    uint32* stackPtr = *(uint32**)(bufferBase + 0x14);

    // Write constant function pointer (PTR_LAB_011273e0) first
    *stackPtr = (uint32)&PTR_LAB_011273e0;
    stackPtr++;

    // Write first argument (param_2)
    *stackPtr = arg0;
    stackPtr++;

    // Write second argument (param_3)
    *stackPtr = arg1;
    stackPtr++;

    // Write third argument (param_4)
    *stackPtr = arg2;
    stackPtr++;

    // Align stack pointer to 4 bytes before writing the remaining arguments
    stackPtr = (uint32*)(((uint32)stackPtr + 3) & ~3);

    // Write fourth argument (param_5)
    *stackPtr = arg3;
    stackPtr++;

    // Write fifth argument (param_6)
    *stackPtr = arg4;
    stackPtr++;

    // Store the updated stack pointer back to the object
    *(uint32**)(bufferBase + 0x14) = stackPtr;
}