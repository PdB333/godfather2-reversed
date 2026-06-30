// FUNC_NAME: Physics::limitHorizontalSpeed
void __fastcall Physics::limitHorizontalSpeed(float *outX, float *outZ, void *vehicleData)
{
    int frictionOverride = *(int *)((char *)vehicleData + 0x1c);
    bool isSpeedDisabled = FUN_00410d80();  // likely a debug flag

    if (isSpeedDisabled) {
        // Apply zero friction if speed limit is disabled
        applyHorizontalFriction(1, outX, outZ, 0.0f, 0.0f);
        return;
    }

    // Apply initial friction (maybe from surface)
    applyHorizontalFriction(1, outX, outZ, frictionOverride, frictionOverride);

    // Current scalar speed from vehicle data (e.g., engine speed)
    float currentSpeed = *(float *)((char *)vehicleData + 0x14);
    float dx = *outX;
    float dz = *outZ;

    // Compute horizontal length
    float length = __SQRT(dz * dz + dx * dx);

    // Clamp length to maximum speed (global constant)
    float clampedLength;
    if (length > 0.0f) {
        if (length >= _DAT_00d5780c) {
            clampedLength = _DAT_00d5780c;
        } else {
            clampedLength = length;
        }
    } else {
        clampedLength = 0.0f;
    }

    // Interpolate between current speed and clamped length
    // Formula: newScale = clampedLength * (maxSpeed - currentSpeed) + length * currentSpeed
    // but since we already clamped to max speed, this reduces to:
    float scale = clampedLength * (_DAT_00d5780c - currentSpeed) + length * currentSpeed;

    // Apply scale to original direction (keeps direction)
    *outX = dx * scale;
    *outZ = dz * scale;

    // Normalize or clamp final velocity vector
    FUN_006c8b50(outX, outZ);
}