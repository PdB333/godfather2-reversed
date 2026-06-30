// FUNC_NAME: Stream::appendHash
void __thiscall Stream::appendHash(int* thisPtr, uint64_t hashPart1, uint64_t hashPart2, uint32_t hashPart3)
{
    // Dereference thisPtr to get the underlying data buffer pointer
    int* bufferBase = *thisPtr; // thisPtr points to a handle holding the buffer address

    // Write a new vtable/class pointer into the stream at offset +0x14 from the buffer
    *(void**)(bufferBase + 0x14) = &PTR_LAB_00e50c5c;

    // Advance the pointer stored at bufferBase+0x14 by 4 bytes (effectively moving the write cursor forward)
    int* cursorPtr = (int*)(bufferBase + 0x14);
    *cursorPtr = *cursorPtr + 4;

    // Copy the 20-byte hash (two 64-bit + one 32-bit) into local stack
    struct Hash20 {
        uint64_t part1;
        uint64_t part2;
        uint32_t part3;
    } hashData;
    hashData.part1 = hashPart1;
    hashData.part2 = hashPart2;
    hashData.part3 = hashPart3;

    // Process the hash (likely copy it into the stream or deserialize it)
    FUN_0049c430(&hashData, 0x14, 4);
    return;
}