// FUNC_NAME: StreamReader::readAlignedBlockAndInvoke
void StreamReader::readAlignedBlockAndInvoke(void* handler) {
    uint32_t** currentPtr = reinterpret_cast<uint32_t**>(this + 0x18); // +0x18: pointer to current read position in buffer
    uint32_t* readAddr = *currentPtr;                          // the actual pointer value
    uint32_t originalValue = *readAddr;                         // value at that pointer (used as first argument to handler)
    uint32_t alignedAddr = reinterpret_cast<uint32_t>(readAddr) & 0xFFFFFFFC; // align down to 4 bytes
    uint64_t sourceInfo = (static_cast<uint64_t>(0x20) << 32) | reinterpret_cast<uint32_t>(readAddr);
    sourceInfo &= 0xFFFFFFFFFFFFFFFC;                           // upper 32 bits remain 0x20 (size)
    void* source = reinterpret_cast<void*>(static_cast<uint32_t>(sourceInfo)); // lower 32 bits = alignedAddr
    size_t copySize = static_cast<size_t>(sourceInfo >> 32);   // 0x20 = 32 bytes
    uint8_t localBuffer[0x20];                                 // receives the 32-byte block
    memcpy(localBuffer, source, copySize);
    // Advance the read pointer past the aligned block
    *currentPtr = reinterpret_cast<uint32_t*>(alignedAddr + 0x20);
    // Call the provided handler with originalValue and the block (passed as four 64-bit values)
    void (**handlerFunc)(uint32_t, uint64_t, uint64_t, uint64_t, uint64_t) =
        reinterpret_cast<void (**)(uint32_t, uint64_t, uint64_t, uint64_t, uint64_t)>(handler);
    (*handlerFunc)(originalValue,
                   *reinterpret_cast<uint64_t*>(localBuffer),
                   *reinterpret_cast<uint64_t*>(localBuffer + 8),
                   *reinterpret_cast<uint64_t*>(localBuffer + 16),
                   *reinterpret_cast<uint64_t*>(localBuffer + 24));
}