// FUNC_NAME: BufferWriter::writeAlignedCommand
void __thiscall BufferWriter::writeAlignedCommand(void* param2, void* param3, int param4, int param5, int param6) {
    // this points to a BufferWriter object, whose first field is a pointer to a DataBuffer structure.
    // DataBuffer has a write position pointer at offset +0x14.
    DataBuffer* buffer = *(DataBuffer**)this;
    char*& writePos = buffer->writePos; // +0x14: current write pointer

    // Write a type tag (function pointer/identifier) at current position, advance by 4 bytes
    *(void**)writePos = (void*)&PTR_FUN_01124c4c;
    writePos += 4;

    // Write param2 at the next 4-byte aligned position (already aligned after type tag)
    *(void**)writePos = param2;

    // Align to next 4-byte boundary (mask = (addr + 7) & ~3) before writing param3
    writePos = (char*)(((int)writePos + 7) & 0xfffffffc);
    *(int*)writePos = (int)param3; // param3 as a 4-byte integer

    // Align to next 4-byte boundary before param4
    writePos = (char*)(((int)writePos + 7) & 0xfffffffc);
    *(int*)writePos = param4;

    // Align to next 4-byte boundary before the 8-byte value (param5:param6)
    writePos = (char*)(((int)writePos + 7) & 0xfffffffc);
    *(int64*)writePos = ((int64)param6 << 32) | (unsigned int)param5;
    writePos += 8; // advance past the 8-byte chunk
}