// FUNC_NAME: setQualityLevel
void setQualityLevel(int qualityLevel)
{
    // Quality level constants: 0 = low, 1 = medium, 2 = high? (from caller context)
    // Global variables:
    //   s_qualityMin (DAT_012058d0) - minimum allowed quality threshold
    //   s_qualityMax (DAT_00f15988) - maximum allowed quality threshold
    //   s_currentQualityLevel (DAT_011f3a30) - current quality level setting (1,2,3)

    int threshold = 22; // 0x16 - likely a framerate or detail limit

    if (qualityLevel == 0)
    {
        if (s_qualityMin < threshold)
        {
            s_qualityMin = threshold;
        }
        if (threshold < s_qualityMax)
        {
            s_qualityMax = threshold;
        }
        s_currentQualityLevel = 1;
    }
    else if (qualityLevel == 1)
    {
        if (s_qualityMin < threshold)
        {
            s_qualityMin = threshold;
        }
        if (threshold < s_qualityMax)
        {
            s_qualityMax = threshold;
        }
        s_currentQualityLevel = 2;
        return;
    }
    else if (qualityLevel == 2)
    {
        if (s_qualityMin < threshold)
        {
            s_qualityMin = threshold;
        }
        if (threshold < s_qualityMax)
        {
            s_qualityMax = threshold;
        }
        s_currentQualityLevel = 3;
        return;
    }
    return;
}