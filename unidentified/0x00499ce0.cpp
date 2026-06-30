// FUN_00499ce0: UIHelper::compareBytewiseMask(uint32* inputBytes, uint32 mask)
bool __fastcall IsAnyByteInMask(uint32* inputBytes, uint32 mask)
{
    // Reads the first 4 bytes from the input pointer and compares each byte
    // against any of the four bytes of the mask. Returns true on first match.
    uint32 input = *inputBytes;
    // Note: inputBytes[1] is also read but unused (likely struct padding or optimization artifact).
    // Loop over 4 byte positions (0-3) of input.
    for (int i = 0; i < 4; i++)
    {
        char byteVal = *((char*)&input + i);

        if (byteVal == '\0' || byteVal == -1)
            continue;

        // Extract four bytes from mask (little-endian order)
        char byte0 = (char)(mask & 0xFF);
        char byte1 = (char)((mask >> 8) & 0xFF);
        char byte2 = (char)((mask >> 16) & 0xFF);
        char byte3 = (char)((mask >> 24) & 0xFF);

        if (byteVal == byte0 || byteVal == byte1 ||
            byteVal == byte2 || byteVal == byte3)
        {
            return true;
        }
    }
    return false;
}