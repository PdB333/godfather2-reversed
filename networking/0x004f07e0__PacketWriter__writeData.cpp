// FUNC_NAME: PacketWriter::writeData
// Function address: 0x004f07e0
// Role: Writes a sequence of typed data items into a buffer with 4-byte alignment after each write.
// The buffer pointer is stored at offset 0x14 from 'this' (a PacketWriter object).
// Data items are written in order: int32, 32-byte block, int32, int64, int32.
// After each write, the buffer pointer is advanced to the next 4-byte boundary.

void __thiscall PacketWriter::writeData(int32 firstValue, const void* dataBlock, int32 secondValue, int64 thirdValue, int32 fourthValue)
{
    // Write the first 4-byte value at the current buffer position
    *(int32*)(*(uint8**)(this + 0x14)) = firstValue;

    // Align the buffer pointer to the next 4-byte boundary after the 4 bytes written
    // Equivalent to (current + 4 + 3) & ~3
    *(uint8**)(this + 0x14) = (uint8*)((*(uint32*)(this + 0x14) + 7) & ~3);

    // Copy the 32-byte data block
    memcpy(*(uint8**)(this + 0x14), dataBlock, 0x20);

    // Align to the next 4-byte boundary after the 32 bytes
    // Equivalent to (current + 32 + 3) & ~3
    *(uint8**)(this + 0x14) = (uint8*)((*(uint32*)(this + 0x14) + 0x23) & ~3);

    // Write the second 4-byte value
    *(int32*)(*(uint8**)(this + 0x14)) = secondValue;

    // Align to the next 4-byte boundary after this 4-byte write
    *(uint8**)(this + 0x14) = (uint8*)((*(uint32*)(this + 0x14) + 7) & ~3);

    // Write the 8-byte value
    *(int64*)(*(uint8**)(this + 0x14)) = thirdValue;

    // Advance the buffer pointer by 8 bytes (the size of the int64)
    *(uint8**)(this + 0x14) += 8;

    // Write the final 4-byte value (no alignment performed)
    *(int32*)(*(uint8**)(this + 0x14)) = fourthValue;

    // Advance the buffer pointer by 4 bytes
    *(uint8**)(this + 0x14) += 4;
}