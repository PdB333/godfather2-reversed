// FUNC_NAME: popAndCallIndirect
void popAndCallIndirect(void *context, void (**funcPtr)(uint, uint, uint, uint64_t, int)) {
    // context is a struct with a stack pointer at offset +0x18
    uint *stackPtr = *(uint **)((char *)context + 0x18); // get current stack pointer
    uint firstArg = *stackPtr; // read first value (pre‑alignment)

    // Align stack pointer to next 4-byte boundary after adding 7
    uint *alignedPtr = (uint *)(((uint)stackPtr + 7) & 0xFFFFFFFC);
    *(uint **)((char *)context + 0x18) = alignedPtr; // update stored stack pointer

    uint secondArg = alignedPtr[0];
    uint thirdArg  = alignedPtr[1];
    int  fourthHigh = alignedPtr[2];
    int  fifthArg  = alignedPtr[3];

    // Align (alignedPtr + fifthArg) to a multiple of fifthArg
    uint alignedEnd = ((uint)alignedPtr + fifthArg + 0xF) & ~(fifthArg - 1);

    // Compute new stack pointer: fourthHigh * 4 + alignedEnd
    uint newStackPtr = fourthHigh * 4 + alignedEnd;
    *(uint *)((char *)context + 0x18) = newStackPtr;

    // Build 64‑bit fourth argument: high = fourthHigh, low = alignedEnd if fourthHigh != 0 else 0
    uint lowPart = (fourthHigh != 0) ? alignedEnd : 0;
    uint64_t fourthArg = ((uint64_t)fourthHigh << 32) | lowPart;

    // Call the target function
    (*funcPtr)(firstArg, secondArg, thirdArg, fourthArg, fifthArg);
}