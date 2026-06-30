// FUNC_NAME: encodeShortTo64Bit
// Function address: 0x00496590
// Encodes a 16-bit value into a 64-bit integer with fixed magic bytes 0xFF, 0x08, 0x01.
// Likely used for packing network packet identifiers or object UIDs in the EARS engine.

#include <cstdint>

uint64_t encodeShortTo64Bit(uint16_t input) {
    // Extract high and low bytes from the input
    uint8_t lowByte = static_cast<uint8_t>(input & 0xFF);
    uint8_t highByte = static_cast<uint8_t>(input >> 8);

    // Build the lower 32-bit portion: lowByte in bits 31-24, fixed 0xFF0801 in bits 23-0
    uint32_t lowPart = (static_cast<uint32_t>(lowByte) << 24) | 0xFF0801u;

    // Build the full 64-bit result: highByte in bits 39-32, lowPart in bits 31-0
    // Bits 63-40 remain zero
    uint64_t result = (static_cast<uint64_t>(highByte) << 32) | lowPart;

    return result;
}