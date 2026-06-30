// FUNC_NAME: utf8EncodeCodePoint

#include <cstdint>

// External function that outputs a single byte (presumably to a buffer or stream)
extern void writeEncodedByte(uint8_t byte);

void utf8EncodeCodePoint(uint32_t codePoint)
{
    // Encode a Unicode code point into UTF-8 and output via writeEncodedByte.
    // This function handles code points up to 0xFFFF (BMP only).

    if (codePoint < 0x80)
    {
        // 1-byte sequence: 0xxxxxxx
        writeEncodedByte(static_cast<uint8_t>(codePoint));
    }
    else if (codePoint < 0x800)
    {
        // 2-byte sequence: 110xxxxx 10xxxxxx
        writeEncodedByte(static_cast<uint8_t>(0xC0 | (codePoint >> 6)));
        writeEncodedByte(static_cast<uint8_t>(0x80 | (codePoint & 0x3F)));
    }
    else
    {
        // 3-byte sequence: 1110xxxx 10xxxxxx 10xxxxxx
        writeEncodedByte(static_cast<uint8_t>(0xE0 | (codePoint >> 12)));
        writeEncodedByte(static_cast<uint8_t>(0x80 | ((codePoint >> 6) & 0x3F)));
        writeEncodedByte(static_cast<uint8_t>(0x80 | (codePoint & 0x3F)));
    }
}