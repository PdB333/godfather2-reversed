// FUNC_NAME: decodeUtf8Char
// Decodes a single UTF-8 character from the byte stream pointed to by ESI (global register variable)
// Writes the 16-bit Unicode code point to *outChar
// Returns the number of bytes consumed (1, 2, or 3)
// Invalid continuation bytes (0x80-0xBF) are replaced with space (0x20)
int __fastcall decodeUtf8Char(ushort* outChar)
{
    byte firstByte = *unaff_ESI; // input byte stream pointer (set by caller in ESI)

    // Single-byte ASCII (0x00-0x7F)
    if ((char)firstByte >= 0) {
        *outChar = (ushort)(char)firstByte;
        return 1;
    }

    // Invalid start byte (continuation byte 0x80-0xBF) -> replace with space
    if ((firstByte & 0x40) == 0) {
        *outChar = 0x20;
        return 1;
    }

    // Two-byte sequence (0xC0-0xDF)
    if ((firstByte & 0x20) == 0) {
        ushort code = (ushort)((firstByte & 0x1F) << 6);
        *outChar = code | (unaff_ESI[1] & 0x3F);
        return 2;
    }

    // Three-byte sequence (0xE0-0xEF)
    ushort code = (ushort)((firstByte & 0x0F) << 6);
    code = (code | (unaff_ESI[1] & 0x3F)) << 6;
    *outChar = code | (unaff_ESI[2] & 0x3F);
    return 3;
}