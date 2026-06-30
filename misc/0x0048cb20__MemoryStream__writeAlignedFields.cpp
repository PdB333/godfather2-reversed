// FUNC_NAME: MemoryStream::writeAlignedFields
void __thiscall MemoryStream::writeAlignedFields(MemoryStream *this, uint32_t low32, uint32_t high32, uint32_t intValue, bool flag)
{
    // +0x00: pointer to internal buffer base (int* bufferBase)
    int *bufferBase = *(int **)this;
    // +0x14: current write pointer within buffer (int* writePos)
    int *writePos = *(int **)(bufferBase + 0x14);

    // Write a function table pointer (likely vtable for deserialization)
    *(int **)writePos = (int *)&PTR_FUN_01123db4;
    // Advance past the pointer (4 bytes)
    writePos = (int *)((char *)writePos + 4);
    // Align to 4-byte boundary for 8-byte write
    writePos = (int *)(((uint32_t)writePos + 3) & ~3);

    // Write 64-bit value composed of high32 and low32
    *(uint64_t *)writePos = ((uint64_t)high32 << 32) | low32;
    // Advance with skip offset (0xB = 11 bytes) then align to next 4-byte boundary
    writePos = (int *)(((uint32_t)writePos + 0xB) & ~3);

    // Write 32-bit integer
    *(int *)writePos = intValue;
    // Advance past the integer (4 bytes)
    writePos = (int *)((char *)writePos + 4);

    // Write boolean as a byte
    *(bool *)writePos = (flag != false);
    // Align to next 4-byte boundary after the boolean
    writePos = (int *)(((uint32_t)writePos + 4) & ~3);

    // Store updated write position back to object
    *(int **)(bufferBase + 0x14) = writePos;
}