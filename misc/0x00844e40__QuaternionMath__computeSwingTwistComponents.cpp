// FUNC_NAME: QuaternionMath::computeSwingTwistComponents

extern void FUN_00b9a9fa(); // Likely FPU operation (e.g., rounding mode set or NaN check)
extern void FUN_00b9c766(); // Another FPU operation (e.g., restore previous state)

extern const float g_scaleFactor;  // DAT_00d5eee4
extern const float g_clampMin;     // DAT_00d5ccf8
extern const float g_clampMax;     // _DAT_00d5780c
extern const float g_offset;       // DAT_00e44564

void QuaternionMath::computeSwingTwistComponents(const float* inputQuat, float* outComponent1, float* outComponent2, float* outComponent3)
{
    // inputQuat is expected as [x, y, z, w]
    float x = inputQuat[0];
    float y = inputQuat[1];
    float z = inputQuat[2];
    float w = inputQuat[3];

    // Component1 = scale * (w*y + z*x)  -> often related to swing around an axis
    float raw1 = g_scaleFactor * (w * y + z * x);
    FUN_00b9a9fa();
    *outComponent1 = raw1;

    // Raw2 = scale * (y*z - w*x)  -> then clamped to [g_clampMin, g_clampMax]
    float raw2 = g_scaleFactor * (y * z - w * x);
    float clamped;

    // Clamp: if raw2 < g_clampMin, set to min; else if raw2 > g_clampMax, set to max
    if (raw2 < g_clampMin)
    {
        clamped = g_clampMin;
    }
    else
    {
        if (g_clampMax < raw2)
        {
            clamped = g_clampMax;
        }
        else
        {
            clamped = raw2;
        }
    }

    double dClamped = (double)clamped;
    FUN_00b9c766();
    *outComponent2 = g_offset - (float)dClamped; // Component2 = offset - clamped value

    // Component3 = scale * (w*z + y*x)  -> other swing component
    float raw3 = g_scaleFactor * (w * z + y * x);
    FUN_00b9a9fa();
    *outComponent3 = raw3;
}