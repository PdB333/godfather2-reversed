// FUNC_NAME: BlendNode::computeBlendResult
float __fastcall BlendNode::computeBlendResult(void* thisPtr)
{
    float localValue;
    float temp;

    // Check if the blend is in "finished" state (offset +700 is a boolean flag)
    if (*(uint8_t*)((uintptr_t)thisPtr + 0x700) == 0)
    {
        // Not finished: compute a weighted blend
        float base = *(float*)((uintptr_t)thisPtr + 0xFC);   // m_fBaseValue
        float target = *(float*)((uintptr_t)thisPtr + 0x100); // m_fTargetValue
        float blendWeight = *(float*)((uintptr_t)thisPtr + 0x298); // m_fBlendWeight
        float speed = *(float*)((uintptr_t)thisPtr + 0x80);    // m_fSpeedFactor

        // First interpolation: blend toward target using weight
        float tempBlend = ((target - base) * blendWeight + base);
        // Apply a second scaling based on speed
        tempBlend = (tempBlend - base) * speed + base;
        localValue = tempBlend;

        // If there is a secondary blend source, blend further
        void* secondarySource = *(void**)((uintptr_t)thisPtr + 0x88); // m_pSecondaryBlend
        if (secondarySource != nullptr)
        {
            // Call a function on the secondary source (likely returns an interpolation value)
            float secondaryValue = (float)FUN_006c1070((int)secondarySource);
            // Retrieve a global default blend value (e.g., 0.0 or 1.0)
            float globalDefault = *(float*)0x00d5efd0; // DAT_00d5efd0
            // Interpolate between globalDefault and localValue using secondary result
            float intermediate = secondaryValue * (localValue - globalDefault) + globalDefault;
            // Final blend using the same weight factor
            localValue = (localValue - intermediate) * blendWeight + intermediate;
        }
    }
    else
    {
        // Finished state: use an alternative interpolation
        float progress = *(float*)((uintptr_t)thisPtr + 0x2DC); // m_fProgress
        float threshold = *(float*)0x00d5780c; // g_threshold (e.g., a time boundary)

        if (threshold < progress)
        {
            // After threshold: interpolate from m_fBaseValue toward m_fAfterTarget
            float afterTarget = *(float*)((uintptr_t)thisPtr + 0x1CC); // m_fAfterTarget
            float base = *(float*)((uintptr_t)thisPtr + 0xFC);        // m_fBaseValue
            localValue = (afterTarget - base) * (progress - threshold) + base;
        }
        else
        {
            // Before threshold: interpolate from m_fBeforeStart to m_fBaseValue
            float beforeStart = *(float*)((uintptr_t)thisPtr + 0x1BC); // m_fBeforeStart
            float base = *(float*)((uintptr_t)thisPtr + 0xFC);         // m_fBaseValue
            localValue = (base - beforeStart) * progress + beforeStart;
        }
    }

    // The result is stored in the x87 FPU extended precision register
    return localValue;
}