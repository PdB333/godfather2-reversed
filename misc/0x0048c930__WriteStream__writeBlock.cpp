// FUNC_NAME: WriteStream::writeBlock
// Address: 0x0048c930
// Role: Writes a structured data block into the stream buffer: type tag, 64-bit value (param3+param4), 32-bit value (param2), null terminator with alignment.

void __thiscall WriteStream::writeBlock(WriteStream* this, int param2, int param3, int param4)
{
    // this points to a stream object; *this is a pointer to buffer manager
    int* bufferMgr = *(int**)this; // +0x00: pointer to buffer manager
    // Write cursor is stored at bufferMgr + 0x14
    int*& cursor = *(int**)(bufferMgr + 0x14); // +0x14: current write pointer

    // Write the type tag (global static descriptor)
    *cursor = (int)&PTR_LAB_01123d8c;
    cursor++;

    // Align cursor to next 4-byte boundary for the 8-byte write
    cursor = (int*)(((int)cursor + 3) & ~3);

    // Write combined 64-bit value: param4 = high 32 bits, param3 = low 32 bits
    *(int64_t*)cursor = ((int64_t)param4 << 32) | (uint32_t)param3;
    cursor += 2; // 8 bytes

    // Write param2 as 32-bit integer
    *cursor = param2;
    cursor++;

    // Write a null byte (terminator) and align to 4 bytes
    *(uint8_t*)cursor = 0;
    cursor = (int*)(((int)cursor + 4) & ~3);
}