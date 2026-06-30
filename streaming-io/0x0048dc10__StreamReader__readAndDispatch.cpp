// FUNC_NAME: StreamReader::readAndDispatch
void __thiscall StreamReader::readAndDispatch(void* thisPtr, uint32_t* callbackFuncPtr)
{
    // +0x18: current read pointer (aligned to 4 bytes)
    uint64_t* alignedPtr = (uint64_t*)((*(int*)((int)thisPtr + 0x18) + 3) & 0xFFFFFFFC);
    *(uint64_t**)((int)thisPtr + 0x18) = alignedPtr;

    // Read a 64-bit value (low/high parts)
    uint64_t value64 = *alignedPtr;
    *(uint64_t**)((int)thisPtr + 0x18) = alignedPtr + 1; // advance past the 64-bit

    // Read a 32-bit value
    uint32_t value32 = *(uint32_t*)(alignedPtr + 1); // after the 64-bit, but alignedPtr+1 is already advanced?
    // Actually careful: alignedPtr+1 points to the next 8-byte word, but we want the 4-byte after the 64-bit?
    // The code does: uVar3 = *(undefined4 *)(puVar4 + 1); then advances 0xc (12 bytes) from start.
    // Let's replicate exactly:
    char* bytePtr = (char*)((int)alignedPtr + 0xC);
    *(char**)((int)thisPtr + 0x18) = bytePtr;

    // Read boolean from byte at offset 0xC
    bool boolVal = *(char*)((int)alignedPtr + 0xC) != '\0';

    // Advance pointer further (skipping 8 more bytes to align to next 8-byte?)
    *(uint64_t**)((int)thisPtr + 0x18) = alignedPtr + 2;

    // Split 64-bit into two 32-bit arguments (low, high)
    uint32_t low = (uint32_t)value64;
    uint32_t high = (uint32_t)(value64 >> 32);

    // Call the callback function with the extracted values
    void (*callback)(uint32_t, uint32_t, uint32_t, bool) = (void (*)(uint32_t, uint32_t, uint32_t, bool))*callbackFuncPtr;
    callback(low, high, value32, boolVal);
}