// FUNC_NAME: BufferReader::dispatchCommand
void __thiscall BufferReader::dispatchCommand(int this, void (**handler)(uint32_t, uint64_t, uint64_t, uint32_t, uint64_t, int32_t))
{
    // this+0x18 is pointer to current read position in buffer
    uint8_t* bufferPos = *(uint8_t**)(this + 0x18);
    // Align the pointer to nearest 4-byte boundary (round up)
    uint8_t* aligned = (uint8_t*)((uint32_t)bufferPos + 7U & 0xFFFFFFFC);
    *(uint8_t**)(this + 0x18) = aligned;

    // Read header fields from aligned buffer
    // Offset 0: uint64 value 1
    uint64_t arg1 = *(uint64_t*)aligned;
    // Offset 8: uint64 value 2
    uint64_t arg2 = *(uint64_t*)(aligned + 8);
    // Offset 16: uint32 value 3
    uint32_t arg3 = *(uint32_t*)(aligned + 16);

    // Advance past the 20-byte header (8+8+4)
    *(uint8_t**)(this + 0x18) = aligned + 0x14;
    // Read iVar5 at offset 0x14 (20)
    int32_t iVar5 = *(int32_t*)(aligned + 0x14);

    // Advance to next 8-byte word
    *(uint8_t**)(this + 0x18) = aligned + 0x18; // Actually aligned+0x18 = aligned+24
    // Read iVar6 at offset 0x18 (24)
    int32_t iVar6 = *(int32_t*)(aligned + 0x18);

    // Compute a new buffer position based on alignment of iVar6 bytes
    // (base + iVar6 + 0x1b) aligned to iVar6 boundary
    uint32_t alignedBase = ((uint32_t)aligned + iVar6 + 0x1b) & ~((uint32_t)iVar6 - 1U);
    // Final buffer pointer updates to iVar5 * 32 + alignedBase
    *(uint32_t*)(this + 0x18) = iVar5 * 0x20 + alignedBase;

    // Call the handler function with the extracted arguments
    (*handler)((uint32_t)aligned, arg1, arg2, arg3, (uint64_t)iVar5 | ((uint64_t)(-(uint32_t)(iVar5 != 0) & (uint64_t)alignedBase) << 32), iVar6);
}