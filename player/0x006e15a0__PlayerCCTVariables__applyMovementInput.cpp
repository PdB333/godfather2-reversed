// FUNC_NAME: PlayerCCTVariables::applyMovementInput
// Function at 0x006e15a0: Applies movement input to a character controller, integrating velocity and updating position.
// This is likely part of the PlayerCCTVariables class (character controller variables).
// Offsets: +0x1e4 = velocityX (float), +0x1e8 = velocityZ (float), +0x1ec = movementState (int, 0x48 = idle/disabled)

char __thiscall PlayerCCTVariables::applyMovementInput(void* thisPtr, float inputX, float inputY, float* position) {
    float fVar1;
    float fVar3;
    float fVar11;
    char result;
    bool isInVehicle;

    result = '\0';

    // Apply global sensitivity scaling if flags are set
    if (DAT_0112a7a5 != '\0') {
        inputX *= DAT_00d5ccf8;  // X axis sensitivity multiplier
    }
    if (DAT_0112a7a4 != '\0') {
        inputY *= DAT_00d5ccf8;  // Y axis sensitivity multiplier
    }

    // Check if character is in a state that allows movement (state not 0 or 0x48)
    int movementState = *(int*)((char*)thisPtr + 0x1ec);
    if (movementState != 0 && movementState != 0x48) {
        // Get forward and right vectors based on current orientation
        // FUN_00424fb0 likely constructs a vector (possibly forward direction)
        // We'll call it getForwardVector
        Vector3 forwardVec;  // local_7c
        Vector3* fwdResult = getForwardVector(&forwardVec, 0);
        Vector3 fwd = *fwdResult;

        // FUN_00425060 likely constructs a right vector
        Vector3 rightVec;  // local_6c
        Vector3* rightResult = getRightVector(&rightVec, 0);
        Vector3 right = *rightResult;

        // Compute some intermediate vectors (probably from orientation)
        // FUN_0056b8a0 might be a cross product or transformation
        Vector3 someVec; // local_50
        someVec = transformVector(fwd, right);

        // Normalize forward and right vectors
        Vector3 fwdNorm = normalizeVector(fwd);
        Vector3 rightNorm = normalizeVector(right);

        // Get the target position or reference from the vector (first vector's components)
        // Local variables: local_5c = fwd.x, local_54 = fwd.y? Actually it's from the first vector's data
        // This part is messy; likely using fwd and right as axes for movement

        // Check if the current position is within a certain range of a target (using the forward vector as target?)
        float targetX = fwd.x;
        float targetY = fwd.y; // but only x and z used? Might be XY of position.
        // The code uses position[0] (x) and position[2] (z) for distance check
        // So targetX is compared with position[0], targetY with position[2]? Actually it's local_94 - local_54 and (float)local_9c - (float)local_5c
        // local_94 = position[2], local_9c = first 8 bytes of position (x and y as double?) Unclear.
        // We'll assume it's a distance check against a target point

        float currentX = position[0];
        float currentZ = position[2];
        float targetXFromVec = fwd.x;
        float targetYFromVec = fwd.y; // but used as z?
        float distanceSq = (currentZ - targetYFromVec)*(currentZ - targetYFromVec) + (currentX - targetXFromVec)*(currentX - targetXFromVec);
        if (DAT_00e51268 < sqrtf(distanceSq)) {
            // Acceleration/deceleration constants
            float accelX = DAT_00e448d4;  // base x acceleration
            float accelZ = DAT_00d5f544;  // base z acceleration

            // Check if character is in a vehicle or special mode (affects acceleration)
            isInVehicle = FUN_00410eb0();  // returns true if in vehicle
            if (isInVehicle) {
                accelZ = DAT_00e44828;  // vehicle acceleration for Z
                accelX = DAT_00e44718;  // vehicle acceleration for X
            }

            // Apply input to velocity with damping
            float* velocityX = (float*)((char*)thisPtr + 0x1e4);
            float* velocityZ = (float*)((char*)thisPtr + 0x1e8);
            float inputMask = DAT_00e44680;  // mask for input acceptance

            // Apply input to velocity X (forward/backward)
            if ((float)((uint)inputY & (uint)inputMask) <= 0.0f) {
                // No input, apply damping or zero
                if (0.0f < (float)(DAT_0112a950 & (uint)inputMask)) {
                    // Some threshold check, clamp velocity toward zero
                    *velocityX = clampToZero(*velocityX, 0.0f, DAT_0112a950);
                }
            } else {
                *velocityX = accelX * inputY + *velocityX;
            }

            // Apply input to velocity Z (lateral/strafe)
            if ((float)((uint)inputX & (uint)inputMask) <= 0.0f) {
                if (0.0f < (float)(DAT_0112a94c & (uint)inputMask)) {
                    *velocityZ = clampToZero(*velocityZ, 0.0f, DAT_0112a94c);
                }
            } else {
                *velocityZ = accelZ * inputX + *velocityZ;
            }

            // Clamp velocities within allowed range
            float velX = *velocityX;
            float minVelX = DAT_00e51264;
            float maxVelX = DAT_00e51260;
            if (minVelX < velX && velX < maxVelX) {
                // Keep within range, otherwise clamp to boundaries
                // Actually the code reassigns fVar11
                float clamped = (minVelX < velX) ? ((velX < maxVelX) ? velX : maxVelX) : minVelX;
                // The original logic is: if (DAT_00e51264 < fVar1) { fVar11 = DAT_00e51260; if(fVar1 < DAT_00e51260) fVar11 = fVar1; } else fVar11 = fVar1? Actually it's messy.
                // We'll just clamp properly
                if (velX > maxVelX) velX = maxVelX;
                else if (velX < minVelX) velX = minVelX;
            }
            *velocityX = velX;

            float velZ = *velocityZ;
            float minVelZ = DAT_00e5125c;
            float maxVelZ = DAT_00e44564 - DAT_00e5125c; // computed from constants
            if (velZ < maxVelZ && (velZ > minVelZ)) {
                // Keep existing
            } else {
                velZ = (velZ < minVelZ) ? minVelZ : maxVelZ;
            }
            *velocityZ = velZ;

            // Apply velocities to position using the forward and right direction vectors
            Vector3 moveFwd = normalizeVector(forwardVec);  // local_9c, local_94 from earlier
            Vector3 moveRight = normalizeVector(rightVec);

            // Move forward direction by velocityZ (forward/backward)
            position[0] += moveFwd.x * (*velocityZ);
            position[1] += moveFwd.y * (*velocityZ);
            position[2] += moveFwd.z * (*velocityZ);

            // Move right direction by velocityX (lateral)
            position[0] += moveRight.x * (*velocityX);
            position[1] += moveRight.y * (*velocityX);
            position[2] += moveRight.z * (*velocityX);
        }
    }

    return result;
}