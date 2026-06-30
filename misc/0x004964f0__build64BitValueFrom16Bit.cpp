// FUNC_NAME: build64BitValueFrom16Bit

uint64_t build64BitValueFrom16Bit(uint16_t input)
{
    // Extract low and high bytes from the 16-bit input
    uint8_t lowByte = (uint8_t)(input & 0xFF);
    uint8_t highByte = (uint8_t)(input >> 8);

    // Build the low 32-bit portion: lowByte shifted left by 16, then OR with constant 0xFF0601
    // This places lowByte at bits 23-16, and 0xFF, 0x06, 0x01 at bits 15-0
    uint32_t low32 = ((uint32_t)lowByte << 16) | 0xFF0601;

    // High 32-bit portion is simply the zero-extended highByte
    uint32_t high32 = (uint32_t)highByte;

    // Combine into a 64-bit result
    uint64_t result = ((uint64_t)high32 << 32) | low32;
    return result;
}