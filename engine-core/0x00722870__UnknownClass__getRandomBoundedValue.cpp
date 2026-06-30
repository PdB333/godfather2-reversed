// FUNC_NAME: UnknownClass::getRandomBoundedValue
float __thiscall UnknownClass::getRandomBoundedValue(void)
{
    float maxVal = *(float *)((int)this + 300);        // +0x12C: maximum (or range)
    float minVal = *(float *)((int)this + 0x128);      // +0x128: minimum (or base)
    if (minVal <= maxVal && minVal != maxVal)
    {
        int randInt = _rand();
        // Global constant at 0xE44590 (likely 1/RAND_MAX or similar)
        float scale = *(float *)0x00E44590;
        // Native decompiled: (randInt * scale * maxVal + minVal) - minVal
        // This reduces to randInt * scale * maxVal – implying minVal is ignored.
        // However, typical usage suggests random in [minVal, maxVal]
        // Possible decompiler mis-optimization; reconstructed as:
        return minVal + ((float)randInt * scale) * (maxVal - minVal);
    }
    return maxVal;
}