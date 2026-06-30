// FUNC_NAME: AIComponent::testDetection_
bool __thiscall SomeClass::isTargetDetectable(const float* targetPos, bool checkRangeOnly, bool checkLineOfSight, float rangeScale)
{
    // compute offset from self position (this+0x44, this+0x48, this+0x4c)
    float dx = targetPos[0] - *(float*)(this + 0x44);
    float dy = targetPos[1] - *(float*)(this + 0x48);
    float dz = targetPos[2] - *(float*)(this + 0x4c);

    float distSq = dx*dx + dy*dy + dz*dz;

    // distance thresholds: this+0x58 = inner radius squared? this+0x5c = outer radius squared
    float innerDistSq = *(float*)(this + 0x58);
    float outerDistSq = *(float*)(this + 0x5c) * rangeScale;

    if (distSq < outerDistSq) {
        if (distSq < innerDistSq) {
            return false; // too close
        }
    } else if (checkRangeOnly) {
        return false; // too far and checkRangeOnly set
    }

    // large constant check (likely max detection distance)
    if (distSq <= 1.0e38f) { // _DAT_00d577a0 assumed huge
        return true; // always success if within distance thresholds? (unclear, but follows original)
    }

    // === angle and line-of-sight checks ===
    // transform offset to local orientation frame (this+0x2c assumed orientation matrix)
    float localX, localY, localZ;
    transformVectorToLocal(&localX, &localY, &localZ, (float*)(this + 0x2c), &dx, &dy, &dz); // FUN_004a07f0

    // normalize local offset
    float vec3[3] = {localX, localY, localZ};
    normalizeVector(vec3, vec3); // FUN_0056afa0

    // compute dot product with second row of orientation matrix? (this+0x38,0x3c,0x40)
    float dot = *(float*)(this + 0x38) * vec3[1] +
                *(float*)(this + 0x3c) * vec3[0] +
                *(float*)(this + 0x40) * vec3[2];

    // clamp dot to [0,1] (large negative/positive ranges)
    float candidates[3] = {0.0f, dot, 1.0f}; // _DAT_00d5780c, DAT_00d5ccf8
    // pick the middle value (clamp to 0..1)
    float clamped;
    if (dot <= 0.0f) clamped = 0.0f;
    else if (dot >= 1.0f) clamped = 1.0f;
    else clamped = dot;

    // compare with angle threshold (this+0x50)
    float angleThreshold = *(float*)(this + 0x50);
    if (clamped < angleThreshold || clamped == angleThreshold) {
        // also need line-of-sight check if required
        bool losCheck = true;
        if (checkLineOfSight) {
            losCheck = (bool)FUN_006e5bb0(targetPos);
        }
        if (losCheck) {
            // additional dot product after re-transforming offset?
            // transform offset back to world? (FUN_0043a210) then compute dot with normalized local
            // This is a second check: compare to this+0x54 threshold
            float localDx2, localDy2, localDz2;
            transformVectorToWorld(&localDx2, &localDy2, &localDz2, (float*)(this + 0x2c), &dx, &dy, &dz);
            float secondDot = dx * vec3[1] + dy * vec3[0] + dz * vec3[2]; // note: using original offset vs normalized? unclear
            // clamp again and compare
            float secondClamped;
            if (secondDot <= 0.0f) secondClamped = 0.0f;
            else if (secondDot >= 1.0f) secondClamped = 1.0f;
            else secondClamped = secondDot;
            float secondThreshold = *(float*)(this + 0x54);
            if (secondClamped < secondThreshold || secondClamped == secondThreshold) {
                return true;
            }
        }
    }

    return false;
}