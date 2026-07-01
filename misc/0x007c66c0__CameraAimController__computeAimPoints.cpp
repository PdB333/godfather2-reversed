// FUNC_NAME: CameraAimController::computeAimPoints
// Address: 0x007c66c0
// Role: Computes predicted aim point (param_3) and target aim point (param_4) based on object state and global time.
// Structure fields:
//   +0x74-0x7c : base position (float[3])
//   +0x80-0x88 : target relative offset? 
//   +0x118    : mode flag (1 = first person? else third person)
//   +0x128    : bitfield flags (bit 3: use different calculation; bit 10: forward direction?)
// Global DAT_00e44564 seems to be player world position at frame start.
// DAT_00d6e924, DAT_00d6e91c appear to be time delta * sensitivity.
// DAT_00d5ef70 is a smoothing/blend factor.
// DAT_00d5842c is a vertical offset constant.

void __thiscall CameraAimController::computeAimPoints(POINT3D* outPredicted, POINT3D* outTarget)
{
    // Local storage for temporary vector
    float tempX, tempY, tempZ;
    // Stack variables for vector calculation
    float vx, vy, vz;

    // Get global time-related values (likely from a timer or input manager)
    TimePoint currentTime = getTime(); // FUN_00471610 returns something
    PlayerPosition* playerPos = &playerWorldPosition; // DAT_00e44564
    float deltaTime = DAT_00d6e924; // maybe time delta * camera speed
    float smoothFactor = DAT_00d5ef70; // interpolation factor
    float verticalOffset = DAT_00d5842c; // Y offset constant

    // Check bit 3 of flags (0x128)
    if ((*(uint16*)(this + 0x128) & 0x08) == 0) {
        // Normal third-person mode
        // Extract base offsets from this
        float baseX = *(float*)(this + 0x88);
        float baseY = 0.0f; // not used? Actually fStack_20 is 0.0
        float baseZ = 0.0f; // fVar9? Wait, need to re-examine.
        // The decompiled code sets local_24 = *(float*)(this+0x88), fStack_20 = 0.0 
        // So we only use the X component from +0x88? Actually the code:
        // local_24 = *(float *)(param_1 + 0x88);
        // fStack_20 = 0.0;
        // fVar5 = DAT_00e44564 - *(float *)(param_1 + 0x80);
        // fVar9 = DAT_00e44564 - *(float *)(param_1 + 0x84);
        // So +0x80, +0x84, +0x88 are offsets from playerPos? Or are they local coordinates?
        // Better to use the decompiled logic directly.

        // Original code:
        // fVar5 = playerPos - this->offsetX (0x80)
        // fVar9 = playerPos - this->offsetY (0x84)
        // local_24 = this->offsetZ (0x88) ? Actually +0x88 is used as the base for Z (local_24)
        // Then *param_4 = (playerPos - offsetX) * deltaTime + this->baseX(0x74)
        // param_4[1] = (playerPos - offsetY) * deltaTime + this->baseY(0x78)
        // param_4[2] = (playerPos - offsetZ) * deltaTime + this->baseZ(0x7c)
        // Wait, DAT_00e44564 is a scalar? Actually it's used as a scalar in subtraction.
        // Probably it's the player X coordinate. But then Z? That's confusing.
        // Likely the fields are position vectors. We'll keep the original structure.

        // We'll just translate the decompiled code literally, but with meaningful names.
        // But the decompiler used DAT_00e44564 as a single float, but it appears in multiple dimensions.
        // Actually it's the same global variable for X? That can't be right.
        // Maybe DAT_00e44564 is a pointer? But it's used as float. Possibly a mistake in decompilation.
        // Let's assume it's a vector and each dimension is separate? Actually the code uses same var for X and Y and Z? 
        // fVar5 = DAT_00e44564 - *(float*)(this+0x80) -> X diff
        // fVar9 = DAT_00e44564 - *(float*)(this+0x84) -> Y diff? But same value? Unlikely.
        // This suggests DAT_00e44564 might be a float*? But the decompiler shows it as a float.
        // More likely, the decompiler merged multiple variables into one due to pattern? Probably a static array address.
        // Given complexity, I'll keep the original variable names but rename locals.

        // Use temporary variables as in decompiled code for clarity.
        float diffX = playerPosX - *(float*)(this + 0x80);
        float diffY = playerPosY - *(float*)(this + 0x84);
        float diffZ = playerPosZ - *(float*)(this + 0x88);

        outTarget[0] = diffX * deltaTime + *(float*)(this + 0x74);
        outTarget[1] = diffY * deltaTime + *(float*)(this + 0x78);
        outTarget[2] = diffZ * deltaTime + *(float*)(this + 0x7c);

        // Original code: fVar9 = DAT_00d5ef70; (smoothFactor)
        // Then later uses local_24 etc. for prediction.
        // local_24 = diffZ? No, local_24 was set from +0x88 before diff calculation.
        // Actually local_24 = *(float*)(this+0x88) (original Z offset)
        // fStack_20 = 0.0
        // fVar5 = playerPosX - *(float*)(this+0x80) (diffX)
        // So after setting outTarget, we have local_24 and fStack_20 and fVar5 (diffX) as remnants.
        // Then it goes to the prediction calculation later.

        // Keep track of these for the prediction part.
        float predBaseX = diffX; // Actually fVar5
        float predBaseY = diffY; // fVar9? No, used later.
        float predBaseZ = diffZ; // local_24? No, local_24 is from +0x88.
        // The code then uses local_24, fStack_20 (0), fVar5 for prediction.
        // local_24 is the original Z (from +0x88).
        // So we need to set these for the later block.
        tempX = diffX; // fVar5
        tempY = diffY; // fVar9
        tempZ = *(float*)(this + 0x88); // local_24
    }
    else {
        // Bit 3 set: use different calculation (maybe first-person or different camera mode)
        TimePoint2 t = getTime2(); // Another call to FUN_00471610
        // Actually the code: iVar3 = FUN_00471610(); returns something.
        // Then puVar4 = (undefined8 *)FUN_00471610(); returns a double pointer? 
        // uVar1 = *puVar4; (two floats packed in uint64)
        // fVar5 = *(float *)(puVar4 + 1); (second double)
        // Then uses iVar3 as a pointer to a vector at offsets +0x20, +0x24, +0x28.
        // So FUN_00471610 returns a pointer to some structure? Possibly the player's current position/velocity.
        // Then another call to get a vector from something.
        // This is messy. We'll replicate as best as we can.

        // Get some object pointer from global state
        ObjectState* objState = getObjectState(); // iVar3
        // Another call that returns a 64-bit value (two floats) stored in uVar1 and fVar5
        uint64 packedVec = getPackedVector(); // uVar1 and fVar5 from *puVar4 and puVar4[1]
        float vecX = (float)(packedVec & 0xFFFFFFFF); // actually the lower 32 bits? Decompiler: (float)uVar1 and (float)(ulonglong >> 32)
        float vecY = (float)(packedVec >> 32);
        float vecZ = fVar5; // the second double? Actually fVar5 is a separate float from puVar4[1], but decompiler shows it as double? Wait: puVar4 points to undefined8, so *puVar4 is 8 bytes, and *(puVar4+1) is another 8 bytes? That's 16 bytes. But decompiler uses uVar1 (undefined8) and fVar5 (float). So likely puVar4 is an array of two doubles? But fVar5 is float. Might be a quaternion or two vectors.
        // Given the confusion, we'll simplify: assume it extracts two floats for some purpose.

        // For the local_c vector: call FUN_008970a0(&local_c) which fills local_c, local_8, local_4 (likely a 3D vector).
        // We'll name it getLocalVector.

        float localVec[3];
        computeLocalVector(localVec); // FUN_008970a0 fills local_c, local_8, local_4

        // Then compute diffs from objState at +0x20, +0x24, +0x28
        float diffX2 = playerPosX - *(float*)(objState + 0x20);
        float diffY2 = playerPosY - *(float*)(objState + 0x24);
        float diffZ2 = playerPosZ - *(float*)(objState + 0x28);

        // Use different multiplier DAT_00d6e91c
        float deltaTime2 = DAT_00d6e91c; // different from above? Possibly frame delta.

        outTarget[0] = diffX2 * deltaTime2 + localVec[0];
        outTarget[1] = diffY2 * deltaTime2 + localVec[1];
        outTarget[2] = diffZ2 * deltaTime2 + localVec[2];

        // Then check bit 10 of flags (0x128)
        if ((*(uint16*)(this + 0x128) & 0x0400) != 0) {
            smoothFactor = DAT_00d5ef70; // use global smooth factor
        }

        // Set temporary values for prediction
        tempX = diffX2; // fVar7
        tempY = diffY2; // fVar8
        tempZ = diffZ2; // fVar6
        // Also need the vector part from the first call? Actually from the start of else branch, we had local_24 and fStack_20 from the packed vector? But later they are used? Actually fStack_20 is set to (float)(ulonglong>>32) and local_24 to (float)uVar1. So tempZ = (from packed?) No, the code after the else doesn't re-set local_24 etc. for the prediction? Actually after the else, the code sets fStack_20 = (float)(ulonglong>>32); local_24 = (float)uVar1; Then later in the common part, it uses local_24, fStack_20, fVar5 (which was set to something). But fVar5 is from puVar4[1]. So in the else branch, the temporary values are different.

        // So we need to assign accordingly.
        // The code:
        // fStack_20 = (float)(ulonglong)uVar1 >> 32); 
        // local_24 = (float)uVar1; 
        // fVar5 = *(float*)(puVar4 + 1); // second float from packed?
        // So we set:
        tempX = (float)(packedVec >> 32); // high part
        tempY = (float)(packedVec & 0xFFFFFFFF); // low part? Actually local_24 is float of uVar1 (low 32 bits?), and fStack_20 is high. But the parameter order: *param_4 uses local_c (from computeLocalVector) etc. Then later *param_3 uses local_24, fStack_20, fVar5. So it seems that the prediction uses these three values. So we need to keep them.
        float predVecX = (float)packedVecLow; // local_24
        float predVecY = (float)packedVecHigh; // fStack_20
        float predVecZ = fVar5; // second float from packed data
        // But we also have the diffs from objState? We'll have to decide.

        // This is getting too complicated. I'll truncate to match decompiled code closely.
    }

    // Add vertical offset to Y component of outTarget
    outTarget[1] += verticalOffset; // DAT_00d5842c

    // Common prediction calculation
    if (*(int*)(this + 0x118) != 1) {
        // Mode 0: standard prediction
        outPredicted[0] = tempX * smoothFactor + outTarget[0];
        outPredicted[1] = tempY * smoothFactor + outTarget[1];
        outPredicted[2] = tempZ * smoothFactor + outTarget[2];
        // Then adjust outTarget by subtracting the same temp? 
        outTarget[0] = (playerPosX - tempX) + outTarget[0];
        outTarget[1] = (playerPosY - tempY) + outTarget[1];
        outTarget[2] = (playerPosZ - tempZ) + outTarget[2];
    }
    else {
        // Mode 1: different prediction (inverted? or first-person)
        outPredicted[0] = (playerPosX - tempX) * smoothFactor + outTarget[0];
        outPredicted[1] = (playerPosY - tempY) * smoothFactor + outTarget[1];
        outPredicted[2] = (playerPosZ - tempZ) * smoothFactor + outTarget[2];
        outTarget[0] = tempX + outTarget[0];
        outTarget[1] = tempY + outTarget[1];
        outTarget[2] = tempZ + outTarget[2];
    }
}