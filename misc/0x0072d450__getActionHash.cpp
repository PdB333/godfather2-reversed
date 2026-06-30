// FUNC_NAME: getActionHash
// Address: 0x0072d450
// Role: Maps a small integer (likely an enum or state index) to a hash/ID constant.
// The returned values are hardcoded 32-bit constants, possibly used as action identifiers or resource hashes.
unsigned int __fastcall getActionHash(unsigned char state)
{
    unsigned int result = 0;
    switch (state)
    {
    case 1:
        return 0xD376F9F3u;
    case 3:
        return 0xB2D93E6Fu;
    case 4:
        return 0xDC7E6FF4u;
    case 5:
        return 0x898D7BACu;
    case 7:
        result = 0xD33E610Eu;
        break;
    // default: result remains 0
    }
    return result;
}