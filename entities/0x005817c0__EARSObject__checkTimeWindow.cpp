// FUNC_NAME: EARSObject::checkTimeWindow
uint __fastcall checkTimeWindow(void* thisPtr, int contextPtr, float minTime, uint flags)
{
    // thisPtr likely points to some animation or timed object
    // +4: type/flag field, requiring value > 9
    // +0x1c: current time or progress value
    float currentTime = *(float*)((uint)thisPtr + 0x1c);
    uint typeField = *(uint*)((uint)thisPtr + 4) & 0xff;

    // Global constants for time validation
    // DAT_00e2e210: minimum time delta threshold
    // DAT_00e44680: bitmask for time difference wrapping
    if (typeField > 9 && currentTime >= 0.0f &&
        *(float*)&DAT_00e2e210 <= (float)(((uint)(maxTime - minTime) & DAT_00e44680)))
    {
        // Extract bits from contextPtr+0x10 for direction/state
        uint highBits = (*(uint*)(contextPtr + 0x10) >> 0x1a) & 0x3F; // bits 26-31
        byte directionFlag = (byte)(~(*(uint*)(contextPtr + 0x10) >> 0x12)) & (byte)(~(flags >> 1));
        // directionFlag Low bit determines range check orientation

        if ((directionFlag & 1) == 0)
        {
            // Normal range: minTime <= currentTime < maxTime
            if (minTime <= currentTime && currentTime < maxTime)
            {
                return (highBits << 8) | 1; // set low byte to 1
            }
        }
        else
        {
            // Inverted range: currentTime <= minTime and maxTime < currentTime
            if (currentTime <= minTime && maxTime < currentTime)
            {
                return (highBits << 8) | 1;
            }
        }
    }
    // Return the original high bits with low byte cleared
    return (uint)thisPtr & 0xffffff00;
}