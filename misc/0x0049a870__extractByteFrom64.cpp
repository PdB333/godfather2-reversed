// FUNC_NAME: extractByteFrom64
// Function address: 0x0049a870
// Extracts a single byte from a 64-bit value represented by two 32-bit halves (lowPart, highPart) at the given byte offset (0-7).
byte extractByteFrom64(uint lowPart, uint highPart, int byteOffset) {
    // Pack the two 32-bit halves into a contiguous 8-byte buffer (little-endian order)
    uint buffer[2] = { lowPart, highPart };
    // Return the byte at the specified offset (0..7)
    return ((byte*)buffer)[byteOffset];
}