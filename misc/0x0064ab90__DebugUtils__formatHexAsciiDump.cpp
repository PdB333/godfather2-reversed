// FUNC_NAME: DebugUtils::formatHexAsciiDump
int DebugUtils::formatHexAsciiDump(const unsigned char* input, unsigned int length, char* outputBuffer)
{
    // Hex digit lookup table: "0123456789abcdef"
    static const char hexDigit[] = {
        '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'
    };

    // Clamp length to maximum allowed (0x3F = 63 bytes)
    unsigned int clampedLen = (length < 0x3F) ? length : 0x3F;

    // If output buffer is provided, initialize it with spaces and null-terminate
    if (outputBuffer != nullptr)
    {
        memset(outputBuffer, ' ', 0x100);
        outputBuffer[0xFF] = '\0';

        // Place a tab character at the end of the hex section (3 bytes per input byte)
        outputBuffer[clampedLen * 3 - 1] = '\t';
    }

    // Iterate through each input byte
    for (unsigned int i = 0; i < clampedLen; i++)
    {
        unsigned char byte = input[i];
        char highNibble = hexDigit[byte >> 4];
        char lowNibble = hexDigit[byte & 0x0F];

        if (outputBuffer != nullptr)
        {
            // Write hex representation: two hex characters
            outputBuffer[i * 3] = highNibble;
            outputBuffer[i * 3 + 1] = lowNibble;

            // ASCII representation: use '.' for non-printable or quote characters
            if (byte < ' ' || byte > '~' || byte == '\"' || byte == '\'')
            {
                outputBuffer[clampedLen * 3 + i] = '.';
            }
            else
            {
                outputBuffer[clampedLen * 3 + i] = (char)byte;
            }
        }
    }

    return 0;
}