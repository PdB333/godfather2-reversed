// FUNC_NAME: Animation::getNormalizedProgress
// Address: 0x006c3640
// Role: Computes normalized progress of an animation or state machine, clamped and scaled.
// Offsets: +0xe8: pointer to animation/timer data; +0xf4: min value; +0xf8: max value.
// Globals: _DAT_00d5780c (max clamp, likely 1.0f), DAT_00d5eee4 (multiplier, likely speed factor).

float Animation::getNormalizedProgress(char forceMax) {
    float result;
    // Check if animation data pointer is null
    int* animData = *(int**)(this + 0xe8);
    if (animData == nullptr) {
        result = 0.0f;
    } else {
        // Offset to internal state/timer structure
        int* stateData = (int*)((char*)animData - 0x48);
        if (stateData == nullptr) {
            result = 0.0f;
        } else {
            // Get current value from function (likely returns current time or progress)
            float current = (float)FUN_006c93c0(stateData);
            float minVal = *(float*)(this + 0xf4);
            float maxVal = *(float*)(this + 0xf8);
            float normalized = (current - minVal) / (maxVal - minVal);
            // Clamp to [0, global max constant]
            if (normalized > 0.0f) {
                if (normalized > _DAT_00d5780c)
                    normalized = _DAT_00d5780c;
            } else {
                normalized = 0.0f;
            }
            result = normalized * DAT_00d5eee4;
            // If forceMax flag is set, return the maximum clamp constant
            if (forceMax != 0) {
                return (float)_DAT_00d5780c;
            }
        }
    }
    return result;
}