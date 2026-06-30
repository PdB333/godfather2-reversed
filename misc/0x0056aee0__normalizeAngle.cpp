// FUNC_NAME: normalizeAngle
// Function address: 0x0056aee0
// Role: Wraps a value into a symmetric range [-halfPeriod, halfPeriod] around zero.
// Uses two global constants: gAngleHalfPeriodFactor (DAT_00e2cd54, typically 0.5f) and gAnglePeriod (DAT_00e44564, typically the full period).
// The function is used extensively for angle normalization (e.g., heading, pitch).

extern float gAngleHalfPeriodFactor; // +0x00e2cd54
extern float gAnglePeriod;           // +0x00e44564

float normalizeAngle(float value, float period)
{
    float halfPeriod = period * gAngleHalfPeriodFactor; // e.g., period * 0.5f

    if (halfPeriod < value)
    {
        // Value is above the upper bound, wrap down
        return value - (int)((halfPeriod + value) / period) * period;
    }

    if (value <= gAnglePeriod - halfPeriod)
    {
        // Value is below the lower bound, wrap up (also handles in-range values that would still be correct)
        return value - (int)((value - halfPeriod) / period) * period;
    }

    // Value is already within the symmetric range
    return value;
}