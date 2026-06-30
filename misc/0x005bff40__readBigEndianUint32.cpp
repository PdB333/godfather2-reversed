// FUNC_NAME: readBigEndianUint32
// Function address: 0x005bff40
// Reads a 32-bit big-endian integer from a 4-byte buffer.

int readBigEndianUint32(const unsigned char* bytes)
{
    // Equivalent to: (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3]
    return ((bytes[0] * 0x100 + bytes[1]) * 0x100 + bytes[2]) * 0x100 + bytes[3];
}