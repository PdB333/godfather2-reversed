// FUNC_NAME: CharacterMovementController::applyInput

// Reconstructed C++ for function at 0x006d7fd0
// This function updates character movement based on input axes and target following logic.
// It adjusts acceleration values (forward and strafe), clamps them, applies to position,
// and computes rotation rate from dot product with movement direction and camera angle.

void __thiscall CharacterMovementController::applyInput(void* this, float inputForward, float inputStrafe)
{
    float* pForwardAccel = (float*)((int)this + 0x25c);
    float* pStrafeAccel = (float*)((int)this + 600);
    int* pFollowTargetNode = (int*)((int)this + 0x260);

    // Global invert multipliers
    static float g_invertForward = *(float*)0x00d5ccf8; // address from DAT_00d5ccf8
    static float g_invertStrafe = *(float*)0x00d5ccf8; // same constant?
    if (*(char*)0x0112a7a5) {
        inputForward *= g_invertForward;
    }
    if (*(char*)0x0112a7a4) {
        inputStrafe *= g_invertStrafe;
    }

    // Retrieve current active target from global game state
    // DAT_012233a0 is pointer to global game state manager
    int* gameState = *(int**)(DAT_012233a0 + 4);
    float activeTargetPosX;
    if (gameState == 0) {
        activeTargetPosX = 0.0f;
    } else {
        activeTargetPosX = (float)((int)gameState - 0x1f30); // offset to some struct
    }

    int activeTarget;
    if (*(int*)((int)activeTargetPosX + 0x31a8) == 0) {
        activeTarget = 0;
    } else {
        activeTarget = *(int*)((int)activeTargetPosX + 0x31a8) - 0x48; // node offset minus header
    }

    int myTarget = 0;
    if (*pFollowTargetNode != 0) {
        myTarget = *pFollowTargetNode - 0x48;
    }

    // Update linked list node if target changed
    if (myTarget != activeTarget) {
        int newTargetFull = activeTarget;
        if (activeTarget == 0) {
            newTargetFull = 0;
        } else {
            newTargetFull = activeTarget + 0x48;
        }

        if (*pFollowTargetNode != newTargetFull) {
            if (*pFollowTargetNode != 0) {
                // Suppose FUN_004daf90 removes from linked list
                FUN_004daf90(pFollowTargetNode);
            }
            *pFollowTargetNode = newTargetFull;
            if (newTargetFull != 0) {
                *(int*)((int)this + 0x264) = *(int*)(newTargetFull + 4); // link next
                *(int**)(newTargetFull + 4) = pFollowTargetNode;
            }
        }
        // Reset accelerations when target changes
        *pForwardAccel = 0.0f;
        *pStrafeAccel = 0.0f;
    }

    // If we have no target or it's invalid (0x48 = null?), skip movement
    if (*pFollowTargetNode != 0 && *pFollowTargetNode != 0x48) {
        // Get our own position and direction
        Vector3 localPos;
        FUN_00424fb0(&localPos, 0); // getPosition(this->m_transform?, ...)

        Vector3 localDir;
        FUN_00425060(&localDir, 0); // getDirection(this->m_transform?, ...)

        Vector3 up = {0,0,1}; // likely up vector

        // Build a transformation matrix or compute basis vectors
        Vector3 forward, strafe, upResult;
        FUN_0056b8a0(localDir, up, &upResult); // cross product -> up?
        // Then normalize these
        FUN_0056afa0(&upResult, &upResult); // normalize up
        Vector3 forwardVec = localDir;
        FUN_0056afa0(&forwardVec, &forwardVec); // normalize forward
        Vector3 strafeVec;
        FUN_0056afa0(&localDir, &localDir); // normalize direction again

        // Check if we can access the target's state
        int targetNode = *pFollowTargetNode - 0x48;
        int stateCheck = FUN_006c8620(&targetNode, 4); // checkStateFlag(targetNode, 4)
        if (stateCheck != 0) {
            // Get target transform and compute distance to target
            int targetTransformA = FUN_00471610(); // might be getTransform()
            int targetTransformB = FUN_00471610(); // same
            float dx = *(float*)(targetTransformB + 0x30) - *(float*)(targetTransformA + 0x30);
            float dy = *(float*)(targetTransformB + 0x34) - *(float*)(targetTransformA + 0x34);
            float dz = *(float*)(targetTransformB + 0x38) - *(float*)(targetTransformA + 0x38);
            float distance = sqrt(dx*dx + dy*dy + dz*dz);
            bool bClose = distance < *(float*)0x00e511d4; // kProximityThreshold

            float forwardAccelRate = *(float*)0x00e448d4;
            float strafeAccelRate = *(float*)0x00d5f544;

            // Check if underwater
            bool bUnderwater = FUN_00410eb0() != 0;
            if (bUnderwater) {
                strafeAccelRate = *(float*)0x00e44828;
                forwardAccelRate = *(float*)0x00e44718;
            }

            // Apply input to acceleration
            float inputStrafeBit = (float)((uint)inputStrafe & *(uint*)0x00e44680); // bitmask?
            if (inputStrafeBit <= 0.0f) {
                // If no strafe input, decelerate using clamp function
                if (0.0f < (float)(*(int*)0x0112a8f0 & *(int*)0x00e44680)) {
                    float clamped = FUN_006c89b0(*pStrafeAccel, 0.0f, *(float*)0x0112a8f0);
                    *pStrafeAccel = clamped;
                }
            } else {
                *pStrafeAccel += strafeAccelRate * inputStrafe;
            }

            float inputForwardBit = (float)((uint)inputForward & *(uint*)0x00e44680);
            if (inputForwardBit <= 0.0f) {
                if (0.0f < (float)(*(int*)0x0112a8ec & *(int*)0x00e44680)) {
                    float clamped = FUN_006c89b0(*pForwardAccel, 0.0f, *(float*)0x0112a8ec);
                    *pForwardAccel = clamped;
                }
            } else {
                *pForwardAccel += forwardAccelRate * inputForward;
            }

            // If close to target, clamp strafe acceleration to zero
            if (bClose) {
                float clamped = FUN_006c89b0(*pStrafeAccel, 0.0f, *(float*)0x00e511d0);
                *pStrafeAccel = clamped;
            }

            // Clamp accelerations to limits
            float maxStrafe = *(float*)0x00e511c4;
            float minStrafe = *(float*)0x00e44564;
            float strafeAccel = *pStrafeAccel;
            float clampedStrafe = strafeAccel;
            float limitHigh = *(float*)0x00e511cc;
            float limitLow = *(float*)0x00e511c8;
            if (strafeAccel > limitHigh && strafeAccel < limitLow) {
                clampedStrafe = strafeAccel;
            } else if (strafeAccel > limitHigh) {
                clampedStrafe = limitHigh;
            } else if (strafeAccel < limitLow) {
                clampedStrafe = limitLow;
            }
            *pStrafeAccel = clampedStrafe;

            float forwardAccel = *pForwardAccel;
            float clampedForward = forwardAccel;
            float minForward = minStrafe - maxStrafe;
            if (forwardAccel > minForward && forwardAccel < maxStrafe) {
                // already in range
            } else if (forwardAccel > maxStrafe) {
                clampedForward = maxStrafe;
            } else {
                clampedForward = minForward;
            }
            *pForwardAccel = clampedForward;

            // Apply acceleration to movement direction
            Vector3 moveDelta;
            moveDelta.x = strafeVec.x * *pStrafeAccel + forwardVec.x * *pForwardAccel;
            moveDelta.y = strafeVec.y * *pStrafeAccel + forwardVec.y * *pForwardAccel;
            moveDelta.z = strafeVec.z * *pStrafeAccel + forwardVec.z * *pForwardAccel;

            // Compute direction from current position to target
            Vector3 toTarget;
            toTarget.x = targetPos.x - localPos.x;
            toTarget.y = targetPos.y - localPos.y;
            toTarget.z = targetPos.z - localPos.z;

            // Normalize to target direction
            Vector3 toTargetNorm = toTarget;
            FUN_0056afa0(&toTargetNorm, &toTargetNorm);

            // Compute dot product between movement direction and to-target direction
            float dotMoveTarget = FUN_004a10f0(&toTargetNorm, &moveDelta);
            float turnRateFactor = *(float*)0x00e44748; // some gain

            // Update angular rate (stored at this+0x22c) based on alignment
            *(float*)((int)this + 0x22c) = dotMoveTarget * turnRateFactor;
            // Also update something at this+0x234 (maybe turn speed)
            FUN_004a10f0(&toTargetNorm, &localPos, &globalUp); // not sure
            *(float*)((int)this + 0x234) = turnRateFactor * *(float*)0x00d5ccf8;

            // If close to target, clamp the turn rate
            if (bClose) {
                float clamped = FUN_006c89b0(*(float*)((int)this + 0x22c), 0.0f, *(float*)0x00e511d0);
                *(float*)((int)this + 0x22c) = clamped;
            }

            // Compute camera influence
            int cameraPtr = FUN_004262f0(0);
            Vector3 cameraPos;
            FUN_00424fb0(&cameraPos, 0); // get camera position
            // Get camera forward vector
            Vector3 camForward;
            Vector3 dummy;
            FUN_0056b420(cameraPtr + 0x40, &cameraPos, &camForward); // transform

            Vector3 camToTarget;
            camToTarget.x = camForward.x - localPos.x;
            camToTarget.y = camForward.y - localPos.y;
            camToTarget.z = camForward.z - localPos.z;

            // Normalize and compute dot with forward vector
            FUN_0056afa0(&camToTarget, &camToTarget);
            float dotCamMove = FUN_004a10f0(&forwardVec, &camToTarget);
            if (dotCamMove > 0.0f) {
                // Subtracting camera alignment reduces turn rate
                *(float*)((int)this + 0x22c) -= dotCamMove * turnRateFactor;
            }
        }
    }
    return;
}