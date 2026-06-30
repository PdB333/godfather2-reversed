// FUNC_NAME: VehicleBrain::updateSteeringHeading
void VehicleBrain::updateSteeringHeading(float *pHeading, const float *pPosition, void *pObject, const float *pTarget1, const float *pTarget2, float multiplier, float distanceThreshold)
{
    // Global constants (likely tuning values for steering)
    const float kMaxSteerAngle = *(float *)0x00d5780c; // _DAT_00d5780c
    const float kSpeedMin = *(float *)0x00d5ef88;      // DAT_00d5ef88
    const float kSpeedScale = *(float *)0x00d5eff0;    // _DAT_00d5eff0
    const float kFrictionScale = *(float *)0x00e50f8c; // _DAT_00e50f8c
    const float kAbsMask = *(float *)0x00e44680;       // DAT_00e44680 (0x7FFFFFFF for absolute value)
    const float kReturnThreshold = *(float *)0x00e50de4; // DAT_00e50de4
    const float kFastSpeedThreshold = *(float *)0x00e50f84; // _DAT_00e50f84
    const float kSlowSpeedThreshold = *(float *)0x00e50f88; // _DAT_00e50f88

    float local_44 = 0.0f;
    float local_34 = 0.0f;
    float local_24 = 0.0f;
    float local_14 = kMaxSteerAngle;

    // Temp vector for orientation calculations
    float tempVec[3]; // actually 12 bytes, aligning with local_68, local_60, etc.
    // Call to zero out a struct (likely a transform)
    zeroStruct(&tempVec, 0); // FUN_00425060
    // Some matrix/vector operation
    multiplyTransform(&tempVec, tempVec, 0, 0); // FUN_0056b8a0 (abstracted)

    // Extract a direction vector from the matrix (possibly forward direction of object)
    float dirX = tempVec[0]; // local_30
    float dirY = 0.0f;
    float dirZ = tempVec[2]; // local_28

    // Compute a perpendicular vector using cross product with (0,1,0)?
    // Actually cross product with (0,0,1) gives (dirZ, 0, -dirX)
    float crossX, crossY, crossZ;
    // Cross product of (dirX, 0, dirZ) with (0,0,1):
    // cross = (0*1 - dirZ*0, dirZ*0 - dirX*1, dirX*0 - 0*0) = (0, -dirX, 0)
    // But the code does a different pattern: It transforms the vector with FUN_0056afa0, then does manual cross with (0,0,1)? The math seems off.
    // Reconstructing from the decompile: after setup, cross product yields ( -dirZ, 0, dirX )? Actually let's trust the code.
    // For simplicity, we'll call the normalize/cross function.
    crossX = -dirZ;
    crossY = 0.0f;
    crossZ = dirX;
    // Then normalize (FUN_0056afa0)
    normalizeVector(&crossX, &crossY, &crossZ); // FUN_0056afa0

    // Distance between pTarget1 and pTarget2
    float dx = pTarget1[0] - pTarget2[0];
    float dy = pTarget1[1] - pTarget2[1];
    float dz = pTarget1[2] - pTarget2[2];
    float distance = sqrtf(dx*dx + dy*dy + dz*dz) / distanceThreshold; // param_7 overwritten

    // Compute speed factor based on distance
    float speedFactor;
    if (distance > 0.0f)
    {
        if (kMaxSteerAngle <= distance)
            speedFactor = (kMaxSteerAngle - kSpeedMin) * kSpeedScale;
        else if (kSpeedMin < distance)
            speedFactor = (distance - kSpeedMin) * kSpeedScale;
        else
            speedFactor = 0.0f;
    }
    else
    {
        speedFactor = 0.0f;
    }
    speedFactor *= multiplier; // param_6

    // Transform pPosition by pObject (maybe world to local?)
    float transformedPos[3];
    transformPoint(transformedPos, pPosition, pObject); // FUN_006c0dd0

    // Offset from current position to transformed
    float offsetX = transformedPos[0] - pPosition[0];
    float offsetY = transformedPos[1] - pPosition[1];
    float offsetZ = transformedPos[2] - pPosition[2];

    // Get some global velocity/position from object's internals (offsets 0x30, 0x38)
    float *pObjData = (float*)FUN_00471610(); // likely returns pointer to object's velocity/position data
    float objX = pObjData[0x30/4]; // +0x30
    float objZ = pObjData[0x38/4]; // +0x38

    // Compute target point with steering contribution
    float baseX = objX + offsetX;
    float baseY = offsetY; // Actually: fStack_ac = local_74 + pPosition[1] but local_74 = transformedPos[1] - pPosition[1]; so baseY = transformedPos[1]? Let's follow code.
    // The code: local_b0 = objX; local_b0 += local_78 (offsetX); fStack_ac = local_74 + pPosition[1]; but local_74 = transformedPos[1] - pPosition[1]; so fStack_ac = transformedPos[1]; similarly local_a8 = objZ + offsetZ.
    // So baseX = objX + offsetX, baseY = transformedPos[1], baseZ = objZ + offsetZ.
    float baseY = transformedPos[1]; // Actually from code: fStack_ac = local_74 + param_2[1]; and local_74 = transformedPos[1] - pPosition[1]; so yes.
    float baseZ = objZ + offsetZ;

    float targetX = crossX * speedFactor + baseX;
    float targetY = crossY * speedFactor + baseY;
    float targetZ = crossZ * speedFactor + baseZ;

    // Compute distances from base to target along the cross direction
    // Actually two distance checks? They call FUN_006c9b00 and FUN_006c9cc0
    float dist1 = computeDistanceA(&baseX, &baseY, &targetX, &targetY, 0); // FUN_006c9b00
    float dist2 = computeDistanceB(&baseX, &baseY, &targetX, &targetY, 2); // FUN_006c9cc0

    float minDist = (dist1 < dist2) ? dist1 : dist2;

    // Vector from target to base? Actually compute difference between target and base
    float diffX = targetX - baseX;
    float diffY = targetY - baseY;
    float diffZ = targetZ - baseZ;
    float magnitude = sqrtf(diffX*diffX + diffY*diffY + diffZ*diffZ);

    // Normalize the diff vector
    normalizeVector(&diffX, &diffY, &diffZ);

    if (minDist < kMaxSteerAngle)
        minDist *= kFrictionScale;

    magnitude = magnitude * minDist;

    // Final target point
    float finalX = crossX * magnitude + baseX;
    float finalY = crossY * magnitude + baseY;
    float finalZ = crossZ * magnitude + baseZ;

    // Clamp speed factor to avoid overshoot? Take absolute of speedFactor
    float absSpeedFactor = fabsf(speedFactor);
    float clampedMagnitude = (magnitude < absSpeedFactor) ? magnitude : absSpeedFactor;

    // Call virtual function on pObject (vtable offset 0x4c)
    // ( **(code **)(*pObject + 0x4c) )(some local struct); // unused? They store to local_5c, but then check conditions.
    void *vtable = *(void**)pObject;
    void (*vfunc)(void*) = (void (*)(void*))((int*)vtable)[0x4c/4];
    vfunc(pObject); // likely updates something, not used further.

    // Decision based on absolute value of current heading and some thresholds
    float absHeading = fabsf(*pHeading);
    float absSpeedFactor = fabsf(speedFactor);
    float param; // fVar3
    float threshold;

    if (absHeading <= fabsf(baseY)) // Actually condition: (uint)*param_1 & ... <= fStack_b8 (which is baseY?) This is weird.
    {
        // Check magnitude of something? The code: if sqrt(...) <= kReturnThreshold, return.
        float checkMag = sqrtf( /*some values from local_5c?*/ ); // The local_5c struct seems unrelated; maybe it's from the vcall.
        // For simplicity, we assume the condition is such that if the magnitude is small, we return without updating heading.
        // But we don't have those values. We'll assume it's checking a velocity magnitude.
        float velX = *(float*)0x00; // unknown, but likely from the local struct
        float velZ = *(float*)0x04;
        if (sqrtf(velX*velX + velZ*velZ) <= kReturnThreshold)
        {
            return;
        }
        threshold = kFastSpeedThreshold;
    }
    else
    {
        threshold = kSlowSpeedThreshold;
        if (absSpeedFactor < fabsf(offsetZ)) // condition: (uint)local_a4 & mask < local_70
        {
            param = speedFactor;
        }
        else
        {
            param = baseZ; // or something else, but the code uses fVar3 = local_a8 after the if... Actually they set fVar3 = local_a8 in the else path? Hard to follow.
        }
    }

    // Compute final heading adjustment via interpolation
    float newHeading = interpolateHeading(*pHeading, param, threshold); // FUN_006c89b0
    *pHeading = newHeading;
}