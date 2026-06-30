// FUNC_NAME: SmoothFollower::updateSmoothedPosition

// Reconstructed from Ghidra at address 0x006c57f0
// This function appears to compute a smoothed position for an object (e.g., camera or entity follower).
// It uses a direction vector (derived from angles or a reference point) and a time delta to update a cached blend factor and output a linearly interpolated result.

void __thiscall SmoothFollower::updateSmoothedPosition(
    void* thisPtr,
    float* currentPosition,        // [in] current 3D position (x, y, z)
    float* timePtr,                // [in] pointer to a time value (e.g., update timestamp)
    float* angleOrRef,             // [in] pointer to two floats (e.g., yaw and pitch) used to compute direction
    float* outPosition,            // [out] resulting smoothed position (single float? actually last line writes one float only, but probably part of vector)
    int flags,                     // [in] unspecified flags (param_6)
    float alpha                     // [in] blend factor for final interpolation (0..1, e.g., deltaTime)
)
{
    float directionVec[3];
    float desiredPos[3];
    float distanceScalar;
    float result;
    float tempArray[1]; // unused output buffer from FUN_006c9b00

    // FUN_004a2540: likely computes a 3D direction vector from two angles or from a reference point.
    // It takes output vector pointer, first float (yaw), second float (pitch).
    // Output stored at directionVec (local_18, local_14, local_10).
    FUN_004a2540(directionVec, angleOrRef[0], angleOrRef[1]);

    // timeDelta = constant "currentEngineTime" - *timePtr (possibly time since last update)
    float timeDelta = DAT_00e44564 - *timePtr;

    // Compute desired position by moving current position along directionVec scaled by timeDelta
    desiredPos[0] = directionVec[0] * timeDelta + currentPosition[0];
    desiredPos[1] = directionVec[1] * timeDelta + currentPosition[1];
    desiredPos[2] = directionVec[2] * timeDelta + currentPosition[2];

    // FUN_006c9b00: returns a scalar value (maybe distance from desiredPos to currentPosition or something else)
    // The fourth argument is an unused output buffer (size 1 float) and the last arg is 1 (unknown flag).
    float scalar = (float)FUN_006c9b00(desiredPos, currentPosition, tempArray, 1);

    // Handle negative result (clamp to zero)
    float effectiveScalar = scalar;
    if (scalar < 0.0f) {
        effectiveScalar = 0.0f;
    }

    // Check if the computed scalar is within thresholds and if the blend factor (local_8, from tempArray?) is valid
    // local_8 is likely from the output of FUN_006c9b00 (tempArray[0]).
    // The following condition appears to determine whether to allow the update.
    // DAT_00d5780c and DAT_00d5ef54 are global constants.
    if (effectiveScalar < _DAT_00d5780c && DAT_00d5ef54 < tempArray[0]) {
        // If condition met, the blend will be adjusted (param_3 set to non-zero)
        // (This influences the subsequent call to FUN_006c45a0)
    }
    // param_3 is reused here as a flag: set to (float*)0 = false, or (float*)1 = true.
    // In the decompiler, param_3 was originally the second pointer, but here it's being reused as boolean flag.
    // This is a side effect of decompiler; we'll capture it as a boolean.
    bool allowBlend = false;
    if (effectiveScalar < _DAT_00d5780c && DAT_00d5ef54 < tempArray[0]) {
        allowBlend = true;
    }

    // Read the current blend factor from the object's state (offset +0x2D4)
    float currentBlend = *(float*)((char*)thisPtr + 0x2D4);

    // If currentBlend <= effectiveScalar, we are catching up; apply interpolation with speed scaling.
    if (currentBlend <= effectiveScalar) {
        // Choose a speed multiplier based on another threshold (DAT_00d5842c)
        float speedScale;
        if (DAT_00d5842c < currentBlend) {
            speedScale = DAT_00d5ef50;
        } else {
            speedScale = DAT_00d5ef4c;
        }
        // Multiply by a base speed from object (+0x168) to get the interpolation rate
        float interpolationRate = *(float*)((char*)thisPtr + 0x168) * speedScale;
        // FUN_006c89b0 performs a smooth interpolation between currentBlend and effectiveScalar using interpolationRate
        float newBlend = (float)FUN_006c89b0(currentBlend, effectiveScalar, interpolationRate);
        *(float*)((char*)thisPtr + 0x2D4) = newBlend;
    } else {
        // If currentBlend > effectiveScalar, simply set to the effective scalar (overshoot case)
        *(float*)((char*)thisPtr + 0x2D4) = effectiveScalar;
    }

    // FUN_006c45a0: computes the final smoothed position based on the updated blend factor and other parameters.
    // It takes desiredPos, currentPosition, angleOrRef, the new blend, the allowBlend flag, and writes output into outPosition (but only a float at the end).
    // The final parameter 'param_4' is reused to hold a computed value (maybe speed or distance).
    // For simplicity, we'll assume it returns an interpolated value that is then blended with the previous outPosition.
    float computedValue;
    FUN_006c45a0(desiredPos, currentPosition, angleOrRef, *(float*)((char*)thisPtr + 0x2D4), allowBlend ? (float*)1 : (float*)0, currentPosition, angleOrRef, &computedValue);

    // Final blend: Lerp between previous outPosition and computedValue scaled by a constant and alpha.
    // _DAT_00d5780c is likely 1.0f.
    *outPosition = computedValue * DAT_00e445c8 * alpha + (_DAT_00d5780c - alpha) * *outPosition;
}

// End of reconstructed function.