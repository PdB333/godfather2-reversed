// FUNC_NAME: TNL::BitStream::readAndInvokeCallback
void TNL::BitStream::readAndInvokeCallback(int thisPtr, uint32_t** callbackFunc) {
    // Reads a packed function call from the bitstream buffer at this+0x18
    // The buffer is read with alignment handling; first word read before alignment, rest aligned.
    // Calls the callback function pointer (first uint32 in callbackFunc) with the extracted arguments.

    // Read first word (message ID or first parameter) from current buffer position (possibly unaligned)
    uint32_t firstArg = **(uint32_t**)(thisPtr + 0x18);  // +0x18: pointer to current read position in buffer

    // Advance buffer pointer to next 4-byte aligned boundary (skip alignment padding)
    uint32_t* alignedPtr = (uint32_t*)(((uint32_t)*(uint32_t**)(thisPtr + 0x18) + 7U) & 0xFFFFFFFC);
    *(uint32_t**)(thisPtr + 0x18) = alignedPtr;

    // Read next 6 aligned uint32 values
    uint32_t arg2 = alignedPtr[0];
    *(uint32_t**)(thisPtr + 0x18) = alignedPtr + 1;

    uint32_t arg3 = alignedPtr[1];
    *(uint32_t**)(thisPtr + 0x18) = alignedPtr + 2;

    // Read 64-bit value (split into two 32-bit halves)
    uint64_t arg4_lo_hi = *(uint64_t*)(alignedPtr + 2);
    uint32_t arg4_lo = (uint32_t)arg4_lo_hi;
    uint32_t arg4_hi = (uint32_t)(arg4_lo_hi >> 32);
    *(uint32_t**)(thisPtr + 0x18) = alignedPtr + 4;

    uint32_t arg5 = alignedPtr[4];
    *(uint32_t**)(thisPtr + 0x18) = alignedPtr + 5;

    uint32_t arg6 = alignedPtr[5];
    *(uint32_t**)(thisPtr + 0x18) = alignedPtr + 6;

    // Call the callback function with the unpacked arguments
    ((void (*)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*callbackFunc))(
        firstArg, arg2, arg3, arg4_lo, arg4_hi, arg5, arg6);
}