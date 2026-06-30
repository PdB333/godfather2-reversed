// FUNC_NAME: BufferWriter::writeAlignedFields
// Reconstructed from function at 0x005085d0
// Writes multiple fields with 4-byte alignment into a buffer pointed to by this+0x14

void BufferWriter::writeAlignedFields(int param1, int param2, long long param3, long long param4, int param5, long long param6)
{
    // Current write pointer is stored at this+0x14
    int* currentPtr = *(int**)(this + 0x14);

    // Write first 4-byte field at current pointer
    *currentPtr = param1;

    // Align to next 4-byte boundary (skip 4 bytes)
    currentPtr = (int*)(((int)currentPtr + 7) & 0xFFFFFFFC);
    *(int**)(this + 0x14) = currentPtr;

    // Write second 4-byte field
    *currentPtr = param2;

    // Align to next 4-byte boundary
    currentPtr = (int*)(((int)currentPtr + 7) & 0xFFFFFFFC);
    *(int**)(this + 0x14) = currentPtr;

    // Write two 8-byte fields and a trailing 4-byte field consecutively
    long long* quadPtr = (long long*)currentPtr;
    *quadPtr = param3;           // first 8 bytes
    *(quadPtr + 1) = param4;     // next 8 bytes
    *(int*)(quadPtr + 2) = param5; // 4 bytes at offset 16

    // Calculate next aligned position after the 20 bytes written (8+8+4=20)
    quadPtr = (long long*)(((int)quadPtr + 0x17) & 0xFFFFFFFC);
    *(long long**)(this + 0x14) = quadPtr;

    // Write final 8-byte field at the new position
    *quadPtr = param6;

    // Advance pointer by 8 bytes (size of param6)
    *(int*)(this + 0x14) = *(int*)(this + 0x14) + 8;
}