// FUNC_NAME: clampAndSetFloat
void clampAndSetFloat(float value) {
    extern float g_maxAllowedValue; // DAT_00d5e288
    float clampedValue;
    if (g_maxAllowedValue < value) {
        *(float *)(this + 0x40) = g_maxAllowedValue;
        return;
    }
    clampedValue = 0.0f;
    if (value >= 0.0f) {
        clampedValue = value;
    }
    *(float *)(this + 0x40) = clampedValue;
}