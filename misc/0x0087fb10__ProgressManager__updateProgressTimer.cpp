// FUNC_NAME: ProgressManager::updateProgressTimer
// Function address: 0x0087fb10
// Called by 0x00880b80. Updates a normalized progress value with time-based interpolation.
// this +0x140: current progress (float, clamped to [0,1] or a global max)
// entity +0xa9c: active flag (int, non-zero enables time accumulation)
// Global 0x00d5c454: lerp factor/constant for interpolation
// Global 0x00d5780c: fallback max value (default 1.0f)

void __thiscall ProgressManager::updateProgressTimer(ProgressManager* this, Entity* entity)
{
    float currentTime;

    if (entity != 0) {
        // If entity's progress flag is zero, use 0 as time base
        if (*(int*)(entity + 0xa9c) == 0) {
            currentTime = 0.0f;
        }
        else {
            currentTime = getCurrentTime();  // FUN_00549a00
        }

        // Interpolate current progress towards new time with a global factor
        currentTime = interpolateFloat(currentTime, *(float*)(this + 0x140), g_lerpFactor); // FUN_004b9c30
        *(float*)(this + 0x140) = currentTime;

        // Clamp results
        if (currentTime > 1.0f) {
            *(float*)(this + 0x140) = g_maxProgress; // DAT_00d5780c
            return;
        }
        if (currentTime < 0.0f) {
            *(float*)(this + 0x140) = 0.0f;
        }
    }
    return;
}