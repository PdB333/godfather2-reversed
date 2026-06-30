// FUNC_NAME: StreamManager::invokeFunctionWithSerializedArgs
void StreamManager::invokeFunctionWithSerializedArgs(int thisObj, int* ppFunc) // thisObj: object with stream buffer at +0x18, ppFunc: pointer to function pointer
{
    // Read first 4-byte value from the buffer (likely an object ID or arg count)
    int firstArg = **(int**)(thisObj + 0x18);  // Dereference pointer at +0x18, then take value
    // Align buffer pointer to next 4-byte boundary (typical for performance)
    void* alignedSrc = (void*)((int)*(int**)(thisObj + 0x18) + 7U & 0xfffffffc);
    // Update stored buffer pointer to aligned version
    *(void**)(thisObj + 0x18) = alignedSrc;

    // Copy 0x24 bytes (36 bytes) of serialized arguments onto local stack
    // These will be passed as separate args (likely as doubles and ints)
    __int64 argBlock[4];  // 4 x 8 bytes = 32 bytes
    int extraArg;         // 4 bytes  -> total 36 bytes
    _memcpy(&argBlock, alignedSrc, 0x24);  // Copy into local variables

    // Advance buffer pointer past the copied block
    *(__int64**)(thisObj + 0x18) = (__int64*)((int)alignedSrc + 0x24);

    // Read another 8-byte value (double or two ints) from the buffer
    __int64 tailArg = *(__int64*)((int)alignedSrc + 0x24);
    unsigned int tailLow = (unsigned int)tailArg;
    unsigned int tailHigh = (unsigned int)(tailArg >> 32);  // Split into two 32-bit halves

    // Finalize buffer pointer (advance past tail)
    *(int*)(thisObj + 0x18) = (int)alignedSrc + 0x2c;

    // Call target function with deserialized arguments
    // firstArg, then the 5 components from argBlock and extraArg (4 doubles + int),
    // then the split tail value
    (*(void (*)(int, __int64, __int64, __int64, __int64, int, unsigned int, unsigned int))*ppFunc)(
        firstArg,
        argBlock[0],  // Same as local_24
        argBlock[1],  // local_1c
        argBlock[2],  // local_14
        argBlock[3],  // local_c
        extraArg,     // local_4
        tailLow,      // local_2c
        tailHigh      // uStack_28
    );
}