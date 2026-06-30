// FUNC_NAME: getGameFrameCount
// Address: 0x0069d530 - Simple accessor returning a global 16-bit value, likely a frame counter or game state flag.
unsigned short getGameFrameCount(void)
{
    return DAT_0112a03c; // Global variable, possibly current frame number or tick count.
}