// FUNC_NAME: Stream::writeSerializedData
void __thiscall Stream::writeSerializedData(int* thisPtr, int intValue, long long value128Low, long long value128High, int value64Low, int value64High)
{
    int* streamPtr;
    int baseAddr;
    long long* alignedPtr;

    baseAddr = *thisPtr;
    // Write a pointer to a vtable or type descriptor at current position
    **(int**)(baseAddr + 0x14) = &PTR_FUN_01124f6c;  // +0x14: current write position pointer
    streamPtr = (int*)(baseAddr + 0x14);
    *streamPtr = *streamPtr + 4;  // Advance by 4 bytes

    // Write the 32-bit integer
    baseAddr = *thisPtr;
    **(int**)(baseAddr + 0x14) = intValue;
    // Align to next 4-byte boundary (ensuring at least 7 bytes gap? Possibly for 8-byte alignment)
    alignedPtr = (long long*)((*(int*)(baseAddr + 0x14) + 7U) & 0xfffffffc);
    *(long long**)(baseAddr + 0x14) = alignedPtr;
    // Write the first 128-bit block (two 64-bit values)
    *alignedPtr = value128Low;
    alignedPtr[1] = value128High;
    // Align again for next block
    alignedPtr = (long long*)((*(int*)(baseAddr + 0x14) + 0x13U) & 0xfffffffc);  // +0x13 = 19 bytes offset, aligns to 4 after skipping 19? Possibly a bug or intended padding
    *(long long**)(baseAddr + 0x14) = alignedPtr;
    *alignedPtr = CONCAT44(value64High, value64Low);  // Combine into 64-bit value
    // Advance by 8 bytes
    *(int*)(baseAddr + 0x14) = *(int*)(baseAddr + 0x14) + 8;
    return;
}