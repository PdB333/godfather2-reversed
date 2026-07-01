// FUNC_NAME: InterpolationHelper::applySmoothInterpolation
void InterpolationHelper::applySmoothInterpolation(float currentValue, float targetValue, char instantFlag)
{
    // Static globals (likely from a singleton or static class data)
    // _DAT_00e52ffc stores a pointer/constant from DAT_012067e8 (maybe maxDelta or something)
    // _DAT_00d5780c is a default fallback value
    // _DAT_00e52ff4 is the divisor for normalizing the difference step
    // DAT_00e52fec, DAT_00e52ff0 are perhaps previous target and rate values
    // DAT_00e52fd4 is an interpolation mode (0=linear/cubic, 1=linear/cubic, 2=quaternion slerp)
    // DAT_0112ba9c is the base (current) value that gets interpolated toward

    // Initialize local variables
    float defaultFallback = _DAT_00d578c0;   // +0x00? (global)
    float zeroValue = 0.0f;                  // local_24
    float normalizedDelta;                   // local_28
    float blendedResult;                     // local_2c (reused)

    // Compute the normalized difference step
    float diff = currentValue - targetValue;
    float absDiff = (float)ABS((float10)FUN_006d6350(diff));  // FUN_006d6350 likely fabsf or similar
    normalizedDelta = absDiff / _DAT_00e52ff4; // _DAT_00e52ff4 is a speed/scaling factor

    // Select which value to use as the blend factor base
    float* blendFactorPtr;
    if (normalizedDelta <= 1.0f) {
        // Within range: use either zero or the normalized delta (clamp to positive)
        if (normalizedDelta >= 0.0f) {
            blendFactorPtr = &normalizedDelta;
        } else {
            blendFactorPtr = &zeroValue;
        }
    } else {
        // Out of range: use the default fallback value
        blendFactorPtr = &defaultFallback;
    }

    // The selected blend factor (raw)
    float rawBlend = *blendFactorPtr;
    normalizedDelta = DAT_00e52fec;   // store a preset target? (overwrites)
    blendedResult = rawBlend;         // store blend factor temporarily

    // Determine interpolation type based on mode flag
    if (instantFlag == 0) {
        if (DAT_00e52fd4 == 0) {
            // Mode 0: check a condition (FUN_00410f30) - possibly 'isPaused' or 'isActive'
            bool isActive = FUN_00410f30();
            if (!isActive) {
                // When not active: use cubic ease (rawBlend^3)
                blendedResult = rawBlend * rawBlend * rawBlend;
            }
            // else leave as rawBlend
        } else {
            // Mode 1: linear (no change) or Mode 2: quaternion-based
            if (DAT_00e52fd4 == 2) {
                // Mode 2: quaternion interpolation (slerp/nlerp) using an array
                float quatIn[4];
                quatIn[0] = rawBlend;   // assume first component is the blend factor
                quatIn[1] = 0.0f;
                quatIn[2] = 0.0f;
                quatIn[3] = 0.0f;
                // FUN_006daac0 likely performs quaternion multiplication with _DAT_00e52ffc
                FUN_006daac0(quatIn, _DAT_00e52ffc);
                blendedResult = quatIn[0]; // take the resulting first component
            }
            // For mode 1 (and others), blendedResult remains the rawBlend
        }
    }

    // Compute the final interpolated value using the base (DAT_0112ba9c) and target (normalizedDelta = DAT_00e52fec)
    // Formula: base + (target - base) * blendFactor
    float interpolatedValue = DAT_0112ba9c + (normalizedDelta - DAT_0112ba9c) * blendedResult;

    // Apply the interpolated value (likely setting a member or output)
    // FUN_007992a0 parameters: currentValue, interpolatedValue, _DAT_00e52ffc, &zeroValue, 0
    FUN_007992a0(currentValue, interpolatedValue, _DAT_00e52ffc, &zeroValue, 0);
}