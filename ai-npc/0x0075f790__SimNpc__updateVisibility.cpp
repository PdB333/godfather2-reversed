// FUNC_NAME: SimNpc::updateVisibility
void __thiscall SimNpc::updateVisibility(int thisPtr, int param_2, float deltaTime)
{
    char visibilityFlag; // local_d (output from detectVisibility)
    float squaredDist;
    int playerPtr;
    float dx, dy, dz;
    char detectionData[12]; // local_c (detection result buffer)

    // Check bit 14 of flags at +0xa8; if set, skip visibility update
    if (((*(uint *)(thisPtr + 0xa8) >> 0xe) & 1) == 0) {
        visibilityFlag = 0;
        // Call external function to compute visibility (fills detectionData and outputs visibilityFlag)
        FUN_0075f4a0(deltaTime, detectionData, &visibilityFlag);

        // Get the local player's position from a singleton (e.g., CameraManager or PlayerManager)
        playerPtr = FUN_00471610();
        dx = *(float *)(thisPtr + 0x60) - *(float *)(playerPtr + 0x30);
        dy = *(float *)(thisPtr + 0x64) - *(float *)(playerPtr + 0x34);
        dz = *(float *)(thisPtr + 0x68) - *(float *)(playerPtr + 0x38);
        squaredDist = dz*dz + dy*dy + dx*dx;

        // Update minimum squared distance to player
        if (squaredDist < *(float *)(thisPtr + 0xf4)) {
            *(float *)(thisPtr + 0xf4) = squaredDist;
        }

        // Increment timer if the entity is currently visible (visibilityFlag != 0)
        if (visibilityFlag == 0) {
            // Not visible: reset timer to 0
            *(float *)(thisPtr + 0x108) = 0.0f;
            // Note: param_2 is ignored when not visible? Actually original code sets fVar3 = 0.0 and then uses it only for the timer else branch
            // But the assignment to fVar3 happens only in the else branch; here fVar3 = 0.0
        } else {
            // Visible: increase timer by delta, and record the last seen identifier (param_2)
            *(float *)(thisPtr + 0x108) = *(float *)(thisPtr + 0x108) + deltaTime;
            *(int *)(thisPtr + 0x10c) = param_2;
        }

        // Determine if the entity was not seen recently: compare current param_2 to last seen id
        // param_2 might be a frame counter or sequence number; if the difference exceeds a global threshold,
        // set the "not recently visible" flag (bit 5 = 0x20)
        if ((param_2 == 0) || (DAT_00e51b14 < (uint)(param_2 - *(int *)(thisPtr + 0x10c)))) {
            *(uint *)(thisPtr + 0xa8) = *(uint *)(thisPtr + 0xa8) | 0x20;
        } else {
            *(uint *)(thisPtr + 0xa8) = *(uint *)(thisPtr + 0xa8) & 0xffffffdf;
        }

        // If the entity has not been flagged as "fully visible" yet (byte at +0xf8 == 0) and the visibility timer
        // is still below a threshold, attempt to trigger a detail level change or render update
        if ((*(char *)(thisPtr + 0xf8) == 0) && (*(float *)(thisPtr + 0x108) <= _DAT_00d651e8)) {
            if (FUN_007448b0() != 0) { // something like isStillRendered() or isActive()
                // If the entity is still within rendering range, trigger a high‑detail update and clear bit 13 (0x2000)
                FUN_0075e480(deltaTime, detectionData, (*(uint *)(thisPtr + 0xa8) >> 0xd) & 0xffffff01);
                *(uint *)(thisPtr + 0xa8) = *(uint *)(thisPtr + 0xa8) & 0xffffdfff;
                return;
            }
            // Otherwise, trigger a low‑detail or hidden update
            FUN_0075ded0(deltaTime, detectionData);
            return;
        }
        // Mark the entity as having been through this visibility update (flag at +0xf8)
        *(char *)(thisPtr + 0xf8) = 1;
    }
    return;
}