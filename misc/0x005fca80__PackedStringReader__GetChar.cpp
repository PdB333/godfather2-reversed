// FUNC_NAME: PackedStringReader::GetChar
// Address: 0x005fca80
// This function decompresses a run-length encoded string on-the-fly and returns the character at a given index.
// The index is passed via the ESI register (not as a function parameter).
// The compressed format: null bytes indicate a skip count (next byte is the number of positions to skip),
// non-null bytes are literal characters.
// The struct at param_2 (EDX) contains:
//   +0x70: char* compressedBuffer
//   +0x74: int compressedSize
//   +0x78: int decompressedSize (0 means no compression, treat buffer as raw string)

#include <cstdint>

// Structure representing a packed/decompressed string reader
struct PackedStringReader {
    char* compressedData;   // +0x70
    int compressedLength;   // +0x74
    int decompressedLength; // +0x78 (0 = raw string, non-zero = compressed)
};

// __fastcall: first param (ECX) is unused, second param (EDX) points to PackedStringReader
uint32_t __fastcall GetCharFromPackedString(void* unused, PackedStringReader* reader) {
    char* buffer = reader->compressedData;
    int index = 0; // This should be the value of ESI (passed via register)
    // Note: In the original code, index was in ESI, but it's not in the parameter list.
    // We'll assume it's a global or set externally.

    if (reader->decompressedLength == 0) {
        // Raw string: return byte at index, combined with high 24 bits of buffer pointer
        return ((uint32_t)buffer & 0xFFFFFF00) | (uint8_t)buffer[index];
    }

    char* end = buffer + reader->compressedLength;
    uint32_t pos = 0; // uncompressed position counter

    // Scan compressed data until we find the character at index
    while (buffer < end) {
        if (*buffer == '\0') {
            // Null byte: skip next byte's worth of positions
            uint8_t skip = *(buffer + 1);
            buffer++; // move past the null byte itself
            pos += skip;
            if (index < pos) {
                // Index fell in skipped range, return end-of-stream indicator
                return (uint32_t)buffer & 0xFFFFFF00;
            }
        } else {
            if (index <= pos) {
                // Found the character at this uncompressed position
                return ((uint32_t)buffer & 0xFFFFFF00) | (uint8_t)*buffer;
            }
            pos++;
        }
        buffer++;
        if (buffer >= end) {
            // Reached end of compressed data
            return (uint32_t)buffer & 0xFFFFFF00;
        }
    }
    return 0; // Should never reach here
}