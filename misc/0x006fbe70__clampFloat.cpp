// FUNC_NAME: clampFloat
void clampFloat(float value, float* out1, float* out2)
{
    // Global clamp limits (addresses 0x00d5c458 and 0x00d5eee4)
    extern float kMinClampValue;
    extern float kMaxClampValue;

    if (value < kMinClampValue) {
        *out1 = kMinClampValue;
        *out2 = *out1;
        return;
    }
    if (kMaxClampValue < value) {
        *out1 = kMaxClampValue;
        *out2 = *out1;
        return;
    }
    *out1 = value;
    *out2 = *out1;
    return;
}