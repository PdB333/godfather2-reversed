// FUNC_NAME: StreamWriter::writeEntry
void __thiscall StreamWriter::writeEntry(int* this, uint32_t param2, uint32_t param3, bool param4)
{
    // this points to a StreamWriter object
    // The object's first field is a pointer to a buffer descriptor (at offset +0x00)
    int* bufferDescriptor = (int*)*this; // dereference this to get buffer descriptor pointer

    // Offset +0x14 in the buffer descriptor is the current write cursor
    uint32_t* writeCursorPtr = (uint32_t*)(bufferDescriptor + 0x14); // actually offset in bytes: 0x14

    // Write a constant marker (address of a global pointer table) into the buffer
    **(uint32_t**)(bufferDescriptor + 0x14) = (uint32_t)&PTR_LAB_01124690;
    // Advance cursor by 4 bytes (size of a pointer)
    *(uint32_t*)(bufferDescriptor + 0x14) = *(uint32_t*)(bufferDescriptor + 0x14) + 4;

    // Write param2 as a 32-bit value
    **(uint32_t**)(bufferDescriptor + 0x14) = param2;
    *(uint32_t*)(bufferDescriptor + 0x14) = *(uint32_t*)(bufferDescriptor + 0x14) + 4;

    // Write param3 as a 32-bit value
    **(uint32_t**)(bufferDescriptor + 0x14) = param3;
    *(uint32_t*)(bufferDescriptor + 0x14) = *(uint32_t*)(bufferDescriptor + 0x14) + 4;

    // Write the boolean flag as a byte
    *(bool*)*(uint32_t*)(bufferDescriptor + 0x14) = param4;

    // Align the write cursor to the next 4-byte boundary
    *(uint32_t*)(bufferDescriptor + 0x14) = (*(uint32_t*)(bufferDescriptor + 0x14) + 4) & 0xfffffffc;
}