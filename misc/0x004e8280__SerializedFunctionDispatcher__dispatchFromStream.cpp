// FUNC_NAME: SerializedFunctionDispatcher::dispatchFromStream
void SerializedFunctionDispatcher::dispatchFromStream(void* thisPtr, void (**functionPointerPtr)()) {
    // param_1 (this) has a pointer at offset 0x18 to a serialized buffer.
    // The buffer layout:
    //   [4 bytes: function selector (uVar2)]
    //   [alignment padding to next 4-byte boundary]
    //   [28 bytes: argument block (7 x 4 bytes)]
    //   [8 bytes: additional argument (2 x 4 bytes)]
    // Then the function pointer is called with selector as first argument,
    // followed by the 7 int arguments, then the 2 int arguments.

    // Read the selector from the start of the buffer
    int selector = **(int**)((char*)thisPtr + 0x18);  // +0x18: pointer to current buffer position

    // Align the buffer pointer to next 4-byte boundary (after selector)
    void* alignedPtr = (void*)((int)*(void**)((char*)thisPtr + 0x18) + 7 & 0xFFFFFFFC);
    *(void**)((char*)thisPtr + 0x18) = alignedPtr;

    // Copy 28 bytes from aligned position into local argument buffer
    int args[7];  // local_1c, local_18, local_14, local_10, local_c, local_8, local_4
    memcpy(args, alignedPtr, 28);

    // Advance buffer pointer past the 28-byte block
    *(void**)((char*)thisPtr + 0x18) = (char*)alignedPtr + 28;

    // Read the next 8 bytes (two 4-byte values)
    unsigned long long extraArg = *(unsigned long long*)((char*)alignedPtr + 28);
    int extraLow = (int)extraArg;          // local_24
    int extraHigh = (int)(extraArg >> 32); // uStack_20

    // Advance buffer pointer past the 8-byte block
    *(void**)((char*)thisPtr + 0x18) = (char*)alignedPtr + 36;

    // Call the provided function pointer with extracted arguments
    // The function signature is: void foo(int selector, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
    (*functionPointerPtr)(selector, args[0], args[1], args[2], args[3], args[4], args[5], args[6], extraLow, extraHigh);
}