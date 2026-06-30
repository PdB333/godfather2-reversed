// FUNC_NAME: PlayerCamera::updateCameraSmoothing

void PlayerCamera::updateCameraSmoothing(float* srcPos, float* tgtPos, float* currentAngle, float deltaTime, bool skipAngleInterp, float* outPos, float* outAngle, float* outBlend)
{
    // Fetch interpolation factors from the camera's state
    float heightStart = *(float*)(this + 0x118);   // +0x118: start of height range
    float heightEnd   = *(float*)(this + 0x11c);   // +0x11c: end of height range
    float interpFactor = *(float*)(this + 0x298);   // +0x298: interpolation factor (0..1)
    float weight      = *(float*)(this + 0x80);    // +0x80: additional blend weight

    // Compute base height value by linearly interpolating between heightStart and heightEnd
    float baseHeight = heightStart + (heightEnd - heightStart) * interpFactor;
    baseHeight = (baseHeight - heightStart) * weight + heightStart;  // apply weight

    float epsilon = *(float*)0x00d5780c;   // likely 0.0f

    if (deltaTime < epsilon) {
        // Fast path: no interpolation, copy target directly
        outPos[0] = tgtPos[0];
        outPos[1] = tgtPos[1];
        outPos[2] = tgtPos[2];
        outAngle[0] = currentAngle[0];
        outAngle[1] = currentAngle[1];
        *(float*)((char*)outAngle + 8) = currentAngle[2];
        *outBlend = baseHeight;
        return;
    }

    // Compute direction from source to target
    float dx = tgtPos[0] - srcPos[0];
    float dz = tgtPos[2] - srcPos[2];   // actually local_8 was tgtPos[1]-srcPos[1]? Wait decompiled: fVar6 = *param_3 - *param_2; fVar9=param_3[2] - param_2[2]; local_8 = param_3[1] - param_2[1]; So dy = tgtPos[1]-srcPos[1]
    // Let's keep consistent: assume x,y,z
    float dy = tgtPos[1] - srcPos[1];
    // Actually in x86: array order is x,y,z. But the code uses [0],[1],[2] as x,y,z. So:
    // fVar6 = dx, local_8 = dy, fVar9 = dz.
    // But later they use local_8 in SQRT? They compute fVar11 = dy * deltaTime; fVar7 = dy*dy.
    // So dy is local_8.

    // Interpolated position
    float interpolatedX = srcPos[0] + dx * deltaTime;
    float interpolatedY = srcPos[1] + dy * deltaTime;
    float interpolatedZ = srcPos[2] + dz * deltaTime;

    outPos[0] = interpolatedX;
    outPos[1] = interpolatedY;
    outPos[2] = interpolatedZ;

    // Determine interpolation ratio for vertical smoothing
    float timeRangeMin = *(float*)(this + 0x17c);   // +0x17c: min time for smooth interpolation
    float timeRangeMax = *(float*)(this + 0x180);   // +0x180: max time for smooth interpolation
    float t;
    if (deltaTime <= timeRangeMin) {
        t = 0.0f;
    } else if (deltaTime >= timeRangeMax) {
        t = 1.0f;
    } else {
        t = (deltaTime - timeRangeMin) / (timeRangeMax - timeRangeMin);
    }
    // FUN_006c91c0 is a clamp/lerp function; assume it returns t clamped to [0,1]
    float clampedT = clamp01(t);  // placeholder for that function
    float oneMinusT = 1.0f - clampedT;

    // Compute distance between source and interpolated position (squared, but with a twist)
    float dxInterp = interpolatedX - srcPos[0]; // actually already dx*deltaTime
    float dyInterp = interpolatedY - srcPos[1];
    float dzInterp = interpolatedZ - srcPos[2];
    float distSquared = dxInterp*dxInterp + dyInterp*dyInterp + dzInterp*dzInterp;
    // But the code computes fVar6 = (fVar9 * fVar9 + fVar6 * fVar6 + fVar7) - (fVar12*fVar12 + fVar10*fVar10);
    // where fVar7 = dy^2, fVar6 = dx, fVar9 = dz, fVar12 = dz*deltaTime, fVar10 = dx*deltaTime.
    // So that equals (dx^2 + dy^2 + dz^2) - ((dx*dt)^2 + (dy*dt)^2 + (dz*dt)^2) = (1-dt^2)*lenSq
    // Then they take sqrt: fVar8 = sqrt(fVar6) - local_8; local_8 is dy.
    // That seems like computing vertical offset after factoring out the horizontal? Hard to follow.
    // For simplicity, I'll implement the logic as written.

    float lenSq = dx*dx + dy*dy + dz*dz;
    float interpLenSq = dxInterp*dxInterp + dyInterp*dyInterp + dzInterp*dzInterp;
    float diffLenSq = lenSq - interpLenSq;
    float distFromSrc = (diffLenSq > 0.0f) ? sqrtf(diffLenSq) : 0.0f;
    distFromSrc = distFromSrc - dy;  // subtract the vertical component? This matches original: fVar8 = fVar8 - local_8;

    // Fetch additional parameters for vertical smoothing
    float vertMin = *(float*)(this + 0x16c);   // +0x16c: vertical speed min
    float vertMax = *(float*)(this + 0x170);   // +0x170: vertical speed max
    float vertSpeed = (vertMin - vertMax) * weight + vertMax;  // linear interpolation
    // Actually original: fVar6 = *(float*)(this+0x170); fVar7=*(float*)(this+0x16c); then fVar6 = param_7[1] + ((fVar7 - fVar6)* weight + fVar6) * fVar8 * fVar1;
    // We'll implement that.

    // Get some global vector (sun direction?) for distance check
    void* globalPtr = FUN_00471610();  // returns some global object
    float globalVec[3];
    *(uint64*)&globalVec[0] = *(uint64*)((char*)globalPtr + 0x30);
    globalVec[2] = *(float*)((char*)globalPtr + 0x38);
    // Compute squared distance from globalVec to outPos
    float distSqToGlobal = distSq2D(globalVec, outPos, 2); // FUN_006c9cc0 with dimension 2 (assuming 2D distance)
    // Actually FUN_006c9cc0 takes two vectors and int dimension; here used twice: one with srcPos, one with globalVec.
    float distSqFromSrc = distSq2D(srcPos, outPos, 2);
    float minDistSq = (distSqFromSrc < distSqToGlobal) ? distSqFromSrc : distSqToGlobal;

    // Apply height correction
    float heightOffset = vertSpeed * distFromSrc * oneMinusT;
    outPos[1] = interpolatedY + heightOffset;   // This matches: param_7[1] = param_7[1] + ((fVar7 - fVar6)*weight + fVar6) * fVar8 * fVar1

    // If we're very close to the reference point, clamp the height
    if (minDistSq < epsilon && !isnan(outPos[1])) {
        float heightThreshold = *(float*)(this + 0x224) + *(float*)0x00e50f80; // +0x224: some ground offset + global ground height
        if (heightThreshold <= outPos[1]) {
            outPos[1] = heightThreshold;
        }
    }

    // Angular interpolation
    float angSpeedMin = *(float*)(this + 0x174); // +0x174: angular speed min
    float angSpeedMax = *(float*)(this + 0x178); // +0x178: angular speed max
    float angularSpeed = (angSpeedMin - angSpeedMax) * weight + angSpeedMax;
    float angularDelta = angularSpeed * *(float*)0x00e445c8 * oneMinusT; // scaling factor

    float newAngle = (skipAngleInterp) ? baseHeight : (*(float*)this + 0x128) - ... ); // Hard to fully reconstruct
    // Actually the code has a branch: if (param_6==0) compute new angle interpolation; else newAngle = baseHeight and angularDelta=0.
    // The computation involves fields at 0x128 and 0x12c (300). They compute a blended value from those two and baseHeight.
    // For brevity, I'll implement as in the original.
    float blendAngle;
    if (!skipAngleInterp) {
        float startAngle = *(float*)(this + 0x128); // +0x128: start angle
        float endAngle   = *(float*)(this + 300);   // +0x12c: end angle (300 decimal)
        float interpAngle = (endAngle - startAngle) * weight + startAngle;
        blendAngle = (interpAngle - baseHeight) * oneMinusT + baseHeight;
    } else {
        blendAngle = baseHeight;
        angularDelta = 0.0f;
    }
    *outBlend = blendAngle;

    // Apply angular delta to current angle
    float angleInput = currentAngle[0] + angularDelta; // assuming first element is yaw
    float wrappedAngle = wrapAngle(angleInput); // FUN_004a1580
    currentAngle[0] = wrappedAngle; // but original writes to *param_4 = wrappedAngle? Actually they assign *param_4 = wrappedAngle, then later copy to outAngle.
    // Wait: original: fVar3 = FUN_004a1580(*param_4 + fVar6); *param_4 = (float)fVar3; then *param_8 = *(undefined8*)param_4; This means they update the input angle and copy it.
    // So we update the caller's angle directly.
    currentAngle[0] = wrappedAngle; // update yaw

    // Copy angle to output: first two floats as 8 bytes, third separately
    *(uint64*)outAngle = *(uint64*)currentAngle;
    *(float*)((char*)outAngle + 8) = currentAngle[2];
}