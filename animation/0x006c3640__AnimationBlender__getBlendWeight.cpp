// FUNC_NAME: AnimationBlender::getBlendWeight
// Address: 0x006c3640
// Role: Computes normalized blend weight from an animation source, clamped to [0, g_blendMax] and scaled by g_blendScale. If forceMax, returns g_blendMax directly.

float __thiscall AnimationBlender::getBlendWeight(void *this, char forceMax) {
    float result;

    // pointer to animation source object (at this+0xE8)
    int *sourcePtr = *(int **)((char *)this + 0xE8);
    if (sourcePtr == nullptr) {
        result = 0.0f;
    } else {
        // subtract 0x48 to get base of containing struct for method call
        int *adjustedPtr = (int *)((char *)sourcePtr - 0x48);
        if (adjustedPtr == nullptr) {
            result = 0.0f;
        } else {
            // call a method on the adjusted pointer to get current progress/value
            float currentValue = (float)FUN_006c93c0(adjustedPtr);

            // blend range: start at +0xF4, end at +0xF8
            float blendStart = *(float *)((char *)this + 0xF4);
            float blendEnd   = *(float *)((char *)this + 0xF8);
            float normalized = (currentValue - blendStart) / (blendEnd - blendStart);

            // clamp to [0, g_blendMax] (global _DAT_00d5780c)
            if (normalized > 0.0f) {
                if (normalized > g_blendMax) {
                    normalized = g_blendMax;
                }
            } else {
                normalized = 0.0f;
            }

            // scale by global factor (DAT_00d5eee4)
            result = normalized * g_blendScale;

            // if forceMax flag set, override with max constant
            if (forceMax != '\0') {
                return g_blendMax;
            }
        }
    }
    return result;
}