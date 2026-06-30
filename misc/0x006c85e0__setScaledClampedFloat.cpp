// FUNC_NAME: setScaledClampedFloat
// Address: 0x006c85e0
// This function scales a float by a global factor (likely frame time or time-scale inverse),
// stores it at offset 0x60 (a class member), then clamps the result to [0.0, g_maxValue].
// The clamping logic uses a short-circuit evaluation: if value <= 0.0, clamp to 0.0;
// else if value >= g_maxValue, clamp to g_maxValue. Otherwise unchanged.
void __thiscall setScaledClampedFloat(float value)
{
    // _DAT_0112a7a8 is a global time scale factor (e.g., 1/g_frameTime)
    float scaled = value / g_timeScaleFactor;
    // Offset 0x60: likely a speed, throttle, or target value member
    this->field_0x60 = scaled;

    // Clamp: if below 0 or above the global maximum, set to the boundary
    float boundary = 0.0f;
    if (scaled <= 0.0f || (boundary = g_maxValue, g_maxValue <= scaled)) {
        scaled = boundary;
    }
    this->field_0x60 = scaled;
}