// FUNC_NAME: ArgumentBuffer::invokeCallback
// Address: 0x005d70e0
// This function reads serialized arguments from a buffer (pointed to by this+0x18) and calls a registered callback.
// The buffer contains: two 4-byte args, a size value (argSize), an alignment value, then an aligned block containing another 4-byte arg.
// The size and alignment are used to skip padding and locate the next argument.
// The callback receives: arg1, arg2, a 64-bit value (size:baseAddress), alignment, and the final arg.

struct ArgumentBuffer {
    // offset +0x18: pointer to current read position in the serialized argument buffer
    uint8_t* currentRead;
};

void ArgumentBuffer::invokeCallback(void (*callbackFunc)(uint32_t, uint32_t, uint64_t, uint32_t, uint32_t)) {
    // Align current pointer to 4-byte boundary
    uint32_t* readPtr = reinterpret_cast<uint32_t*>(
        (reinterpret_cast<uint32_t>(currentRead) + 3) & ~3
    );
    currentRead = reinterpret_cast<uint8_t*>(readPtr);

    // Read first two arguments
    uint32_t arg1 = *readPtr++;
    currentRead = reinterpret_cast<uint8_t*>(readPtr);
    uint32_t arg2 = *readPtr++;
    currentRead = reinterpret_cast<uint8_t*>(readPtr);

    // Read argSize and alignment values
    int32_t argSize = static_cast<int32_t>(*readPtr++);
    currentRead = reinterpret_cast<uint8_t*>(readPtr);
    int32_t alignment = static_cast<int32_t>(*readPtr++);
    currentRead = reinterpret_cast<uint8_t*>(readPtr);

    // Compute next aligned address: align (current pointer + alignment) to 'alignment' boundary
    uint32_t nextAligned = (reinterpret_cast<uint32_t>(readPtr) + alignment + 0xF) & ~(alignment - 1);
    // Then compute position where next argument resides: align argSize to 4 and add to nextAligned
    uint32_t alignedSize = (argSize + 3) & ~3;
    uint32_t* nextPtr = reinterpret_cast<uint32_t*>(alignedSize + nextAligned);
    currentRead = reinterpret_cast<uint8_t*>(nextPtr);

    // Read the next argument (arg3)
    uint32_t arg3 = *nextPtr++;
    currentRead = reinterpret_cast<uint8_t*>(nextPtr);

    // Build the 64-bit third argument: combine argSize (high) with (argSize != 0 ? nextAligned : 0) (low)
    // This matches the decompiler's CONCAT44 pattern.
    uint64_t combined = (static_cast<uint64_t>(argSize) << 32) |
                        (argSize != 0 ? nextAligned : 0);

    // Call the registered function with the extracted arguments
    callbackFunc(arg1, arg2, combined, static_cast<uint32_t>(alignment), arg3);
}