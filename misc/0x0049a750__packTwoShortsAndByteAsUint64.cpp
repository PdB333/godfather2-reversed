// FUNC_NAME: packTwoShortsAndByteAsUint64
#include <cstdint>

// Combines two bytes into a 16-bit low word and a byte + converted byte into a 24-bit high word with zero low byte.
// Returns as a 64-bit integer (high 32 bits = shifted combo, low 32 bits = combined first two bytes).
// Called at 0x00692340 for constructing a compact network/intra-object data field.
uint64_t packTwoShortsAndByteAsUint64(uint8_t byte1, uint8_t byte2, uint32_t unused, float inputFloat, uint8_t byte3)
{
    // Combine first two bytes into a 16-bit low word (little-endian)
    uint32_t lowWord = static_cast<uint32_t>(byte2) | (static_cast<uint32_t>(byte1) << 8);
    // Convert float to a byte (clamp/scale via helper)
    uint8_t convertedByte = FUN_00499b80(inputFloat); // returns 0-255
    // Combine third byte with converted byte into 16-bit value, shift left by 8 to form high 24 bits (low 8 bits zero)
    uint32_t highPart = (static_cast<uint32_t>(byte3) | (static_cast<uint32_t>(convertedByte) << 8)) << 8;
    // Final 64-bit: high 32 bits = highPart, low 32 bits = lowWord
    return (static_cast<uint64_t>(highPart) << 32) | lowWord;
}