// FUNC_NAME: MakeExtendedID
// Function address: 0x0049a640
// Role: Builds a 64-bit identifier from a byte input by combining it with a constant prefix (0x300ff).
// Used extensively by multiple callers for constructing extended object type/resource IDs.

uint64_t __cdecl MakeExtendedID(byte inputByte)
{
    // Extend the byte to a 32-bit unsigned value (zero-extend)
    uint32_t lowerPart = (uint32_t)inputByte;

    // Combine: high 32 bits = 0x300ff, low 32 bits = lowerPart
    // Result: 0x300ff << 32 | lowerPart
    return ((uint64_t)0x300ff << 32) | (uint64_t)lowerPart;
}