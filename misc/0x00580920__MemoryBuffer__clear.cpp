// FUNC_NAME: MemoryBuffer::clear
void __fastcall MemoryBuffer::clear(MemoryBuffer* this)
{
    // Clear the inline buffer of the MemoryBuffer object
    // Object layout:
    //   +0x00: unknown (vtable?)
    //   +0x04: unknown
    //   +0x08: unknown
    //   +0x0c: size in bytes (int)
    //   +0x10: inline data buffer

    int sizeWords = this->size >> 2;  // Number of 4-byte chunks
    undefined4* current = reinterpret_cast<undefined4*>(&this->data);  // +0x10

    // Zero out 16 bytes at a time (4 dwords)
    for (int i = sizeWords; i > 0; i--) {
        current[0] = 0;
        current[1] = 0;
        current[2] = 0;
        current[3] = 0;
        current += 4;
    }

    // Handle remaining bytes (0-3)
    uint remainder = this->size & 3;
    if (remainder != 0) {
        for (; remainder != 0; remainder--) {
            *current = 0;
            current++;
        }
    }
}