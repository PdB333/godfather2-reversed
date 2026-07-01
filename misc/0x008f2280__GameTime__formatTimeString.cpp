// FUNC_NAME: GameTime::formatTimeString
void __thiscall GameTime::formatTimeString(int this, undefined4 outputBuffer)
{
    uint totalSeconds;
    
    // Read 64-bit timestamp (milliseconds) from offset +0x20 and +0x24
    // Add 500ms for rounding, then divide by 1000 to get seconds
    totalSeconds = __aulldiv(*(uint *)(this + 0x20) + 500,
                             *(int *)(this + 0x24) + (uint)(0xfffffe0b < *(uint *)(this + 0x20)),
                             1000, 0);
    
    // Convert total seconds to hours, minutes, seconds and format
    // 0xe10 = 3600 (seconds per hour)
    // 0x3c = 60
    formatTimeString(totalSeconds / 0xe10,          // hours
                     (totalSeconds / 0x3c) % 0x3c, // minutes
                     totalSeconds % 0x3c,          // seconds
                     outputBuffer);
    return;
}