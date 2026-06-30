// FUNC_NAME: StreamWriter::writeArgs
void StreamWriter::writeArgs(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5, uint64_t arg6)
{
    // offset 0x14: pointer to current write position in the stream buffer
    uint8_t*& writePtr = *(uint8_t**)(this + 0x14);

    // ---- Write arg1 (4 bytes) ----
    *(uint32_t*)writePtr = arg1;
    // Align to next 4-byte boundary after the write
    writePtr = (uint8_t*)(((uintptr_t)writePtr + 7) & 0xFFFFFFFC);

    // ---- Write arg2 (4 bytes) ----
    *(uint32_t*)writePtr = arg2;
    writePtr = (uint8_t*)(((uintptr_t)writePtr + 7) & 0xFFFFFFFC);

    // ---- Write arg3 and arg4 as two 4-byte values, then arg5 as a 4-byte value ----
    // The base for this triple‑write is aligned to a 4‑byte boundary
    uint32_t* tripleBase = (uint32_t*)((uintptr_t)writePtr);
    tripleBase[0] = arg3;       // +0x00
    tripleBase[1] = arg4;       // +0x04
    tripleBase[2] = arg5;       // +0x08
    // Advance write pointer past the 12 bytes and align for the final 8‑byte write
    writePtr = (uint8_t*)(((uintptr_t)(tripleBase + 3) + 0x17) & 0xFFFFFFFC);
    // Note: the original code uses (writePtr + 0x17) & ~3 to skip past the triple and align;
    // the triple occupies exactly 12 bytes (3 × 4), so 0x17 ensures the pointer moves past them.

    // ---- Write arg6 as 8 bytes ----
    *(uint64_t*)writePtr = arg6;
    writePtr += 8;   // advance past the 8 bytes
}