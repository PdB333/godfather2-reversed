// FUNC_NAME: StreamWriter::writePackedRecord
// Function address: 0x004fcf10
// Role: Writes a type tag and aligned data to a streaming buffer. The buffer is managed via a pointer at `this[0]` which points to a structure containing a write pointer at offset 0x14.

void __thiscall StreamWriter::writePackedRecord(int* this, uint32 tag, uint32 data1, uint32 data2, uint32 data3, uint32 data4_lo, uint32 data4_hi)
{
    // this[0] points to a buffer manager structure
    int* bufferMgr = (int*)*this;

    // Write type tag (function pointer) at current write position
    // bufferMgr+0x14 holds pointer to current write location
    **(int***)(bufferMgr + 0x14) = &PTR_FUN_01124ea4;
    // Advance write pointer by 4 bytes
    int** writePtr = (int**)(bufferMgr + 0x14);
    *writePtr = (int*)((int)*writePtr + 4);

    // Write data1 (no alignment before it, already aligned after tag)
    **(uint32**)(bufferMgr + 0x14) = data1;
    // Advance write pointer by 4 bytes, then align to next 4-byte boundary
    uint32* alignedPtr = (uint32*)(((uint32)*(int*)(bufferMgr + 0x14) + 7) & 0xFFFFFFFC);
    *(int**)(bufferMgr + 0x14) = (int*)alignedPtr;
    *alignedPtr = data2;

    // Align and write data3
    alignedPtr = (uint32*)(((uint32)*(int*)(bufferMgr + 0x14) + 7) & 0xFFFFFFFC);
    *(int**)(bufferMgr + 0x14) = (int*)alignedPtr;
    *alignedPtr = data3;

    // Align and write 8-byte value (data4_lo | (data4_hi << 32))
    alignedPtr = (uint32*)(((uint32)*(int*)(bufferMgr + 0x14) + 7) & 0xFFFFFFFC);
    *(int**)(bufferMgr + 0x14) = (int*)alignedPtr;
    *(uint64*)alignedPtr = (uint64)data4_lo | ((uint64)data4_hi << 32);
    // Advance write pointer by 8 bytes
    *(int*)(bufferMgr + 0x14) = (int)(alignedPtr + 2);

    // Write data4 (last 4-byte value) at current aligned position, no further alignment
    **(uint32**)(bufferMgr + 0x14) = data4_hi; // Actually this is param_5, final 4-byte
    *(int*)(bufferMgr + 0x14) = *(int*)(bufferMgr + 0x14) + 4;
}