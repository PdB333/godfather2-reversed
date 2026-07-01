// FUNC_NAME: Animated::normalizeDuration
#include <cstdint>

// Global sentinel for invalid/unset scale factor
static const float kInvalidScale = *(float*)0x00d577a0;

// class Animated - time/duration scaling component (offset 0x198 = m_scaleDuration)
float __thiscall Animated::normalizeDuration(float10 rawDuration) // param_2 → rawDuration from another source
{
    // Retrieve some base value from param_2 (possibly another Animated object)
    float10 value = FUN_008be7f0(rawDuration); // note: param_2 is passed as 'rawDuration' but actually a handle

    // If the value is non-zero and our internal scale is valid, scale it
    if (value != 0.0f && *(float*)(this + 0x198) != kInvalidScale)
    {
        value = (float)value / *(float*)(this + 0x198);
    }
    return value;
}