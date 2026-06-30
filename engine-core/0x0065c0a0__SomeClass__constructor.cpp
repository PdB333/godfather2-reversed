// FUNC_NAME: SomeClass::constructor
void SomeClass::constructor(void)
{
    // Temporary buffer of 0x40 bytes (64 bytes) allocated on stack
    uint32_t buffer[16]; // 16 * 4 = 64 bytes, but we only use first two uint32_t

    // Call initialization function to fill buffer with data (likely random or default values)
    generateInitializationData(0x40, buffer);

    // Copy first two 4-byte fields from buffer into the object's first two fields
    // Offset +0x00: first field (e.g., some ID or vector component)
    // Offset +0x04: second field (e.g., another component)
    *(uint32_t*)this = buffer[0];
    *(uint32_t*)((uint8_t*)this + 4) = buffer[1];
}