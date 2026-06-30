// FUNC_NAME: smoothInterpolateWithClamp
float smoothInterpolateWithClamp(float currentValue, float targetValue, float factor)
{
    float delta = targetValue - currentValue; // param_2 = param_2 - param_1

    // Check if delta exceeds threshold to apply smoothing
    if (s_smoothEnableThreshold < delta)  // _DAT_00d577a0
    {
        float range = s_maxSmoothRange - s_minSmoothRange; // DAT_00e51178 - _DAT_00e511a8
        float smoothedDelta;

        if (range <= currentValue)
        {
            smoothedDelta = s_baseSmoothFactor; // _DAT_00d5780c
            if (currentValue < s_maxSmoothRange)
            {
                float t = (currentValue - range) / (s_maxSmoothRange - range);
                smoothedDelta = s_smoothMultiplier * t + (s_baseSmoothFactor - t);
            }
        }
        else
        {
            smoothedDelta = (s_baseSmoothFactor - currentValue / range) * s_smoothMultiplier + currentValue / range;
        }

        smoothedDelta *= factor;
        if (smoothedDelta < delta)
        {
            return currentValue + smoothedDelta;
        }

        // Clamp delta if it exceeds max allowed offset
        if (delta < s_maxClampOffset - smoothedDelta) // DAT_00e44564
        {
            delta = s_maxClampOffset - smoothedDelta;
        }
    }

    // No smoothing applied, just move linearly
    return currentValue + delta;
}