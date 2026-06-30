// FUNC_NAME: ChaseCamera::updateChaseMovement

void __thiscall ChaseCamera::updateChaseMovement(void* this, bool* pOutReached) {
    float fDotResult;
    float fDist;
    float fDistClamped;
    float fCurrentSpeed;
    float fAccelFactor;

    // Vector offsets relative to this:
    // +0x214 : current position (Vec3)
    // +0x220 : target position (Vec3)
    // +0x24c : desired position (Vec3) – may be updated based on direction alignment
    // +0x298 : current speed (float)
    // +0x168 : acceleration multiplier (float)

    // Check dot product between (target - current) and (desired - current)
    // If target is not aligned with desired relative to current, switch desired to target.
    fDotResult = (*(float*)(this + 0x224) - *(float*)(this + 0x218)) *
                 (*(float*)(this + 0x250) - *(float*)(this + 0x218)) +
                 (*(float*)(this + 0x220) - *(float*)(this + 0x214)) *
                 (*(float*)(this + 0x24c) - *(float*)(this + 0x214)) +
                 (*(float*)(this + 0x228) - *(float*)(this + 0x21c)) *
                 (*(float*)(this + 0x254) - *(float*)(this + 0x21c));

    // Global epsilon for dot product threshold
    if (fDotResult <= CHASE_DOT_EPSILON) {
        // Copy target position into temporary
        memcpy(&tempVec, (void*)(this + 0x220), 8);
        *(undefined4*)((char*)&tempVec + 8) = *(undefined4*)(this + 0x228);
    } else {
        // Keep current desired position
        memcpy(&tempVec, (void*)(this + 0x24c), 8);
        *(undefined4*)((char*)&tempVec + 8) = *(undefined4*)(this + 0x254);
    }

    // Write the chosen position back to desired position
    memcpy((void*)(this + 0x24c), &tempVec, 8);
    *(undefined4*)(this + 0x254) = *(undefined4*)((char*)&tempVec + 8);

    // Compute distance from current position to desired position, also obtain a timer value
    float fTimer;
    float10 dDist = FUN_006c9b00(&tempVec, (void*)(this + 0x214), &fTimer, 0);
    fDist = (float)dDist;
    if (dDist < (float10)0.0f) {
        fDist = 0.0f;
    }

    *pOutReached = false;
    if ((fDist < CHASE_DIST_THRESHOLD) && (CHASE_TIMER_THRESHOLD < fTimer)) {
        *pOutReached = true;
    }

    fCurrentSpeed = *(float*)(this + 0x298);
    if (fCurrentSpeed <= fDist) {
        // Need to accelerate/decelerate toward the distance
        if (fCurrentSpeed > CHASE_FAST_SPEED_THRESHOLD) {
            fAccelFactor = CHASE_ACCEL_FACTOR_FAST;
        } else {
            fAccelFactor = CHASE_ACCEL_FACTOR;
        }
        // Apply acceleration smoothing: uses speed, distance and a factor from this+0x168
        fCurrentSpeed = (float)FUN_006c89b0(fCurrentSpeed, fDist, *(float*)(this + 0x168) * fAccelFactor);
    } else {
        // If current speed is greater than distance, snap to distance
        fCurrentSpeed = fDist;
    }

    *(float*)(this + 0x298) = fCurrentSpeed;
}