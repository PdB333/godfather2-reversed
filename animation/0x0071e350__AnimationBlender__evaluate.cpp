// FUNC_NAME: AnimationBlender::evaluate
float __thiscall AnimationBlender::evaluate(int thisPtr, float t)
{
    // Global default return value (e.g., for missing states)
    float defaultReturn = *(float*)0x00e44758;

    // Current animation state at +0x78 (0 = stopped, 0x48 = idle?)
    int animState = *(int*)(thisPtr + 0x78);

    if (animState != 0 && animState != 0x48)
    {
        // Active state: evaluate the curve with no blend weight
        return evaluateFloatCurve(t, 0.0f); // FUN_00726710
    }

    // Stopped/idle: try to get an interpolator object
    int* pInterpolator = getAnimInterpolator(); // FUN_0071e270 - returns pointer or 0
    if (pInterpolator != nullptr)
    {
        // Get current transition progress (weight) from interpolator
        float blendWeight = getTransitionProgress(pInterpolator + 0x130); // FUN_004702b0, +0x130: progress field
        return evaluateFloatCurve(t, blendWeight);
    }

    return defaultReturn;
}