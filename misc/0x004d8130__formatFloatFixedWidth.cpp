// FUNC_NAME: formatFloatFixedWidth
int __cdecl formatFloatFixedWidth(char* dest, int fieldWidth, int maxFractionDigits, bool keepDecimalPoint, float value)
{
    char tempBuf[32];
    int sprintfLen = sprintf(tempBuf, "%1.9f", (double)value); // e.g. "123.456000000"
    char* dotPos = (char*)_strchr(tempBuf, '.');
    // integer part length = position of '.' in tempBuf
    int intPartLen = dotPos - tempBuf;
    int padding = fieldWidth - intPartLen;
    char* outPos;
    if (padding < 0) {
        // integer part longer than field width -> fill entire slot with spaces
        size_t totalLen = fieldWidth + (keepDecimalPoint ? 1 : 0) + maxFractionDigits;
        _memset(dest, 0x20, totalLen);               // spaces
        outPos = dest + totalLen;                    // past the filled area
    } else {
        outPos = dest;
        if (padding > 0) {
            _memset(dest, 0x20, padding);            // left pad with spaces
            outPos += padding;
        }
        // copy integer part (without the decimal point)
        _memcpy(outPos, tempBuf, intPartLen);
        outPos += intPartLen;
        // optionally insert decimal point
        if (keepDecimalPoint) {
            *outPos++ = '.';
        }
        // number of fraction digits originally formatted (after the dot)
        // iVar1 originally = sprintfLen - intPartLen = 1 + 9 = 10 for %1.9f
        int fracAvailable = sprintfLen - intPartLen - 1; // 9 digits after dot
        // copy up to maxFractionDigits or fracAvailable, whichever is smaller
        char* srcPos = dotPos + 1; // first fraction digit
        while (true) {
            if (fracAvailable <= 0) break;
            fracAvailable--;
            if (maxFractionDigits <= 0) break;
            *outPos++ = *srcPos++;
            maxFractionDigits--;
        }
        // pad with zeros if more digits requested than available
        while (maxFractionDigits > 0) {
            *outPos++ = '0';
            maxFractionDigits--;
        }
    }
    *outPos = '\0';
    return (int)(outPos - dest);
}