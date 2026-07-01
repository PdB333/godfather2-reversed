// FUNC_NAME: clampedLerp (address 0x007f27a0)
// This function performs a clamped linear interpolation.
// It returns start if t < 0, end if t >= maxLerpValue, otherwise returns start*(maxLerpValue - t) + end*t.
// The global variable _DAT_00d5780c is assumed to be a maximum interpolation factor (e.g., a time threshold or duration).

extern float _DAT_00d5780c; // global max interpolation threshold

float clampedLerp(float start, float end, float t)
{
    if (t < 0.0f)
    {
        return start;
    }
    if (_DAT_00d5780c < t)
    {
        return end;
    }
    // Linear interpolation: start * (max - t) + end * t
    return ((_DAT_00d5780c - t) * start) + (end * t);
}