// FUNC_NAME: packTwoBytesWithConstantTag
// Address: 0x004965e0
// Helper function: packs two bytes into a 64-bit value with a fixed tag byte (0x01) in the lowest position.
// Used extensively by FUN_006a0840 (likely to generate packed IDs or indices).
uint64_t packTwoBytesWithConstantTag(uint8_t lowByte, uint8_t highByte)
{
    // Construct a 3-byte value: highByte (bits 23-16), lowByte (bits 15-8), tag 0x01 (bits 7-0)
    // Zero-extend to 64-bit.
    return ((uint64_t)highByte << 16) | ((uint64_t)lowByte << 8) | 0x01ULL;
}