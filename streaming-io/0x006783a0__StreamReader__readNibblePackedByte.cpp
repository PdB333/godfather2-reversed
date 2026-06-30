// FUNC_NAME: StreamReader::readNibblePackedByte

#include <cstdint>

// Represents a bit-stream reading context for nibble-packed 12-bit values.
// The stream stores a sequence of bytes that encode 12-bit values.
// When modeFlag == 0, each input byte is used directly as an 8-bit result.
// When modeFlag != 0, two bytes are consumed: the first byte becomes the high 8 bits,
// and the high nibble of the second byte becomes the low 4 bits, yielding a 12-bit value.
// The low nibble of the second byte is left unused and will be part of the next read.
struct NibblePackReader {
    uint8_t* dataPtr;      // +0x00: current position in input stream
    uint16_t modeFlag;     // +0x04: 0 = raw byte mode, non‑zero = 12‑bit packed mode
};

// Reads one value from the stream according to the current mode.
// Returns the decoded 8‑bit or 12‑bit value as a char (truncated from the actual 12 bits).
// Advances dataPtr by 1 byte in both modes.
char __fastcall readNibblePackedByte(uint32_t unused /*ecx*/, NibblePackReader* ctx /*edx*/)
{
    char firstByte;
    uint8_t* nextPtr;

    // Check the mode flag stored at offset +0x04 (uint16)
    if (ctx->modeFlag == 0) {
        // Raw byte mode: read a single byte directly
        firstByte = *(char*)(ctx->dataPtr);
        ctx->dataPtr += 1;
        return firstByte;
    }

    // Packed 12‑bit mode
    firstByte = *(char*)(ctx->dataPtr);                // high 8 bits
    nextPtr = ctx->dataPtr + 1;                        // point to the second byte
    ctx->dataPtr = nextPtr;                            // advance pointer by one byte (only to the second byte)
    // Combine: firstByte << 4 | (secondByte >> 4)
    // The low nibble of the second byte is discarded and will be part of the next read.
    return (char)(((uint8_t)firstByte << 4) | (*nextPtr >> 4));
}