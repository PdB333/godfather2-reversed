// FUNC_NAME: buildUniqueIdFrom16
uint64_t buildUniqueIdFrom16(uint16_t input) {
    // Construct a 64-bit unique identifier from a 16-bit input.
    // Format: [high byte (8 bits)][low byte (8 bits)][0xFF][0x07][0x01] (5 bytes) zero-extended to 64 bits.
    uint8_t lowByte = input & 0xFF;
    uint8_t highByte = input >> 8;

    // lower 32 bits: lowByte in the most significant byte position, followed by constant 0x00FF0701
    uint32_t lowerPart = (static_cast<uint32_t>(lowByte) << 24) | 0x00FF0701;

    // final 64-bit value: highByte in bits 39–32, lowerPart in bits 31–0
    uint64_t result = (static_cast<uint64_t>(highByte) << 32) | lowerPart;
    return result;
}