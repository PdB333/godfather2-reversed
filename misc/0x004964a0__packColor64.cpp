// FUNC_NAME: packColor64
// Address: 0x004964a0
// Packs a 16-bit input into a 64-bit value with fixed bytes (0x01, 0x05, 0xFF) and the low/high bytes of the input.
uint64_t packColor64(uint16_t input)
{
    // Extract low and high bytes of the 16-bit input
    uint8_t lowByte = (uint8_t)(input & 0xFF);
    uint8_t highByte = (uint8_t)((input >> 8) & 0xFF);

    // Build lower 32 bits: lowByte (MSB), then 0xFF, 0x05, 0x01 (LSB)
    uint32_t lower32 = ((uint32_t)lowByte << 24) | 0x00FF0501;

    // Build upper 32 bits: highByte (MSB), then zeros
    uint32_t upper32 = ((uint32_t)highByte << 24);

    // Combine into 64-bit: highByte at bits 56-63, lowByte at bits 24-31, fixed bytes at bits 0-23
    return ((uint64_t)upper32 << 32) | lower32;
}