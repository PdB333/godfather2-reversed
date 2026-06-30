// FUNC_NAME: StreamWriter::writeSerializedData
void __thiscall StreamWriter::writeSerializedData(int param2, int param3, int param4, int param5_lo, int param5_hi)
{
    int *dataBlock = *this;                     // dereference this to get internal data block pointer
    int &bufferPtr = *(int *)(dataBlock + 0x14); // buffer write pointer stored at offset +0x14

    // Write constant function pointer (type identifier / vtable?)
    *(int **)bufferPtr = &PTR_FUN_01124c4c;
    bufferPtr += 4;

    // Write param2 (no alignment performed)
    dataBlock = *this;                          // reload dataBlock (to avoid aliasing)
    *(int *)bufferPtr = param2;
    // Align to 4-byte boundary for next write
    int *aligned = (int *)((bufferPtr + 7) & ~3);
    *(int **)(dataBlock + 0x14) = aligned;
    *aligned = param3;                         // write param3 at aligned address
    // Align again for param4
    aligned = (int *)((aligned + 1) + 7 & ~3); // (bufferPtr+4 aligned) but simplified: re-read from structure
    // Actually we re-read bufferPtr from the structure after alignment
    // The decompiled code re-reads dataBlock and bufferPtr each time
    // We'll simulate exactly:
    dataBlock = *this;
    int nextWrite = *(int *)(dataBlock + 0x14); // now aligned address
    int *aligned2 = (int *)((nextWrite + 7) & ~3);
    *(int **)(dataBlock + 0x14) = aligned2;
    *aligned2 = param4;

    // Write 64-bit value (param5_lo, param5_hi)
    dataBlock = *this;
    long long *aligned8 = (long long *)((*(int *)(dataBlock + 0x14) + 7) & ~3);
    *(long long **)(dataBlock + 0x14) = aligned8;
    *aligned8 = ((long long)param5_hi << 32) | (unsigned int)param5_lo;

    // Final advance of buffer pointer by 8 bytes (size of the 64-bit write)
    *(int *)(dataBlock + 0x14) = *(int *)(dataBlock + 0x14) + 8;
}