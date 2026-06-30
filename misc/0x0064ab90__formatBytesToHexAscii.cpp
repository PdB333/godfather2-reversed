// FUNC_NAME: formatBytesToHexAscii
// Converts binary data to a hex+ASCII dump string.
// Input: source data pointer, length (passed in EAX, capped at 63), output buffer (passed in EDI, assumed 256 bytes).
// Output buffer is cleared, then filled with hex digits and ASCII representation per byte.
// Non-printable and quote characters are replaced with '.'.
void formatBytesToHexAscii(const uint8_t* data, uint32_t length, char* outputBuffer)
{
    // Local hex digit table: 0-9, a-f
    const char hexTable[] = { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f' };

    // Cap length to 0x3f (63) – maximum bytes displayed
    if (length > 0x3f)
        length = 0x3f;

    if (outputBuffer != nullptr)
    {
        // Fill output buffer with spaces (0x20) and null-terminate
        memset(outputBuffer, 0x20, 0x100); // 256 bytes
        outputBuffer[0xff] = '\0';

        // Place a tab character at the end of the hex portion (before ASCII)
        outputBuffer[length * 3 - 1] = '\t';
    }

    char* hexPos = outputBuffer;
    for (uint32_t i = 0; i < length; i++)
    {
        // Extract hex digits from current byte
        uint8_t byteVal = data[i];
        char firstHex = hexTable[byteVal >> 4];
        char secondHex = hexTable[byteVal & 0xf];

        if (outputBuffer != nullptr)
        {
            // Write hex digits (each byte -> 2 hex chars)
            *hexPos = firstHex;
            hexPos[1] = secondHex;

            // Determine ASCII representation
            char asciiChar = (char)byteVal;
            // Replace non-printable or problematic chars with '.'
            if (asciiChar < ' ' || asciiChar > '~' || asciiChar == '\"' || asciiChar == '\'')
                outputBuffer[i + length * 3] = '.';
            else
                outputBuffer[i + length * 3] = asciiChar;
        }
        hexPos += 3; // Advance past two hex digits and the space already set by memset
    }
}