// FUNC_NAME: pack7BytesToU64
uint64 pack7BytesToU64(byte b0, byte b1, byte b2, byte b3, byte b4, byte b5, byte b6)
{
    uint32 low = (uint32)b0 | ((uint32)b1 << 8) | ((uint32)b2 << 16) | ((uint32)b3 << 24);
    uint16 mid = (uint16)b4 | ((uint16)b5 << 8);
    return ((uint64)low) | ((uint64)mid << 32) | ((uint64)b6 << 48);
}