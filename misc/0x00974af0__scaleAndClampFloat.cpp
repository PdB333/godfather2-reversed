// FUNC_NAME: scaleAndClampFloat
float scaleAndClampFloat(float input)
{
    // Global constants for scaling and clamping
    extern float g_scaleFactor;   // DAT_00e5758c
    extern float g_clampMin;      // DAT_00d8f7e8
    extern float g_clampMax;      // DAT_00d8f7ec

    float result = g_scaleFactor * input + g_clampMin;

    // Clamp between min and max
    if (result < g_clampMin)
        result = g_clampMin;
    else if (result > g_clampMax)
        result = g_clampMax;

    return result;
}