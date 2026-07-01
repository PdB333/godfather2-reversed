// FUNC_NAME: PlayerAimController::updateAimTurn
void __fastcall PlayerAimController::updateAimTurn(int thisPtr)
{
    bool bSetTurnFlag = false;
    char cIsPaused = FUN_00481620(); // isGamePaused?
    if (cIsPaused == '\0') {
        // Not paused: get camera direction and compute aim vector
        float cameraDir[3]; // local_70, fStack_6c, fStack_68
        char cGotDir = FUN_00472510(&cameraDir); // getCameraDirection
        if (cGotDir != '\0') {
            float dirLenSq = cameraDir[1]*cameraDir[1] + cameraDir[2]*cameraDir[2] + cameraDir[0]*cameraDir[0];
            float invLen = 0.0f;
            if (dirLenSq != 0.0f) {
                invLen = _DAT_00d5780c / sqrtf(dirLenSq); // 1.0f / length
            }
            // Normalized camera direction
            float aimDirX = invLen * cameraDir[0];
            float aimDirY = invLen * cameraDir[1];
            float aimDirZ = invLen * cameraDir[2];
            // Also store a scaled version? (fStack_54 is used later)
            float aimDirScaled = cameraDir[2] * invLen; // fStack_54? Actually fStack_54 is set to 0 then overwritten
            // Actually fStack_54 was set to 0, then later used as fStack_54 * fStack_64 - fStack_54 * fStack_64 = 0
            // So it's likely a dummy.

            // Get player transform (position/rotation)
            int playerTransform = FUN_00471610(); // getPlayerTransform
            float playerForward[3]; // fStack_6c, fStack_68, local_70
            playerForward[0] = *(float *)(playerTransform + 0x20); // x
            playerForward[1] = *(float *)(playerTransform + 0x24); // y
            playerForward[2] = *(float *)(playerTransform + 0x28); // z
            float fwdLenSq = playerForward[1]*playerForward[1] + playerForward[2]*playerForward[2] + playerForward[0]*playerForward[0];
            float invFwdLen = 0.0f;
            if (fwdLenSq != 0.0f) {
                invFwdLen = _DAT_00d5780c / sqrtf(fwdLenSq);
            }
            // Normalized player forward
            float fwdX = invFwdLen * playerForward[0];
            float fwdY = invFwdLen * playerForward[1];
            float fwdZ = invFwdLen * playerForward[2];

            // Dot product between aim direction and player forward
            float dot = fwdX*aimDirX + fwdY*aimDirY + fwdZ*aimDirZ;
            float clampedDot = _DAT_00d5780c; // 1.0f
            if (dot <= _DAT_00d5780c) {
                clampedDot = dot;
                if (dot < DAT_00d5ccf8) { // -1.0f?
                    clampedDot = DAT_00d5ccf8;
                }
            }
            // Cross product to get turn axis (up vector)
            float crossX = aimDirX * fwdY - aimDirY * fwdX; // fStack_5c? Actually computed as fStack_58 * fStack_6c - fStack_5c * fStack_68
            // The decompiled code uses local_60, fStack_5c, fStack_58 as intermediate cross product components.
            // Let's reconstruct properly:
            float crossY = aimDirY * fwdZ - aimDirZ * fwdY; // fStack_5c? Actually fVar11 - fStack_58 * local_70
            float crossZ = aimDirZ * fwdX - aimDirX * fwdZ; // fStack_58? Actually fVar12 - fVar9
            // The code then computes angle from dot and cross (atan2)
            double angle = (double)clampedDot;
            if (crossY >= 0.0f) { // using crossY as sign? Actually fStack_5c is crossY
                FUN_00b9b988(); // atan2? Actually it's a function that returns angle from dot and cross? Might be acos.
                float angleRad = (float)angle;
            } else {
                FUN_00b9b988();
                float angleRad = DAT_00e44564 - (float)angle; // 2*PI - angle
            }
            // Check if angle exceeds threshold
            if (DAT_00e446f4 <= (float)((uint)(angleRad * DAT_00e44748) & DAT_00e44680)) {
                // Set turn direction
                if (angleRad * DAT_00e44748 >= 0.0f) {
                    *(int *)(thisPtr + 0x118) = 2; // turn right
                } else {
                    *(int *)(thisPtr + 0x118) = 1; // turn left
                }
                goto LAB_007c7ee8;
            }
        }
    } else {
        // Game is paused? Actually the else branch is for when cIsPaused != 0
        // This branch handles aiming while paused? Or maybe it's the opposite.
        // Let's re-read: if (cIsPaused == '\0') { ... } else { ... }
        // So else is when not paused? Wait, the first if checks cIsPaused == '\0', so else is when paused.
        // But the code in else seems to handle aiming with random variation.
        // Actually the decompiled code has: if (cIsPaused == '\0') { ... } else { ... } but the else branch is large.
        // Let's trust the decompiled structure.

        // Get some vector from a table indexed by something at +0x58
        int entityPtr = *(int *)(thisPtr + 0x58);
        FUN_00425060(&aimDirX, *(int *)(&DAT_00002494 + entityPtr)); // get some direction from entity
        float fVar8 = aimDirY * DAT_00e44748; // aimDirY is local_7c? Actually local_7c is aimDirY from earlier? No, local_7c is from the vector.
        // The code uses local_80, local_7c, local_78 as the vector from FUN_00425060.
        // So we need to rename accordingly.

        // Get player transform again
        int playerTransform = FUN_00471610();
        float playerMatrix[16]; // local_50 array of 16 floats? Actually local_50 is undefined4[8] so 8 ints = 32 bytes = 8 floats? No, 8 undefined4 = 32 bytes, but then used as 16 floats? Actually the loop copies 0x10 (16) ints? Wait: for (iVar4 = 0x10; iVar4 != 0; iVar4--) { *puVar5 = *puVar3; puVar3++; puVar5++; } That copies 16 ints = 64 bytes = 16 floats. So local_50 is a 16-float array (matrix). Then local_30 is the 13th float? Actually local_30 is at offset 0x30 from local_50? local_50 is at stack offset -0x50? The decompiled shows local_50 [8] and then local_30, so local_30 is after local_50, so it's the 9th element? Actually local_50 is 8 undefined4 = 32 bytes, then local_30 is a float at offset 0x20 from local_50? No, local_30 is declared after local_50, so it's at a higher address. The stack layout: local_80, local_7c, local_78, local_70, fStack_6c, fStack_68, fStack_64, local_60, fStack_5c, fStack_58, fStack_54, local_50[8], local_30. So local_30 is at offset 0x30 from local_50? Actually local_50 is at some offset, local_30 is after it. The loop copies 16 floats into local_50, so local_30 is the 13th float? No, local_50 is 8 undefined4 = 32 bytes = 8 floats, but the loop copies 16 ints = 64 bytes, so it overwrites beyond local_50 into local_30 and beyond. So local_30 is part of the copied matrix. So the matrix is 16 floats, starting at local_50 and ending at local_30+? Actually local_30 is at offset 0x30 from local_50? Let's not overcomplicate.

        // After copying, they do:
        double dVar10 = (double)local_30; // local_30 is a float from the matrix (probably the 13th element, which is the translation z? Or rotation?)
        FUN_00b9a9fa(); // some math function (maybe sin/cos)
        int entityPtr2 = *(int *)(thisPtr + 0x58);
        float fVar9 = (float)dVar10 * DAT_00e44748;
        // Check flags on entity
        if ((((*(uint *)(entityPtr2 + 0x8e0) >> 9 & 1) == 0) &&
             ((*(uint *)(entityPtr2 + 0x249c) >> 0x17 & 1) == 0)) &&
            ((*(uint *)(entityPtr2 + 0x8e0) >> 9 & 1) == 0) &&
            ((*(byte *)(entityPtr2 + 0x249f) & 1) == 0)) {
            // Random chance
            float random1 = (float)FUN_0079eb40(0, 1); // random float 0-1
            if ((float)*(float *)(DAT_01223464 + 0x1694) < random1) {
                float random2 = (float)FUN_0079eb90(0, 0); // another random
                float angleDiff = (random2 * DAT_00e44748 + fVar8) - fVar9;
                float normalizedAngle = (float)FUN_006d6350(angleDiff); // normalize angle
                if ((DAT_00d5842c < random1) &&
                    ((float)((uint)normalizedAngle & DAT_00e44680) < DAT_00e446f4)) {
                    // Increment counter
                    *(int *)(thisPtr + 0xd0) = *(int *)(thisPtr + 0xd0) + 1;
                    goto LAB_007c7f2d;
                }
                // Set turn direction based on normalized angle
                if (normalizedAngle >= 0.0f) {
                    *(int *)(thisPtr + 0x118) = 2;
                } else {
                    *(int *)(thisPtr + 0x118) = 1;
                }
                bSetTurnFlag = true;
            }
        }
        // Reset counter
        *(int *)(thisPtr + 0xd0) = 0;
        if (bSetTurnFlag) {
LAB_007c7ee8:
            *(int *)(thisPtr + 0x124) = 0; // reset retry count
            char cIsInVehicle = FUN_00481660(); // isPlayerInVehicle?
            if ((cIsInVehicle != '\0') && ((*(byte *)(thisPtr + 0x12a) & 1) != 0)) {
                FUN_00472130(1); // set some input mode
                *(uint *)(thisPtr + 0x128) = *(uint *)(thisPtr + 0x128) & 0xfffeffff; // clear bit 16
            }
            *(uint *)(thisPtr + 0x128) = *(uint *)(thisPtr + 0x128) | 4; // set bit 2
            goto LAB_007c7f81;
        }
    }
LAB_007c7f2d:
    char cIsPaused2 = FUN_00481620();
    if (cIsPaused2 == '\0') {
        char cIsAiming = FUN_00481640(); // isPlayerAiming?
        if (cIsAiming == '\0') goto LAB_007c7f81;
        if ((*(uint *)(thisPtr + 0x124) < 3) && (cIsAiming = FUN_00472820(), cIsAiming != '\0')) {
            // Increment retry count
            *(int *)(thisPtr + 0x124) = *(int *)(thisPtr + 0x124) + 1;
            goto LAB_007c7f81;
        }
    } else {
        char cIsInVehicle2 = FUN_00481660();
        if (((cIsInVehicle2 != '\0') && ((*(uint *)(thisPtr + 0x128) >> 2 & 1) == 0)) &&
            ((*(uint *)(thisPtr + 0x128) >> 0x10 & 1) == 0)) {
            FUN_00472130(0); // set input mode
            *(uint *)(thisPtr + 0x128) = *(uint *)(thisPtr + 0x128) | 0x10000; // set bit 16
        }
    }
    *(uint *)(thisPtr + 0x128) = *(uint *)(thisPtr + 0x128) & 0xfffffffb; // clear bit 2
LAB_007c7f81:
    if (*(int *)(thisPtr + 0x118) != 1) {
        // Not turning left
        FUN_007f63e0(0x1e); // play sound 0x1e
        FUN_007f6420(0x1d); // stop sound 0x1d
        return;
    }
    // Turning left
    FUN_007f63e0(0x1d); // play sound 0x1d
    FUN_007f6420(0x1e); // stop sound 0x1e
    return;
}