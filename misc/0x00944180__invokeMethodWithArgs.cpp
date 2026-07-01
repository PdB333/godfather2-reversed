// FUNC_NAME: invokeMethodWithArgs

// Function address: 0x00944180
// Role: Reads a set of arguments from a structured buffer and calls a function pointer with those arguments.
// This appears to be a generic method invocation helper used for reflection or scripting calls.
// The buffer structure at param_1+0x18 is a double pointer to a stack of arguments.
// The arguments are extracted and the function at *param_2 is called with 9 arguments.

void invokeMethodWithArgs(void* context, void** funcPtr)
{
    // context->argBuffer (offset +0x18) is a pointer to an argument stack.
    // Initially, the stack starts with a pointer to the first argument.
    uint* stackPtr = *(uint**)((char*)context + 0x18); // +0x18: pointer to current position in argument buffer
    uint firstArg = *stackPtr; // First argument from double-dereference

    // Calculate base address for the argument struct (aligned up from stackPtr + 0x13)
    uint argStructBase = ((uint)stackPtr + 0x13) & 0xFFFFFFF0; // Align to 16-byte boundary

    // Read arguments from fixed offsets relative to argStructBase
    uint arg5 = *(uint*)(argStructBase + 0x60); // +0x60: 5th argument
    uint arg6 = *(uint*)(argStructBase + 0x64); // +0x64: 6th argument (offset 100 decimal)
    uint arg7 = *(uint*)(argStructBase + 0x68); // +0x68: 7th argument
    int   arg8 = *(int*)(argStructBase + 0x6C);  // +0x6C: 8th argument (signed)
    int   arg9 = *(int*)(argStructBase + 0x70);  // +0x70: 9th argument

    // Update the buffer pointer after reading each argument (possibly for debugging or iteration)
    *(uint*)((char*)context + 0x18) = argStructBase + 0x60; // store address of arg5
    *(uint**)((char*)context + 0x18) = (uint*)(argStructBase + 0x64); // store address of arg6
    *(uint*)((char*)context + 0x18) = argStructBase + 0x68; // store address of arg7
    *(int**)((char*)context + 0x18) = (int*)(argStructBase + 0x6C); // store address of arg8
    *(int**)((char*)context + 0x18) = (int*)(argStructBase + 0x70); // store address of arg9

    // Calculate a combined 64-bit value for the 8th argument (arg8 and an aligned pointer)
    uint combinedHigh = arg8;
    uint combinedLow = (argStructBase + 0x73 + arg9) & ~(arg9 - 1U); // alignment trick: align to arg9 size
    uint64_t combinedArg = ((uint64_t)combinedHigh << 32) | (uint64_t)combinedLow;

    // Advance the buffer pointer after all arguments (for next call?):
    // The new pointer is: arg8 * 0x30 + aligned address
    *(uint*)((char*)context + 0x18) = arg8 * 0x30 + combinedLow;

    // Call the target function with all arguments
    void (*func)(uint, uint, uint, uint, uint, uint, uint, uint64_t, int) = 
        (void (*)(uint, uint, uint, uint, uint, uint, uint, uint64_t, int))*funcPtr;
    func(firstArg, argStructBase, argStructBase + 0x10, argStructBase + 0x20,
         arg5, arg6, arg7, combinedArg, arg9);
}