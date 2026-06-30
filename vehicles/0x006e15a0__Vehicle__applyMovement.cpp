// FUNC_NAME: Vehicle::applyMovement
char __thiscall Vehicle::applyMovement(int thisPtr, float steeringInput, float throttleInput, float *position)
{
    float fVar1;
    float fVar3;
    float fVar11;
    char result;
    char isPlayer;
    uint uVar12;
    float10 fVar10;
    float distance;
    float targetX, targetY, targetZ;
    float forwardX, forwardY, forwardZ;
    float rightX, rightY, rightZ;
    float upX, upY, upZ;
    float velocityForward, velocityRight;
    float accelForward, accelRight;
    float maxForwardSpeed, maxReverseSpeed, maxRightSpeed;
    float clampMin, clampMax;
    float scaleFactor;
    int state;

    result = '\0';
    // Apply global scaling if debug flags are set
    if (DAT_0112a7a5 != '\0') {
        steeringInput = steeringInput * DAT_00d5ccf8;
    }
    if (DAT_0112a7a4 != '\0') {
        throttleInput = throttleInput * DAT_00d5ccf8;
    }

    state = *(int *)(thisPtr + 0x1ec); // +0x1ec: current state/gear
    if ((state != 0) && (state != 0x48)) {
        // Get forward and right vectors from some global (maybe vehicle orientation)
        // FUN_00424fb0 returns pointer to a 3D vector (x,y packed in 8 bytes, z separate)
        {
            undefined8 *vecPtr;
            vecPtr = (undefined8 *)FUN_00424fb0(&local_7c, 0);
            forwardX = *(float *)vecPtr; // first 4 bytes
            forwardY = *(float *)((int)vecPtr + 4); // next 4 bytes
            forwardZ = *(float *)(vecPtr + 1); // next 4 bytes? Actually offset 8
        }
        // Similarly for right vector
        {
            undefined8 *vecPtr;
            vecPtr = (undefined8 *)FUN_00425060(&local_6c, 0);
            rightX = *(float *)vecPtr;
            rightY = *(float *)((int)vecPtr + 4);
            rightZ = *(float *)(vecPtr + 1);
        }
        // Compute up vector as cross product of forward and right? (FUN_0056b8a0)
        FUN_0056b8a0(forwardX, forwardY, forwardZ, &upX); // Actually signature might be cross product
        // Normalize forward, right, up (FUN_0056afa0)
        FUN_0056afa0(&forwardX, &forwardX);
        FUN_0056afa0(&rightX, &rightX);
        FUN_0056afa0(&upX, &upX);

        // Check if target position is valid (FUN_006c8620)
        int targetState = (state == 0) ? 0 : (state - 0x48);
        result = FUN_006c8620(position, targetState, 4);
        if (result != '\0') {
            targetX = position[0];
            targetY = position[1];
            targetZ = position[2];
            // Compute distance to target (2D? using forwardX,forwardY? Actually using local_5c which is forwardX? Wait, local_5c was set from first vector)
            // The code compares distance between target and the forward vector's origin? Actually it uses local_5c (forwardX?) and local_54 (forwardY?) as reference point.
            // But that doesn't make sense. Possibly the first vector is the current position? Let's re-evaluate.
            // The code: local_5c = *puVar8; local_54 = *(float*)(puVar8+1); So local_5c is first 8 bytes (two floats), local_54 is next 4 (third float). So it's a 3D vector.
            // Then later: (float)local_9c - (float)local_5c where local_9c is targetX? Actually local_9c is set from param_4[0] and param_4[1] as an undefined8, so it's targetX and targetY packed.
            // So distance is sqrt((targetZ - forwardZ)^2 + (targetX - forwardX)^2 + (targetY - forwardY)^2?) Actually the code only uses two components: (local_94 - local_54) and ((float)local_9c - (float)local_5c). That's only two dimensions. Possibly it's a 2D distance ignoring Y? Or the vector is 2D? 
            // Given the complexity, I'll assume it's a 2D distance in the horizontal plane.
            distance = SQRT((targetZ - forwardZ) * (targetZ - forwardZ) + (targetX - forwardX) * (targetX - forwardX));
            if (distance > DAT_00e51268) {
                // Acceleration values
                accelForward = DAT_00e448d4;
                accelRight = DAT_00d5f544;
                isPlayer = FUN_00410eb0(); // Check if player controlled
                if (isPlayer != '\0') {
                    accelRight = DAT_00e44828;
                    accelForward = DAT_00e44718;
                }
                // Apply throttle input to forward velocity (stored at +0x1e4)
                uVar12 = DAT_00e44680;
                if ((float)((uint)throttleInput & uVar12) <= 0.0f) {
                    if (0.0f < (float)(DAT_0112a950 & uVar12)) {
                        fVar10 = (float10)FUN_006c89b0(*(undefined4 *)(thisPtr + 0x1e4), 0, DAT_0112a950);
                        *(float *)(thisPtr + 0x1e4) = (float)fVar10;
                    }
                } else {
                    *(float *)(thisPtr + 0x1e4) = accelForward * throttleInput + *(float *)(thisPtr + 0x1e4);
                }
                // Apply steering input to right velocity (stored at +0x1e8)
                if ((float)((uint)steeringInput & uVar12) <= 0.0f) {
                    if (0.0f < (float)(DAT_0112a94c & uVar12)) {
                        fVar10 = (float10)FUN_006c89b0(*(undefined4 *)(thisPtr + 0x1e8), 0, DAT_0112a94c);
                        *(float *)(thisPtr + 0x1e8) = (float)fVar10;
                    }
                } else {
                    *(float *)(thisPtr + 0x1e8) = accelRight * steeringInput + *(float *)(thisPtr + 0x1e8);
                }
                // Clamp forward velocity
                fVar3 = DAT_00e5125c;
                fVar1 = *(float *)(thisPtr + 0x1e4);
                fVar11 = DAT_00e51264;
                if ((DAT_00e51264 < fVar1) && (fVar11 = DAT_00e51260, fVar1 < DAT_00e51260)) {
                    fVar11 = fVar1;
                }
                fVar1 = *(float *)(thisPtr + 0x1e8);
                *(float *)(thisPtr + 0x1e4) = fVar11;
                // Clamp right velocity
                fVar11 = DAT_00e44564 - fVar3;
                if ((DAT_00e44564 - fVar3 < fVar1) && (fVar11 = fVar1, fVar3 <= fVar1)) {
                    fVar11 = fVar3;
                }
                *(float *)(thisPtr + 0x1e8) = fVar11;
                // Apply velocities to position
                // Use normalized forward vector scaled by forward velocity
                FUN_0043a210(&forwardX, &forwardX); // This might be a scale? Actually it's likely a normalize? But already normalized. Maybe it's a copy?
                fVar1 = *(float *)(thisPtr + 0x1e8);
                position[0] = position[0] + forwardX * fVar1;
                position[1] = position[1] + forwardY * fVar1;
                position[2] = position[2] + forwardZ * fVar1;
                // Use normalized right vector scaled by right velocity
                FUN_0043a210(&rightX, &rightX);
                fVar1 = *(float *)(thisPtr + 0x1e4);
                position[0] = position[0] + rightX * fVar1;
                position[1] = position[1] + rightY * fVar1;
                position[2] = position[2] + rightZ * fVar1;
            }
        }
    }
    return result;
}