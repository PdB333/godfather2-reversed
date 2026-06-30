// FUNC_NAME: BitStreamReader::readPackedByte
// Address: 0x006796b0
// Role: Reads a packed symbol from a nibble-compressed stream.
//   If the mode flag (offset +0x2) is zero, returns a literal byte.
//   Otherwise, reads a 12-bit symbol (8 bits from first byte, 4 bits from high nibble of second byte)
//   and leaves the read pointer on the byte containing the remaining low nibble.
//   The return value is cast to char (low 8 bits). The high nibble is lost if the value exceeds 0xFF.
// Notes: param_1 (ecx) is unused and may be a dummy 'this' pointer.

struct BitStreamReader {
    char* dataPtr;   // +0x0: current read pointer
    short mode;      // +0x2: 0 = literal byte mode, non‑zero = packed 12‑bit mode
};

char __fastcall BitStreamReader::readPackedByte(int unused, BitStreamReader* stream) {
    // Read first byte
    char firstByte = *(stream->dataPtr);
    
    if (stream->mode == 0) {
        // Literal mode: just consume one byte
        stream->dataPtr++;
        return firstByte;
    } else {
        // Packed mode: consume first byte and high nibble of second byte
        unsigned char* nextBytePtr = (unsigned char*)(stream->dataPtr + 1);
        stream->dataPtr = (char*)nextBytePtr; // advance only by one byte (second byte not fully consumed)
        char lowNibble = (char)(*nextBytePtr >> 4); // high nibble of second byte
        return (char)(firstByte * 0x10 + lowNibble); // 12‑bit value, truncated to 8 bits
    }
}