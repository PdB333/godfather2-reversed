// FUNC_NAME: BufferStream::callFunction
void BufferStream::callFunction(void (**funcPtrPtr)()) {
    // +0x18: current read pointer (to byte buffer)
    uint8_t* currentPtr = *reinterpret_cast<uint8_t**>(reinterpret_cast<uint8_t*>(this) + 0x18);
    uint32_t arg0 = *reinterpret_cast<uint32_t*>(currentPtr); // first arg from unaligned position

    // Align pointer to next 4-byte boundary, then read remaining args
    uint8_t* alignedPtr = reinterpret_cast<uint8_t*>((reinterpret_cast<uint32_t>(currentPtr) + 7) & 0xFFFFFFFC);
    *reinterpret_cast<uint8_t**>(reinterpret_cast<uint8_t*>(this) + 0x18) = alignedPtr;

    uint32_t arg1 = *reinterpret_cast<uint32_t*>(alignedPtr);
    *reinterpret_cast<uint8_t**>(reinterpret_cast<uint8_t*>(this) + 0x18) = alignedPtr + 4;

    uint32_t arg2 = *reinterpret_cast<uint32_t*>(alignedPtr + 4);
    *reinterpret_cast<uint8_t**>(reinterpret_cast<uint8_t*>(this) + 0x18) = alignedPtr + 8;

    // Read 64-bit value (acts as two separate 32-bit args)
    uint64_t doubleWord = *reinterpret_cast<uint64_t*>(alignedPtr + 8);
    uint32_t arg3_low = static_cast<uint32_t>(doubleWord);
    uint32_t arg3_high = static_cast<uint32_t>(doubleWord >> 32);
    *reinterpret_cast<uint8_t**>(reinterpret_cast<uint8_t*>(this) + 0x18) = alignedPtr + 16;

    uint32_t arg4 = *reinterpret_cast<uint32_t*>(alignedPtr + 16);
    *reinterpret_cast<uint8_t**>(reinterpret_cast<uint8_t*>(this) + 0x18) = alignedPtr + 20;

    // Call the target function with the extracted arguments
    void (*targetFunc)() = *funcPtrPtr;
    targetFunc(arg0, arg1, arg2, arg3_low, arg3_high, arg4);
}