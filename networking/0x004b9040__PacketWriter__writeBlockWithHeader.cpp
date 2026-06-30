// FUNC_NAME: PacketWriter::writeBlockWithHeader
// Address: 0x004b9040
// Role: Serializes a header and an aligned block of 12-byte elements into a growing buffer.
// The 'this' pointer has a buffer cursor at offset +0x14.
void __thiscall PacketWriter::writeBlockWithHeader(
    int headerField1,           // First 4-byte header value
    int headerField2,           // Second 4-byte header value
    int64_t headerValue3,       // 8-byte header value (double or int64)
    void* elementData,          // Pointer to array of 12-byte structures
    int elementCount,           // Number of elements to copy
    int alignment)              // Alignment requirement for element block (also written to header)
{
    // Current write pointer stored at this+0x14
    int* cursorPtr = *(int**)(this + 0x14);

    // Write headerField1 (4 bytes)
    *cursorPtr = headerField1;
    cursorPtr++;

    // Write headerField2 (4 bytes)
    *cursorPtr = headerField2;
    cursorPtr++;

    // Align to 4-byte boundary for 8-byte write (ceil to next multiple of 4)
    cursorPtr = (int*)(((int)cursorPtr + 3) & ~3);

    // Write 8-byte headerValue3
    *(int64_t*)cursorPtr = headerValue3;
    cursorPtr += 2; // advance 8 bytes

    // Write elementCount (4 bytes)
    *cursorPtr = elementCount;
    cursorPtr++;

    // Write alignment value (4 bytes)
    *cursorPtr = alignment;
    cursorPtr++;

    // Align cursor to the specified alignment boundary.
    // The expression replicates the original: 
    // newPos = (currentPos + alignment + 3) & ~(alignment - 1)
    void* alignedDst = (void*)(
        ~(alignment - 1U) & ((int)cursorPtr + alignment + 3)
    );

    // Copy elementCount * 12 bytes from elementData to aligned destination
    __memcpy(alignedDst, elementData, elementCount * 12);

    // Advance cursor by the copied size
    cursorPtr = (int*)((char*)alignedDst + elementCount * 12);

    // Store updated cursor back to this+0x14
    *(int**)(this + 0x14) = cursorPtr;
}