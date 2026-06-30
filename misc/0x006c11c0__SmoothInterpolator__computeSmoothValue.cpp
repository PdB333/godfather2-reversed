// FUNC_NAME: SmoothInterpolator::computeSmoothValue
float __thiscall SmoothInterpolator::computeSmoothValue(void *thisPtr)
{
    // +0x298: handle or type identifier passed to interpolation function
    int handle = *(int *)((char *)thisPtr + 0x298);

    // +0x108: total range (e.g., duration), +0x10c: current progress
    float ratio = *(float *)((char *)thisPtr + 0x10c) / *(float *)((char *)thisPtr + 0x108);

    // Calls a Hermite or smoothstep interpolation:
    // FUN_006c91c0(handle, 0, 1.0f, 1.0f, ratio)
    float interpolated = FUN_006c91c0(handle, 0, 1.0f, 1.0f, ratio);

    // +0x80: blending factor between 1.0 and the interpolated value
    float blendFactor = *(float *)((char *)thisPtr + 0x80);

    // Linear blend: result = 1.0 + (interpolated - 1.0) * blendFactor
    return 1.0f + (interpolated - 1.0f) * blendFactor;
}