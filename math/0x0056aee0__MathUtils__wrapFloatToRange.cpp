// FUNC_NAME: MathUtils::wrapFloatToRange
float wrapFloatToRange(float value, float period)
{
    // Constants likely define the center or offset of the range
    extern float g_wrapOffset;   // DAT_00e2cd54
    extern float g_wrapLimit;   // DAT_00e44564

    float offset = period * g_wrapOffset;

    if (offset < value) {
        // Wrap downward
        return value - (float)(int)((offset + value) / period) * period;
    }

    if (value <= g_wrapLimit - offset) {
        // Wrap upward
        return value - (float)(int)((value - offset) / period) * period;
    }

    // Value is already within the desired range
    return value;
}