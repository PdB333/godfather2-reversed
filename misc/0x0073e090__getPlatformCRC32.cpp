// FUNC_NAME: getPlatformCRC32
uint32_t getPlatformCRC32(void)
{
    // FUN_00806440 likely returns platform identifier (e.g., 2=Xbox360, 3=PS3, default=PC)
    int platformId = FUN_00806440();
    
    if (platformId == 2) {
        return 0x8ac051f;      // Xbox360 CRC
    }
    if (platformId != 3) {
        return 0xaec6023b;     // PC CRC
    }
    return 0xfbc354bb;         // PS3 CRC
}