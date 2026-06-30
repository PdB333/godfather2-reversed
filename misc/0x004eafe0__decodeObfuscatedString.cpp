// FUNC_NAME: decodeObfuscatedString
void __fastcall decodeObfuscatedString(char* outBuffer, const char* encodedString)
{
    // Global substitution table: maps input bytes to decoded bytes (0 = terminator)
    extern const unsigned char gSubstitutionTable[256]; // 0x010c2330
    // Lookup table for base-conversion (indexed by byte+0xFF)
    extern const unsigned char gBaseConversionTable[256]; // 0x010c2331

    size_t i; // current index in encoded string
    unsigned char tempBuf[12]; // temporary buffer for mapped characters (max 11)
    size_t tempLen; // number of valid characters in tempBuf

    // Clear the 8-byte output buffer
    outBuffer[0] = 0;
    outBuffer[1] = 0;
    outBuffer[2] = 0;
    outBuffer[3] = 0;
    outBuffer[4] = 0;
    outBuffer[5] = 0;
    outBuffer[6] = 0;
    outBuffer[7] = 0;

    if (encodedString == nullptr)
        return;

    tempLen = 0;
    do {
        unsigned char mapped = gSubstitutionTable[(unsigned char)encodedString[tempLen]];
        if (mapped == 0)
            break;
        tempBuf[tempLen] = mapped;
        tempLen++;
    } while (tempLen < 11); // process up to 11 characters

    if (tempLen < 9) {
        // Short string: simple substitution copy
        if (tempLen > 0) {
            memcpy(outBuffer, tempBuf, tempLen);
        }
        return;
    }

    // Long string (9,10, or 11 characters): decode into exactly 8 bytes
    // _Size_00 = 23 - 2*tempLen  (Obfuscated formula: tempLen * -2 + 0x17)
    size_t tailLen = 23 - 2 * tempLen; // number of last characters to copy directly

    // Copy the last 'tailLen' characters from tempBuf to output
    if (tailLen > 0) {
        memcpy(outBuffer, tempBuf + (tempLen - tailLen), tailLen);
    }

    size_t outIdx = tailLen; // current write position in output

    // First character (index 0) decoded via a modified lookup with offset
    outBuffer[outIdx] = gBaseConversionTable[tempBuf[0] + 0xFF] - 0x80;
    outIdx++;

    // Process remaining characters in groups of 3
    // Each triple (a,b,c) maps to two 16-bit values via base-40 encoding
    // iVar4 = table[a] + table[b]*0x28 + table[c]*0x640
    const unsigned char* src = tempBuf + 1;
    while (outIdx < 8) {
        int decoded = (int)gBaseConversionTable[src[0] + 0xFF] +
                      (int)gBaseConversionTable[src[1] + 0xFF] * 0x28 +
                      (int)gBaseConversionTable[src[2] + 0xFF] * 0x640;

        outBuffer[outIdx]     = (char)(decoded & 0xFF);
        outBuffer[outIdx + 1] = (char)((decoded >> 8) & 0xFF);

        outIdx += 2;
        src    += 3;
    }
}