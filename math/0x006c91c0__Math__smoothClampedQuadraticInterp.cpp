// FUNC_NAME: Math::smoothClampedQuadraticInterp
float smoothClampedQuadraticInterp(float primary, float secondary, float candidate, float outMin, float outMax)
{
    // Determine the clamped input value: 
    // If secondary < primary, use candidate clamped to primary as upper bound; otherwise use secondary.
    float clampedInput = secondary;
    if (secondary < primary) {
        clampedInput = primary;
        if (candidate <= primary) {
            clampedInput = candidate;
        }
    }

    // Normalize clamped input relative to [secondary, primary] range and scale by global factor
    double t = (double)(((clampedInput - secondary) / (primary - secondary)) * DAT_00d5f00c);
    // Appears to be a seeded random or noise injection (function ignored)
    FUN_00b99fcb(); // Presumably a random seed or similar side effect
    // Quadratic ease curve: t^2 applied to output range
    float result = (float)(t * t) * (outMax - outMin) + outMin;

    // Clamp result between outMin and outMax based on threshold
    if (outMax - outMin <= _DAT_00d577a0) {
        // Small range: clamp to outMax if result > outMax, else to outMin
        if (result > outMax) {
            result = outMax;
        } else if (result < outMin) {
            result = outMin;
        }
    } else {
        // Larger range: clamp to outMin if result < outMin, else to outMax if > outMax
        if (result < outMin) {
            result = outMin;
        } else if (result > outMax) {
            result = outMax;
        }
    }
    return result;
}