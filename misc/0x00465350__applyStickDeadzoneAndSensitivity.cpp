// FUNC_NAME: applyStickDeadzoneAndSensitivity
void __fastcall applyStickDeadzoneAndSensitivity(float* axisX, float* axisY, InputController* context)
{
    // Threshold for deadzone (inner) and full-scale (outer)
    static const float kDeadzoneThreshold = DAT_00e2b1a4;  // Outer threshold (full scale)
    static const float kDeadzoneSqThreshold = DAT_00e2cbe0; // Square of outer threshold? Possibly
    static const float kDefaultDeadzone = DAT_00e2eff4;    // Sentinel value meaning "use object's deadzone"

    float deadzoneRadius;
    // If the caller passed a sentinel (likely FLT_MAX), use the deadzone from the context object.
    if (in_XMM3_Da == kDefaultDeadzone) {
        deadzoneRadius = *(float*)((uint8_t*)context + 0x1694); // +0x1694: deadzone radius for this stick
    } else {
        deadzoneRadius = in_XMM3_Da;
    }

    float y = *axisY;
    float x = *axisX;
    float lengthSq = x*x + y*y;
    float length = SQRT(lengthSq);

    // If magnitude below deadzone, snap to zero.
    if (length < deadzoneRadius) {
        *axisY = 0.0f;
        *axisX = 0.0f;
        return;
    }

    // Compute linear ramp factor: 0 at deadzoneRadius, 1 at outer threshold.
    float rampFactor = (length - deadzoneRadius) / (kDeadzoneThreshold - deadzoneRadius);

    // Normalize to outer threshold if above squared threshold; otherwise set length to zero.
    float normalizedLength;
    if (lengthSq <= kDeadzoneSqThreshold) {
        normalizedLength = 0.0f;
    } else {
        normalizedLength = kDeadzoneThreshold / length;
    }

    // Apply both ramp and normalization, preserving direction.
    *axisY = normalizedLength * y * rampFactor;
    *axisX = normalizedLength * x * rampFactor;
}