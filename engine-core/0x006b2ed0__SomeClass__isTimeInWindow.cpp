// FUNC_NAME: SomeClass::isTimeInWindow
int __fastcall SomeClass::isTimeInWindow(int thisPtr)
{
    float minTime;
    float maxTime;
    int local_c;
    int local_8;
    int local_4;
    uint8_t timeBuf[8];

    minTime = *(float *)(thisPtr + 0x104); // +0x104: window start time
    maxTime = *(float *)(thisPtr + 0x108); // +0x108: window end time

    // If times match or time check disabled, always return true
    if (minTime == maxTime || g_TimeCheckEnabled == 0)
        return 1;

    FUN_00826540(timeBuf); // presumably fills timeBuf with current game time data

    // Convert timeBuf components (likely hours/minutes/seconds or ticks) to a float
    float currentTime = (float)local_4 * g_TimeConversionFactor1 +
                        (float)local_8 * g_TimeConversionFactor2 +
                        (float)local_c;

    if (minTime < maxTime)
    {
        // Normal range: [minTime, maxTime]
        if (minTime <= currentTime && currentTime <= maxTime)
            return 1;
    }
    else
    {
        // Inverted range: window crosses midnight (e.g., 23:00 to 01:00)
        // Check if currentTime is not between maxTime and minTime (i.e., outside)
        if (maxTime <= currentTime && currentTime <= minTime)
            return 1;
    }

    return 0;
}