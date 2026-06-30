// FUNC_NAME: MathUtils::smoothInterpolate
void __thiscall MathUtils::smoothInterpolate(int thisPtr, float from, float to, float t)
{
    // +0x60: smoothing factor (e.g., speed or blend weight)
    float factor = *(float *)(thisPtr + 0x60);
    
    // Compute the difference and apply an intermediate function (likely sqrt or linearize)
    float diff = to - from;
    float fVar1 = (float)FUN_004a1580(diff);  // FUN_004a1580 is likely sqrt or ease function
    
    // Compute the interpolated value and apply the same function again
    float interpolated = from + fVar1 * factor * t;
    FUN_004a1580(interpolated);  // Result discarded (possibly used for side effects)
    
    return;
}