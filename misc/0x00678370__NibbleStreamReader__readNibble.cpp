// FUNC_NAME: NibbleStreamReader::readNibble
// Address: 0x00678370
// Reads a nibble (4 bits) from a byte stream. Structure:
// +0x00: byte* currentBytePtr
// +0x04: short highNibbleConsumed (0 = high nibble next, 1 = low nibble next)

#include <cstdint>

class NibbleStreamReader {
public:
    uint8_t* currentBytePtr;   // +0x00
    short     highNibbleFlag;  // +0x04: 0 if high nibble not yet consumed, 1 if low nibble pending

    // __fastcall: this in ECX
    uint8_t readNibble() {
        if (highNibbleFlag == 0) {
            // Read high nibble of current byte
            uint8_t byteVal = *currentBytePtr;
            highNibbleFlag = 1;          // mark high nibble consumed
            return byteVal >> 4;         // high nibble
        } else {
            // Read low nibble and advance pointer
            uint8_t byteVal = *currentBytePtr;
            highNibbleFlag = 0;          // reset for next byte
            currentBytePtr++;            // move to next byte
            return byteVal & 0x0F;       // low nibble
        }
    }
};