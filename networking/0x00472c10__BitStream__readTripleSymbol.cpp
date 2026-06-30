// FUNC_NAME: BitStream::readTripleSymbol
// Address: 0x00472c10
// Role: Reads three variable-length symbols from a bitstream (1 bit per symbol: 0 = consume 1 bit, 1 = consume 2 bits). 
//      If the third symbol is 1, calls additional decoding functions. Used in ghost/packet update processing.
// Structure offsets:
//   +0x00 - unknown
//   +0x04 - unknown
//   +0x08 - unknown
//   +0x0c - uint8* buffer (pointer to byte array containing the bitstream)
//   +0x18 - uint32 bitIndex (current bit position)
//   +0x1c - uint8 overflowFlag (set to 1 when bitIndex >= bitLimit)
//   +0x2c - uint32 bitLimit (total number of bits in the stream)
//   Other fields may exist but are not accessed here.

#include <cstdint>

// External functions (unknown signatures, guessed from usage)
void decodeGhostUpdate(BitStream* stream, uint8_t* outBuffer);  // FUN_004a97b0
void copyPacketChunk(uint32_t size, uint8_t* buffer);           // FUN_0064b9e0

class BitStream {
public:
    uint8_t*  buffer;      // +0x0c
    uint32_t  bitIndex;    // +0x18
    uint8_t   overflow;    // +0x1c
    uint32_t  bitLimit;    // +0x2c
    // other members...

    // Read one symbol: if next bit == 0, advance 1 bit; if 1, advance 2 bits.
    // Returns true if the bit was 1, false otherwise.
    // Sets overflow flag if the required advancement goes beyond bitLimit.
    bool readSymbol() {
        if (bitIndex >= bitLimit) {
            overflow = 1;
            return false; // return value undefined, but we mimic the pattern
        }
        uint8_t byte = buffer[bitIndex >> 3];
        bool bit = (byte >> (bitIndex & 7)) & 1;
        bitIndex++; // always consume at least 1 bit
        if (bit) {
            if (bitIndex >= bitLimit) {
                overflow = 1;
            } else {
                bitIndex++; // consume second bit (discarded)
            }
        }
        return bit;
    }

    // The unrolled triple read (from decompiled code)
    void readTripleSymbol() {
        // Symbol 1
        uint32_t idx = bitIndex;
        if (idx >= bitLimit) {
            overflow = 1;
        } else {
            uint8_t byte = buffer[idx >> 3];
            bitIndex = idx + 1; // always +1
            if ((byte >> (idx & 7)) & 1) {
                if (idx + 1 >= bitLimit) {
                    overflow = 1;
                } else {
                    bitIndex = idx + 2; // +2 total
                }
            }
        }

        // Symbol 2
        idx = bitIndex;
        if (idx >= bitLimit) {
            overflow = 1;
        } else {
            uint8_t byte = buffer[idx >> 3];
            bitIndex = idx + 1;
            if ((byte >> (idx & 7)) & 1) {
                if (idx + 1 >= bitLimit) {
                    overflow = 1;
                } else {
                    bitIndex = idx + 2;
                }
            }
        }

        // Symbol 3
        idx = bitIndex;
        if (idx >= bitLimit) {
            overflow = 1;
            return;
        } else {
            uint8_t byte = buffer[idx >> 3];
            bitIndex = idx + 1;
            if ((byte >> (idx & 7)) & 1) {
                if (idx + 1 >= bitLimit) {
                    overflow = 1;
                } else {
                    bitIndex = idx + 2;
                }
                // If the third symbol was 1, call additional functions
                uint8_t local_48[68]; // 0x44 bytes
                uint8_t local_4c[4];  // 0x4 bytes
                decodeGhostUpdate(this, local_48);
                copyPacketChunk(0x20, local_4c);
            }
        }
    }
};