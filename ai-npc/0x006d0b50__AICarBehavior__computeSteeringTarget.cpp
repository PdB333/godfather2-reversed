// FUNC_NAME: AICarBehavior::computeSteeringTarget
// Address: 0x006d0b50
// Role: Computes a smoothed steering target position relative to current vehicle state, with time-dependent blending.
// Uses two vtable methods at offsets 0x10 (getCurrentPosition) and 0x14 (getDesiredPosition).

void __thiscall AICarBehavior::computeSteeringTarget(float* outTarget, const float* inTarget, bool isReversing)
{
    // Vtable methods return float[3] pointers (x,y,z)
    float* currentPos = (*(float*(__thiscall**)(AICarBehavior*))(*(int*)this + 0x10))(this);
    float* desiredPos = (*(float*(__thiscall**)(AICarBehavior*))(*(int*)this + 0x14))(this);

    float heightOffset = DAT_00e51128;               // +0x? Y-offset (e.g., ground level)
    float dz = desiredPos[2] - currentPos[2];
    float dx = DAT_00e44564 - (desiredPos[0] - currentPos[0]); // DAT_00e44564 likely 0.0f

    float distSq = dx * dx + dz * dz;
    float invDist;
    if (distSq <= DAT_00d5f2b4) {                    // Distance threshold (probably small)
        invDist = 0.0f;
    } else {
        invDist = 1.0f / sqrtf(distSq);              // _DAT_00d5780c is 1.0f
    }

    float dirScale = DAT_00e51124;                   // Scaling factor for direction
    float steerX = dirScale * invDist * dx;
    float steerZ = dirScale * invDist * dz;

    // Timer variable for blending
    static char lastDirection;                       // DAT_0112a860
    if (isReversing != lastDirection) {
        DAT_00e510d0 = DAT_00e510cc - DAT_00e510d0;  // Invert timer
    }

    float blendSpeed = (isReversing) ? DAT_00d5f00c : DAT_00e446a0; // DAT_00e446a0 likely normal blend, DAT_00d5f00c reverse blend

    double timerRatio = (double)(DAT_00e510d0 / DAT_00e510cc); // Normalized timer (0..1)
    double blendFactorRaw = (timerRatio * (double)DAT_00d5eee4 - 1.0) * (double)blendSpeed;
    (*(void(__thiscall**)(void))(0x00b99fcb))();      // Unknown smoothing/noise function

    float blendFactor = ((float)blendFactorRaw + 1.0f) * DAT_00d5c458; // Final blend factor

    float finalSteerX, finalSteerZ;
    if (!isReversing) {
        blendFactor = 1.0f - blendFactor;
        // For forward: steer components approach zero
        finalSteerX = (0.0f - steerX) * blendFactor + steerX;   // = steerX * (1-blendFactor)
        finalSteerZ = (0.0f - steerZ) * blendFactor + steerZ;   // = steerZ * (1-blendFactor)
    } else {
        // For reverse: steer components build from zero
        finalSteerX = (steerX - 0.0f) * blendFactor + 0.0f;     // = steerX * blendFactor
        finalSteerZ = (steerZ - 0.0f) * blendFactor + 0.0f;     // = steerZ * blendFactor
    }

    // Re-acquire current position (now used for distance-to-target interpolation)
    currentPos = (*(float*(__thiscall**)(AICarBehavior*))(*(int*)this + 0x10))(this);

    // Compute normalized distance between input target and current position
    float diffX = inTarget[0] - currentPos[0];
    float diffY = inTarget[1] - currentPos[1];
    float diffZ = inTarget[2] - currentPos[2];
    float dist = sqrtf(diffX * diffX + diffY * diffY + diffZ * diffZ);

    float distFactor = (dist - DAT_00e51170) / (DAT_00e51178 - DAT_00e51170); // Normalize within [minDist, maxDist]
    if (distFactor <= 0.0f)
        distFactor = 0.0f;
    else if (distFactor >= 1.0f)
        distFactor = 1.0f;

    // Lerp between original target and offset target
    const float* srcTarget = inTarget;
    float modifiedTarget[4] = {
        srcTarget[0] + steerX,
        srcTarget[1] + heightOffset,       // Originally was srcTarget[1] + fVar9 (since fVar16=0)
        srcTarget[2] + steerZ,
        srcTarget[3]                       // Unchanged component (often 0 or 1)
    };

    outTarget[0] = (modifiedTarget[0] - srcTarget[0]) * distFactor + srcTarget[0];
    outTarget[1] = (modifiedTarget[1] - srcTarget[1]) * distFactor + srcTarget[1];
    outTarget[2] = (modifiedTarget[2] - srcTarget[2]) * distFactor + srcTarget[2];
    outTarget[3] = (modifiedTarget[3] - srcTarget[3]) * distFactor + srcTarget[3];

    lastDirection = (char)isReversing;               // Store for next call
    return;
}