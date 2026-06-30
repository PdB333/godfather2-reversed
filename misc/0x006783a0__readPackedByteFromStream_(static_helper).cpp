// FUNC_NAME: readPackedByteFromStream (static helper)
// Address: 0x006783a0
// Reads a byte from a packed stream that may be in raw mode or nibble-pair mode.
// The stream context has a pointer (offset 0x00) and a 16-bit mode flag (offset 0x04).
// When mode == 0, a single raw byte is consumed.
// When mode != 0, two bytes are read: the first byte's value forms the high nibble,
// and the high nibble of the second byte forms the low nibble; the pointer advances
// only past the first byte, leaving the second byte partially consumed.
// This pattern suggests a nibble-interleaved format where each pair of bytes yields
// one 8-bit value, and the low nibble of the second byte is handled elsewhere.

struct PackedStreamContext {
    unsigned char* ptr; // +0x00: current read position
    short mode;         // +0x04: 0 = raw byte mode, non-zero = nibble mode
};

unsigned char readPackedByteFromStream(PackedStreamContext* ctx) {
    if (ctx->mode == 0) {
        // Raw mode: read a single byte
        return *ctx->ptr++;
    } else {
        // Nibble mode: read two bytes, combine
        unsigned char highNibble = *ctx->ptr++; // first byte -> high nibble
        unsigned char secondByte = *ctx->ptr;   // read second byte (pointer does NOT advance)
        // Combine: high nibble * 16 + high nibble of second byte
        unsigned char result = (highNibble << 4) | (secondByte >> 4);
        return result;
    }
}