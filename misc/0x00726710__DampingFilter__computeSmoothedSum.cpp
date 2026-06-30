// FUNC_NAME: DampingFilter::computeSmoothedSum
// Address: 0x00726710
// Role: Computes a smoothed sum of a 4-component target vector scaled by per-component damping factors,
// with optional time-based scaling when bit 3 of flags is set.

float __thiscall DampingFilter::computeSmoothedSum(void* thisPtr, float* targetVector, float deltaTime)
{
    // Global default damping multiplier (from .data)
    float defaultDamping = _DAT_00d5780c;

    float dampingFactor = defaultDamping;

    // Check bit 3 of flags at offset 0x110 (e.g., DAMPING_FLAG_USE_TIME_DELTA)
    uint flags = *(uint*)((char*)thisPtr + 0x110);
    if ((flags & 8) != 0) {
        // Reduce damping by the ratio of deltaTime to a stored time constant at +0x74
        float timeConstant = *(float*)((char*)thisPtr + 0x74);
        dampingFactor = defaultDamping - deltaTime / timeConstant;
    }

    // Retrieve per-component damping coefficients from object fields (+0xe4, +0xe8, +0xec, +0xf0)
    float dampingCoeffX = *(float*)((char*)thisPtr + 0xe4);
    float dampingCoeffY = *(float*)((char*)thisPtr + 0xe8);
    float dampingCoeffZ = *(float*)((char*)thisPtr + 0xec);
    float dampingCoeffW = *(float*)((char*)thisPtr + 0xf0);

    // Apply smoothing function (FUN_0077e890) to each component of the target vector
    float smoothedX = (float)FUN_0077e890(targetVector[0], dampingCoeffX * dampingFactor);
    float smoothedY = (float)FUN_0077e890(targetVector[1], dampingCoeffY * dampingFactor);
    float smoothedZ = (float)FUN_0077e890(targetVector[2], dampingCoeffZ * dampingFactor);
    float smoothedW = (float)FUN_0077e890(targetVector[3], dampingCoeffW * dampingFactor);

    // Return the sum of the smoothed components
    return smoothedW + (smoothedZ + (smoothedY + smoothedX));
}