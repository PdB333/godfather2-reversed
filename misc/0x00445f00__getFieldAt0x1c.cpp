// FUNC_NAME: getFieldAt0x1c
// Address: 0x00445f00
// Role: Returns the 32-bit value at offset 0x1c from a pointer, with null safety.
uint32_t getFieldAt0x1c(void* ptr) {
    if (!ptr) {
        return 0;
    }
    // +0x1c: field (likely a pointer or handle)
    return *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(ptr) + 0x1c);
}