// FUNC_NAME: getGlobalFrameCount
// Function at 0x0060d860: Returns the current global frame counter (or game tick) stored at 0x012058a4.
// This value is used by various subsystems for timing and sequencing (e.g., animation, network sync).
uint32_t getGlobalFrameCount(void)
{
    // DAT_012058a4 is a 4-byte global variable in .data section.
    // It is incremented each frame by the main game loop.
    return DAT_012058a4;
}