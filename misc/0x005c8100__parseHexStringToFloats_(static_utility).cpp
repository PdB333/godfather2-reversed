// FUNC_NAME: parseHexStringToFloats (static utility)
// Address: 0x005c8100
// Parses an 8-character hex string (e.g., "FF0000FF") into 4 floats (RGBA, 0-255 each)
// Uses global lookup table g_hexDigitFloatTable[32] and multiplier g_hexPairMultiplier (likely 16.0f)

extern float g_hexDigitFloatTable[32]; // +0x00e2b210
extern float g_hexPairMultiplier;      // +0x00e2eb58 (expected value ~16.0f)

void parseHexStringToFloats(float* outFloats, const char* hexStr)
{
    // Extract 8 hex digits from the string, convert each to an index (0-31) via table
    // The masking and sign adjust logic ensures a safe modulo-32 mapping for '0'-'9', 'A'-'F', 'a'-'f'
    auto hexDigitIndex = [hexStr](int offset) -> uint {
        int ch = hexStr[offset] - 0x30;           // subtract ASCII '0'
        ch = ch & 0x8000001f;                     // keep sign bit and low 5 bits
        if (ch < 0) {
            ch = (ch - 1 | 0xffffffe0) + 1;       // sign-extend modulo 32
        }
        return (uint)ch;
    };

    uint idx0 = hexDigitIndex(0);
    uint idx1 = hexDigitIndex(1);
    uint idx2 = hexDigitIndex(2);
    uint idx3 = hexDigitIndex(3);
    uint idx4 = hexDigitIndex(4);
    uint idx5 = hexDigitIndex(5);
    uint idx6 = hexDigitIndex(6);
    uint idx7 = hexDigitIndex(7);

    // Each output float = multiplier * high_nibble + low_nibble
    outFloats[0] = g_hexPairMultiplier * g_hexDigitFloatTable[idx0] + g_hexDigitFloatTable[idx1];
    outFloats[1] = g_hexPairMultiplier * g_hexDigitFloatTable[idx2] + g_hexDigitFloatTable[idx3];
    outFloats[2] = g_hexPairMultiplier * g_hexDigitFloatTable[idx4] + g_hexDigitFloatTable[idx5];
    outFloats[3] = g_hexPairMultiplier * g_hexDigitFloatTable[idx6] + g_hexDigitFloatTable[idx7];
}