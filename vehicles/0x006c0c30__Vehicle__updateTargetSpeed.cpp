// FUNC_NAME: Vehicle::updateTargetSpeed
void __thiscall Vehicle::updateTargetSpeed(float* outDesired) {
    float fVar1;
    float10 fVar2;
    float fVar3;
    __m128 chosenTarget; // packed 3 floats: x,y,z
    // Note: chosenTarget is actually 12 bytes, but as __m128 is 16, we use three floats and store separately.
    // The decompiler shows local_18 (8 bytes) and local_10 (4 bytes) representing a 3D vector.
    // We'll use individual floats for clarity.

    // Compute dot product of (targetPosition - position) and (intermediateTarget - position)
    float dx1 = *(float*)(this + 0x220) - *(float*)(this + 0x214);
    float dy1 = *(float*)(this + 0x224) - *(float*)(this + 0x218);
    float dz1 = *(float*)(this + 0x228) - *(float*)(this + 0x21c);
    float dx2 = *(float*)(this + 0x24c) - *(float*)(this + 0x214);
    float dy2 = *(float*)(this + 0x250) - *(float*)(this + 0x218);
    float dz2 = *(float*)(this + 0x254) - *(float*)(this + 0x21c);
    float dot = (dx1 * dx2 + dy1 * dy2 + dz1 * dz2);

    if (dot <= _DAT_00d577a0) {
        // Use targetPosition as the new intermediate target
        chosenTarget.x = *(float*)(this + 0x220);
        chosenTarget.y = *(float*)(this + 0x224);
        chosenTarget.z = *(float*)(this + 0x228);
    } else {
        // Keep the current intermediate target
        chosenTarget.x = *(float*)(this + 0x24c);
        chosenTarget.y = *(float*)(this + 0x250);
        chosenTarget.z = *(float*)(this + 0x254);
    }

    // Write the chosen target to the intermediate target slot
    *(float*)(this + 0x24c) = chosenTarget.x;
    *(float*)(this + 0x250) = chosenTarget.y;
    *(float*)(this + 0x254) = chosenTarget.z;

    // Compute distance from position to chosen target (returns 80-bit float)
    float distance; // output of FUN_006c9b00, written to a temporary buffer
    fVar2 = (float10)FUN_006c9b00(&chosenTarget, this + 0x214, &distance, 0);
    fVar1 = _DAT_00d5780c; // minimum distance threshold
    fVar3 = (float)fVar2;
    if (fVar2 < (float10)0) {
        fVar3 = 0.0f;
    }

    *outDesired = 0.0f; // default: no steering
    if ((fVar3 < fVar1) && (DAT_00d5ef54 < distance)) {
        *outDesired = 1.0f; // steer towards target
    }

    float currentSpeed = *(float*)(this + 0x298);
    if (currentSpeed <= fVar3) {
        // Accelerate or maintain speed
        float speedFactor = _DAT_00d5ef4c; // default factor
        if (DAT_00d5842c < currentSpeed) {
            speedFactor = DAT_00d5ef50; // use higher factor when above threshold
        }
        fVar2 = (float10)FUN_006c89b0(currentSpeed, fVar3, *(float*)(this + 0x168) * speedFactor);
        *(float*)(this + 0x298) = (float)fVar2;
    } else {
        // Decelerate to target speed
        *(float*)(this + 0x298) = fVar3;
    }
}