// FUNC_NAME: packTaggedId
// Address: 0x0049a680
// Packs two bytes (low, high) into a 64-bit identifier with a fixed tag (0x000300FF) in the upper 32 bits.
// Used to create a typed identifier from a 16-bit ID value. The tag likely indicates an object type or message class.

uint64_t packTaggedId(uint8_t byteLow, uint8_t byteHigh)
{
    // Combine the two bytes into a 16-bit value (big-endian: byteHigh in upper byte)
    uint32_t combined = ((uint32_t)byteHigh << 8) | (uint32_t)byteLow;
    // Prepend the constant tag to form a 64-bit identifier
    return (((uint64_t)0x000300FF) << 32) | (uint64_t)combined;
}