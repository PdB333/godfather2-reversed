// FUNC_NAME: SteeringController::computeSteeringOutput
float SteeringController::computeSteeringOutput(float currentAngle, float targetAngle1, float targetAngle2, float maxYawRate, float gain, float acceleration, float maxSteeringAngle, float outputScale, float deltaTime) {
    // Global constants (likely engine parameters)
    const float kTwoPi = 6.283185307179586f;
    const float kPi = 3.141592653589793f;
    const float kAngleEpsilon = 0.001f;          // small angle threshold
    const float kMaxRotation = 45.0f * kPi / 180.0f; // maximum steering angle (radians)
    const float kDeadZoneMultiplier = 0.0f;      // dead zone threshold multiplier
    const uint32 kAbsMask = 0x7FFFFFFF;          // bitmask to get absolute value of float via integer reinterpretation

    // Normalize angle differences (FUN_0056aee0 is expected to wrap to [-Pi, Pi])
    // First call: might set internal state or be redundant – kept for fidelity
    normalizeAngleDifference(targetAngle1 - currentAngle, kTwoPi, this);

    // Compute difference to second target
    float rawDiff = normalizeAngleDifference(targetAngle2 - currentAngle, kTwoPi);
    float diff = rawDiff;

    // If the raw difference is significant, adjust the sign for shortest path
    if (fabsf(rawDiff) > kAngleEpsilon) {
        float diffToFirst = normalizeAngleDifference(targetAngle2 - targetAngle1, kTwoPi);
        if (diffToFirst <= 0.0f) {
            if (kPi < diff) {
                diff -= kTwoPi; // wrap around
            }
        } else {
            if (diff < 0.0f) {
                diff += kTwoPi; // wrap around
            }
        }
    }

    // Clamp diff to [-maxSteeringAngle, maxSteeringAngle]
    float maxClamp = kMaxRotation - maxSteeringAngle;
    float clampedDiff = maxClamp;
    if (maxClamp <= diff && (clampedDiff = diff, maxSteeringAngle < diff)) {
        clampedDiff = maxSteeringAngle;
    }

    // Normalize the resulting angle difference
    float normalizedDiff = normalizeAngleDifference(clampedDiff + currentAngle, kTwoPi);
    normalizedDiff = normalizeAngleDifference(normalizedDiff - targetAngle1, kTwoPi);
    float finalDiff = normalizedDiff;

    // Determine upper bound based on sign of diff
    float bound;
    bool useBound;
    if (finalDiff <= 0.0f) {
        bound = maxClamp - maxYawRate; // assuming maxClamp = kMaxRotation - maxSteeringAngle
        useBound = bound < finalDiff;
    } else {
        bound = maxSteeringAngle - maxYawRate;
        useBound = finalDiff < bound;
    }
    if (!useBound && finalDiff != bound) {
        finalDiff = bound;
    }

    // Apply dead zone: check if absolute value is significant
    float absFinalDiff = *reinterpret_cast<float*>(&reinterpret_cast<uint32&>(finalDiff) & kAbsMask);
    if (gain * deltaTime * kDeadZoneMultiplier <= absFinalDiff) {
        // Apply acceleration smoothing
        float stepChange = finalDiff - gain * deltaTime;
        float scaledStep = stepChange * deltaTime;
        if (scaledStep * acceleration <= 0.0f && (stepChange = absFinalDiff, stepChange < deltaTime)) {
            deltaTime = stepChange;
        }
        // Final output with clamping
        if (scaledStep <= deltaTime) {
            if (scaledStep < kMaxRotation - deltaTime) {
                scaledStep = kMaxRotation - deltaTime;
            }
            return (scaledStep * gain) * outputScale;
        }
        return (deltaTime * gain) * outputScale;
    }
    return 0.0f * outputScale;
}