// FUNC_NAME: CharacterController::updateMovement
// Address: 0x004ff4d0
// This function updates character movement each frame. It computes steering forces, applies damping,
// and integrates forward/backward impulses. Handles sprint flags, collision impulses, and a short timer.

void __thiscall CharacterController::updateMovement(int thisPtr, float deltaTime)
{
    float steeringForce;
    float forwardForce;
    float impulseScale;
    float timeAccum;
    float forceX, forceY, forceZ;
    // local_60: temp force vector components
    float tempForce[4]; // Actually 4 floats but only 3 used? local_60, local_5c, local_58
    // local_50: 48-byte buffer for matrix or misc

    // Get character entity pointer (offset +0x04)
    int entityPtr = *(int *)(thisPtr + 4);
    // Fetch field at +0x8c from entity (likely current speed or target speed)
    float targetSpeed = *(float *)(entityPtr + 0x8c);

    // Compute index into interpolation data: base = entity+0x10, then offset by short at this+0x0e * 0x24 + 0x30
    int shortIndex = *(short *)(thisPtr + 0x0e);
    int interpBase = (*(int *)(entityPtr + 0x10)) + 0x30 + shortIndex * 0x24;
    // interpBase points to a structure with interpolation values

    // Steering force = (targetSpeed - currentSpeed) * dampingFactor
    float steeringDelta = targetSpeed - *(float *)(interpBase + 0x18);
    steeringForce = steeringDelta * *(float *)(interpBase + 0x14);
    if (steeringForce > 0.0f) {
        if (steeringForce > DAT_00e2b1a4) // clamp to global max
            steeringForce = DAT_00e2b1a4;
    } else {
        steeringForce = 0.0f;
    }

    // Forward/backward force similar
    float forwardDelta = targetSpeed - *(float *)(interpBase + 0x20);
    forwardForce = forwardDelta * *(float *)(interpBase + 0x1c);
    if (forwardForce > 0.0f) {
        if (forwardForce > DAT_00e2b1a4)
            forwardForce = DAT_00e2b1a4;
    } else {
        forwardForce = 0.0f;
    }

    // If product is <= 0 (i.e., no net directional force), maybe stop
    if (forwardForce * steeringForce <= 0.0f) {
        if (*(int *)(thisPtr + 0x28) != 0) { // some active state
            FUN_004ff430(); // stop movement
            return;
        }
    } else {
        if ((*(int *)(thisPtr + 0x28) != 0) || // already active
            (FUN_004ff0f0(), *(int *)(thisPtr + 0x28) != 0)) { // try to activate
            tempForce[0] = 0.0f; // zero the force vector
            // piVar4 is global game state pointer at FS_OFFSET + 0x2c
            int *gameStatePtr = *(int **)(unaff_FS_OFFSET + 0x2c);
            // Check and decrement short timer (offset this+0x10)
            if (*(float *)(thisPtr + 0x40) > 0.0f) {
                float newTimer = *(float *)(thisPtr + 0x40) - deltaTime;
                *(float *)(thisPtr + 0x40) = newTimer;
                if (newTimer <= 0.0f) {
                    // Set a bit on a per-entity flag (offset +8 from gameState)
                    uint *flagPtr = (uint *)(*(int *)(*gameStatePtr + 8) + *(int *)(thisPtr + 0x10));
                    *flagPtr |= 1;
                }
            }

            // Check entity flags for speed mode (bit 0x40 and 0x4000 potentially walking/running)
            uint entityFlags = *(uint *)(*(int *)(entityPtr + 0x10) + 0x14);
            if (((entityFlags & 0x40) == 0) && ((entityFlags & 0x4000) == 0)) {
                // Not in a special state (e.g., not stunned or special animation)
                float *worldMatrix = (float *)(*(int *)(thisPtr + 0x10) + 0x80 + *(int *)(*gameStatePtr + 8));
                // Copy world orientation
                tempForce[0] = worldMatrix[0];
                tempForce[1] = worldMatrix[1];
                tempForce[2] = worldMatrix[2];
                tempForce[3] = worldMatrix[3];

                int physicsData = *(int *)(thisPtr + 0x24); // offset +0x24 physics data
                if ((*(uint *)(physicsData + 0x10) & 6) == 0) {
                    // Add optional offset from physics data
                    tempForce[0] += *(float *)(physicsData + 0x1c);
                    tempForce[1] += *(float *)(physicsData + 0x20);
                    tempForce[2] += *(float *)(physicsData + 0x24);
                }

                if (*(char *)(physicsData + 0x6c) == '\0') {
                    // No special override, set velocity directly
                    FUN_004e9440(*(int *)(thisPtr + 0x28), &tempForce); // apply velocity
                } else {
                    // Special physics case
                    if ((*(uint *)(physicsData + 0x10) & 0x2000) == 0) {
                        FUN_0048efa0(*(int *)(thisPtr + 0x10) + *(int *)(*gameStatePtr + 8) + 0x50, local_50_48);
                    } else {
                        FUN_004fef50();
                    }
                    FUN_004e9400(); // some setup
                    tempForce[0] = 0.0f;
                }
            }

            // Check if impulse magnitude is below threshold and timer condition
            if ((tempForce[0] < *(float *)(*(int *)(thisPtr + 0x24) + 0x14)) &&
                (*(float *)(*(int *)(thisPtr + 0x24) + 0x14) < *(float *)(thisPtr + 0x34))) {
                // Call virtual function via vtable (offset 0x1c) - likely onCollision or stop
                (*(code **)(*(int *)thisPtr + 0x1c))();
                tempForce[0] = 0.0f;
            }

            // Check collision flag at gameState
            int gsBase = *gameStatePtr;
            if ((*(byte *)(*(int *)(thisPtr + 0x10) + *(int *)(gsBase + 8)) & 1) != 0) {
                // Collision bit set: clear force and call apply with zero
                tempForce[1] = 0.0f;
                tempForce[2] = 0.0f;
                tempForce[3] = 0.0f;
                FUN_004e94a0(&tempForce, 0);
                return;
            }

            // Compute impulse scale based on accumulated time and physics parameters
            int physData = *(int *)(thisPtr + 0x24);
            float maxImpulse = *(float *)(physData + 0x3c);
            float minImpulse = *(float *)(physData + 0x38);
            float accumTime = *(float *)(thisPtr + 0x34); // time accumulator (offset +0x34)
            float rampUp = accumTime * *(float *)(physData + 0x2c) + *(float *)(physData + 0x28);
            float rampDown = accumTime * *(float *)(physData + 0x34) + *(float *)(physData + 0x30);
            if (rampUp < rampDown) {
                rampDown = rampUp;
            }
            // Clamp to min/max range
            if ((rampDown < minImpulse) || (maxImpulse < rampDown)) {
                rampDown = maxImpulse;
            }

            // Check state flags: if not in sprint or something matching (offset 0x2c, 0x30)
            if ((*(int *)(thisPtr + 0x2c) != 1) || (*(int *)(thisPtr + 0x30) != 0)) {
                float tempScale = rampDown;
                FUN_004ebc00(*(int *)(thisPtr + 4), 0); // possibly reset something
                rampDown = tempScale * rampDown; // rampDown * rampDown? Actually fVar9 = fVar10; then fVar10 = fVar9 * fVar10 -> square
                tempForce[0] = 0.0f;
            }

            impulseScale = rampDown * forwardForce * steeringForce;

            // If short timer remains, scale impulse by ratio
            if (tempForce[0] < *(float *)(thisPtr + 0x40)) {
                impulseScale = (*(float *)(thisPtr + 0x40) / *(float *)(physData + 0x78)) * impulseScale;
            }

            // Handle sprint/run state flags (offset 0x3c)
            uint runFlags = *(uint *)(thisPtr + 0x3c);
            if ((runFlags & 6) != 0) {
                if ((runFlags & 2) == 0) {
                    if ((runFlags & 1) != 0) {
                        *(uint *)(thisPtr + 0x3c) = runFlags & 0xfffffffe;
                        FUN_004e9600(); // stop sprint
                    }
                    *(uint *)(thisPtr + 0x3c) = *(uint *)(thisPtr + 0x3c) & 0xfffffffb;
                } else {
                    if (impulseScale <= DAT_00e2dd1c) {
                        if ((runFlags & 1) != 0) {
                            *(uint *)(thisPtr + 0x3c) = runFlags & 0xfffffffe;
                            FUN_004e9600();
                        }
                    } else if (((runFlags & 1) == 0) && (char ret = FUN_004e95e0(), ret != '\0')) {
                        // can sprint
                        *(uint *)(thisPtr + 0x3c) = runFlags | 1;
                    }
                }
            }

            // Build force vector from physics data's direction (offset 0x44,0x48,0x4c)
            int phys = *(int *)(thisPtr + 0x24);
            forceX = impulseScale * *(float *)(phys + 0x44);
            forceY = impulseScale * *(float *)(phys + 0x48);
            forceZ = impulseScale * *(float *)(phys + 0x4c);

            // If some flag (0x80000) on entity, apply scaling from entity (offset 0xa0,0xa4,0xa8)
            if ((*(uint *)(*(int *)(thisPtr + 0x10) + *((int *)(*gameStatePtr) + 2)) & 0x80000) != 0) {
                int entBase = *(int *)(thisPtr + 4);
                forceX *= *(float *)(entBase + 0xa0);
                forceY *= *(float *)(entBase + 0xa4);
                forceZ *= *(float *)(entBase + 0xa8);
            }

            // Apply the impulse with a flag from physics data (offset 0x40)
            FUN_004e94a0(&tempForce, *(int *)(phys + 0x40));
            FUN_004aa7b0(*(int *)(entityPtr + 0x84)); // update animation timer

            // Accumulate time
            *(float *)(thisPtr + 0x34) = *(float *)(thisPtr + 0x34) + deltaTime;
        }
    }
}