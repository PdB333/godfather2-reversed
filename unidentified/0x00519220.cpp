// FUN_00519220: BytecodeWriter::emitQualifiedValue
void __thiscall BytecodeWriter::emitQualifiedValue(int *this, unsigned int low, unsigned int high)
{
    // Dereference this to get the stream buffer base pointer
    int *streamBase = (int *)*this;
    // Current write pointer is stored at streamBase+0x14
    unsigned char *writePtr = *(unsigned char **)(streamBase + 0x14);

    // Write the vtable/type function pointer table address for this value
    *(unsigned int **)writePtr = &PTR_FUN_01125144;
    writePtr += 4;

    // Align to next 4-byte boundary (round up)
    writePtr = (unsigned char *)(((unsigned int)writePtr + 3) & ~3);

    // Write the 64-bit value (low 32 bits, high 32 bits)
    *(unsigned long long *)writePtr = ((unsigned long long)high << 32) | low;
    writePtr += 8;

    // Update the stream's write pointer
    *(unsigned char **)(streamBase + 0x14) = writePtr;
}