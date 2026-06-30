// FUNC_NAME: PackedArgsWriter::writeNextCallArgs
// Address: 0x0051b930
// Role: Serializes a set of arguments (4-byte constant, two 4-byte args, two 8-byte args) into a buffer for deferred execution.
// The buffer layout is: [4B constant][4B arg0][4B arg1][8B arg2][8B arg3] (28 bytes total).
// The internal buffer write pointer is stored at offset 0x14 of the buffer header structure pointed to by this.

void __thiscall PackedArgsWriter::writeNextCallArgs(void* this, uint32_t arg0, uint32_t arg1, uint64_t arg2, uint64_t arg3)
{
    // this points to an object whose first member is a pointer to a buffer header
    struct BufferHeader* header = *(struct BufferHeader**)this;

    // Write the constant identifier (often a function pointer or type ID)
    *(uint32_t*)header->writePtr = (uint32_t)&PTR_LAB_01125194; // +0x14 offset
    header->writePtr += 4; // advance past constant

    // Write arg0 (4 bytes)
    *(uint32_t*)header->writePtr = arg0;
    // Align write pointer to next 4-byte boundary (advances by 4 if already aligned)
    header->writePtr = (uint8_t*)((uint32_t)(header->writePtr + 3) & ~3); // equivalent to +4 due to alignment

    // Write arg1 (4 bytes)
    *(uint32_t*)header->writePtr = arg1;
    // Align again for next write
    header->writePtr = (uint8_t*)((uint32_t)(header->writePtr + 3) & ~3);

    // Write arg2 (8 bytes) – 32-bit low and high halves
    *(uint64_t*)header->writePtr = arg2; // low part at current, high part at current+4? Actually 8-byte write
    // Immediately after, write arg3 (8 bytes) at next 8-byte slot
    *(uint64_t*)(header->writePtr + 8) = arg3; // [1] in original means next 8 bytes

    // Advance write pointer past both 8-byte values (16 bytes total)
    header->writePtr += 16;
}