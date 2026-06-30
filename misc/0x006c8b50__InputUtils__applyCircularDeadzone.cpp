// FUNC_NAME: InputUtils::applyCircularDeadzone

void applyCircularDeadzone(float *pX, float *pY)
{
    float x = *pX;
    float y = *pY;
    float magnitude = SQRT(x * x + y * y);

    // If magnitude is zero or exceeds maximum allowed, clamp to zero or max
    float clampedMag;
    if (magnitude <= 0.0f || magnitude >= g_analogDeadzoneMax) { // _DAT_00d5780c
        clampedMag = (magnitude <= 0.0f) ? 0.0f : g_analogDeadzoneMax;
    } else {
        clampedMag = magnitude;
    }

    // Compute angle from vertical (atan2(y, some constant))
    float angle = atan2(y, g_deadzoneAngleConstant); // _DAT_00d5f00c, FUN_0056aee0
    float cosAngle = fcos(angle);

    // Scale factors to preserve direction while mapping to circular boundary
    float scale = clampedMag / cosAngle;
    *pX = x * scale;
    *pY = y * scale;
}