// FUNC_NAME: AimControl::updateTargetRotation
void __thiscall AimControl::updateTargetRotation(int thisPtr, int action, float* targetAngle, bool useSmoothing) {
    // +0x5c: pointer to some entity (likely owner or camera)
    int entityPtr = *(int *)(thisPtr + 0x5c);
    
    // Get player/camera transform matrix (16 floats)
    float* viewMatrix = (float*)FUN_00471610(); // returns matrix pointer
    // Copy 16 floats to local matrix
    float localMatrix[16];
    for (int i = 0; i < 16; i++) {
        localMatrix[i] = viewMatrix[i];
    }
    // localMatrix[12] and localMatrix[13] are used later (likely forward vector components)
    float& fwdX = localMatrix[12]; // +0x30 from base? Actually at offset 12*4 = 48 bytes -> but stack layout: local_30 is 13th float, local_28 is 14th
    float& fwdY = localMatrix[13]; // 
    
    // Get current rotation angle (yaw) from member
    float currentAngle = *(float *)(thisPtr + 0x90);
    
    // ========== Normalize target angle to [-PI, PI] ==========
    FUN_00b9a9fa(); // likely FPU state prepare
    float diff = *targetAngle - currentAngle; // not yet used for normalization
    // Actually the code normalizes *targetAngle - some constant? Wait: The first part normalizes something else.
    // Let's follow: after FUN_00471610, it does dVar8 = (double)(*param_3 - *(float *)(iVar3 + 0x30));
    // But iVar3 is result of FUN_00471610, so *(float *)(iVar3+0x30) is the 13th float of the matrix? Actually iVar3 is pointer to matrix, +0x30 is offset to 12th float? Let's re-read:
    // iVar3 = FUN_00471610(); dVar8 = (double)(*param_3 - *(float *)(iVar3 + 0x30));
    // So they subtract the 13th float of the matrix from the target angle. That is weird. Possibly param_3 is target angle, and the matrix contains some reference angle (like current facing direction). 
    // Actually the code then does FUN_00b9a9fa() again, and then the fmod normalization of dVar8. Then stores result in this+0x90. So they compute a new currentAngle as normalized difference? No, they store fVar7 in this+0x90 after normalization. So this+0x90 is being updated.
    // Let's go step by step.
    
    // The first block:
    float* matrix = (float*)FUN_00471610(); // maybe this is a global transform (player position? It's used to get a reference angle.)
    double delta = (double)(*targetAngle - *(float *)(matrix + 0x30)); // 0x30 = 48 bytes = 12th float. That's the 13th element (index 12) of the matrix. Might be the z-axis? Actually typical view matrix: column-major, so index 12 is translation z? Or row 3 col 0? Hard to tell. Maybe it's the camera's pitch? But the function deals with yaw (rotation around Y axis). Let's assume it's the camera's yaw angle.
    
    FUN_00b9a9fa(); // prepare for fmod
    
    float fVar10 = (float)delta * 0.1591549f? Actually _DAT_00d5eee8 is likely 1/(2*PI) = 0.1591549
    // The code does a bitwise fmod to get delta in [-PI, PI]
    // Simplify: normalize angle to range [-PI, PI]
    float normalizedDelta = normalizeAngle((float)delta); // we'll define a helper
    // Actually the code:
    float fVar7 = (float)delta;
    // Then the fmod sequence...
    // I'll skip the bit tricks and assume a function normalizeAngle.
    float norm = normalizeAngle((float)delta);
    *(float *)(thisPtr + 0x90) = norm;
    
    // Now copy matrix again? Actually the code copies the matrix again after normalizing? No, it copies once before the normalization block. Wait, the flow: after normalization, it does puVar4 = (undefined4 *)FUN_00471610(); and copies again. So two copies? The decompiled code shows:
    // iVar3 = FUN_00471610(); // first call
    // ... normalize and store this+0x90
    // Then puVar4 = (undefined4 *)FUN_00471610(); // second call
    // puVar5 = local_50; for ... copy 16 dwords.
    // So the matrix is copied again (overwrites the earlier local_30/28). That second copy is used for the later dot product.
    // So the matrix is obtained again after updating currentAngle.
    
    // So after normalizing, copy matrix to local
    matrix = (float*)FUN_00471610(); // second call
    float localMat[16];
    memcpy(localMat, matrix, 16*4);
    float forwardX = localMat[12]; // local_30
    float forwardY = localMat[13]; // local_28
    
    // Now currentAngle is stored in this+0x90
    float curAngle = *(float *)(thisPtr + 0x90);
    float targetAngleVal = *targetAngle;
    
    // If action is 3 or 2 (rotate towards target)
    if ((action == 3) || (action == 2)) {
        float angleDiff = (curAngle - targetAngleVal) + PI;
        // Normalize angleDiff to [-PI, PI]
        angleDiff = normalizeAngle(angleDiff); // the code does a similar fmod wrap
        // Check if we are close enough to the target (within some threshold)
        bool isClose = FUN_00776d60(angleDiff); // likely checks if abs(angleDiff) < threshold
        // Check if the entity has a specific flag set (bit 2 of uint at +0x249c)
        uint entityFlags = *(uint *)(entityPtr + 0x249c);
        bool canRotate = (entityFlags >> 2) & 1;
        // Also check line-of-sight or something
        bool canSee = FUN_007178e0(); // likely check if target is visible
        if (isClose && canRotate && canSee) {
            // Set "rotation completed" flag (bit 5)
            *(uint *)(thisPtr + 0xac) |= 0x20;
            return;
        } else {
            // Clear the flag
            *(uint *)(thisPtr + 0xac) &= ~0x20;
            return;
        }
    }
    // For other actions (0 or 1)
    float angleDelta;
    if (action == 0) {
        angleDelta = curAngle - targetAngleVal; // rotate clockwise?
    } else {
        angleDelta = targetAngleVal - curAngle; // rotate counter-clockwise?
    }
    float absDelta = fabs(angleDelta);
    if (absDelta < 0.0f) { // this will never be true, but the code has path for negative abs, maybe due to floating point issues?
        // Actually the condition is local_70 < 0.0, but fabs is non-negative, so this path is dead.
        // The code does: if (local_70 < 0.0) { ... } else { if (local_70 <= PI) ... else ... }
        // But since local_70 is absolute value, it's always >=0, so the first if is false.
        // Likely a code error or the comparison is for something else.
        // However the decompiler shows that path, we'll include it but note it's unreachable.
    }
    
    if (absDelta > PI) {
        // If difference > 180 degrees, limit rotation to PI and adjust accordingly
        if (action == 0) {
            angleDelta = targetAngleVal + PI; // actually fVar7 = fVar7 + PI? The code: fVar7 = fVar7 + DAT_00d5eeec; and local_70 = DAT_00d5eeec;
            // Hard to follow exactly, but the intent is to make the target angle point opposite to current.
        } else {
            angleDelta = targetAngleVal - PI; // negative adjustment
        }
    } else if (absDelta <= PI) {
        // Check if we are close enough
        bool isClose = FUN_00776d60(absDelta);
        // Check flags and line-of-sight
        uint entityFlags = *(uint *)(entityPtr + 0x249c);
        bool canRotate = (entityFlags >> 2) & 1;
        bool canSee = FUN_007178e0();
        if (isClose && canRotate && canSee) {
            *(uint *)(thisPtr + 0xac) |= 0x20;
        } else {
            *(uint *)(thisPtr + 0xac) &= ~0x20;
        }
        // If the flag is set (already close), do something (play sound? emit?)
        if (*(uint *)(thisPtr + 0xac) & 0x20) {
            FUN_00732460(someSoundBuffer, 0); // might be play sound
            FUN_0072a0b0(someSoundBuffer); // might be release sound
        }
        goto done;
    } else {
        // absDelta > PI: set local_70 = PI, adjust angleDelta
        if (action != 0) {
            // Similar to earlier but with subtraction
        }
    }
    
    // Normalize the new target angle and store
    float newAngle = normalizeAngle(angleDelta);
    *(float *)(thisPtr + 0x90) = newAngle;
    // Clear the "rotation completed" flag
    *(uint *)(thisPtr + 0xac) &= ~0x20;
    
done:
    // Apply smoothing to the rotation
    float speed = absDelta * 0.95f? Actually DAT_00e44748 is likely a factor (maybe rotation speed multiplier).
    float rotationSpeed = absDelta * 0.01f; // guess
    float currentRotationSpeed = *(float *)(entityPtr + 0x1f88); // maybe current angular velocity
    float newSpeed;
    if (useSmoothing) {
        // If useSmoothing is true, blend towards the target speed
        newSpeed = (rotationSpeed - currentRotationSpeed) * 0.1f + currentRotationSpeed; // _DAT_00d6826c likely 0.1
        FUN_00722370(newSpeed); // set the rotation speed
    } else {
        // If the difference between speeds is very small, just set directly
        float speedDiff = rotationSpeed - currentRotationSpeed;
        // The code does a bitwise AND with DAT_00e44680 (which might be a mask for float bits)
        if ((uint&)speedDiff <= *(uint*)&DAT_00d5f414) { // some epsilon
            FUN_00722370(rotationSpeed);
        } else {
            newSpeed = (rotationSpeed - currentRotationSpeed) * 0.05f + currentRotationSpeed; // _DAT_00d68270 likely 0.05
            FUN_00722370(newSpeed);
        }
    }
}

// Helper function: normalize angle to [-PI, PI]
float normalizeAngle(float angle) {
    const float twoPi = 6.2831855f;
    const float pi = 3.1415927f;
    while (angle > pi) angle -= twoPi;
    while (angle < -pi) angle += twoPi;
    return angle;
}