// FUNC_NAME: CharacterStateMachine::processAnimationUpdate

void __thiscall CharacterStateMachine::processAnimationUpdate(int thisPtr, uint param_2)
{
    float *matrixPtr;
    float *matrixPtrB;
    float *matrixPtrC;
    byte byteVal;
    int stateObjPtr;
    bool canUpdate;
    char charResult;
    int localIndex;
    int *queuePtr;
    undefined4 ecxOut;
    int fsOffset;
    undefined4 xmm0In;
    float tempFloat1;
    float tempFloat2;
    float local_a0;
    float fStack_9c;
    float fStack_98;
    undefined4 uStack_94;
    float local_90;
    float fStack_8c;
    float fStack_88;
    float fStack_84;
    float local_80;
    float local_7c;
    float local_70;
    float fStack_6c;
    float fStack_68;
    float fStack_64;
    float local_60;
    float fStack_5c;
    float fStack_58;
    float fStack_54;
    float local_50;
    float fStack_4c;
    float fStack_48;
    float fStack_44;
    float local_40;
    float fStack_3c;
    float fStack_38;
    undefined4 uStack_34;
    float local_30;
    float local_2c;
    float local_28;
    char animSetBuffer[28];

    canUpdate = true;
    // Check if the character is in a stunned/interrupted state (bit 0x40) or being ragdolled (bit 0x200)
    if ((*(byte *)(*(int *)(thisPtr + 0x24) + 0x14) & 0x40) == 0) {
LAB_004e7a23:
        if (((*(uint *)(*(int *)(thisPtr + 0x24) + 0x14) & 0x200) == 0) ||
           (((byteVal = *(byte *)(*(int *)(thisPtr + 0x24) + 0x11), byteVal == 0 || (DAT_011947e4 == 0)) ||
            (((byte)DAT_011947e4 & byteVal) != 0)))) goto LAB_004e7a46;
    }
    else {
        // Stunned state: check if we can break out
        stateObjPtr = *(int *)(*(int *)(thisPtr + 4) + 0x20); // +0x20 in some sub-object
        if (stateObjPtr != 0) {
            *(int *)(stateObjPtr + 4) = *(int *)(stateObjPtr + 4) + 1; // reference count?
        }
        stateObjPtr = FUN_004e8550(stateObjPtr); // Check condition
        if ((stateObjPtr == 0) || (charResult = FUN_004e4230(), charResult != '\0')) goto LAB_004e7a23;
    }
    canUpdate = false;

LAB_004e7a46:
    // Parse animation set from param_2 into local buffer
    charResult = FUN_004e62a0(param_2, &local_a0, animSetBuffer);
    if (charResult == '\0') {
        canUpdate = false;
    }

    stateObjPtr = *(int *)(thisPtr + 0x24);
    // Check if animation state is valid (0x10 is the state count, array at 0x01194738 indicates state validity)
    if (((*(byte *)(stateObjPtr + 0x10) < 0x11) && ((&DAT_01194738)[*(byte *)(stateObjPtr + 0x10)] != '\0')) ||
       (!canUpdate)) {
        // If not valid or update disallowed, set flag to push event to queue
        if (*(char *)(thisPtr + 0x5c) != '\0') {
            *(char *)(thisPtr + 0x5c) = 0;
            queuePtr = (int *)(DAT_01206880 + 0x14); // Event queue pointer
            if (*(char *)(stateObjPtr + 0x10) == '\v') { // 0xB – special state
                **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01124b1c; // Tag for this type
                *queuePtr = *queuePtr + 4;
                *(int *)*queuePtr = thisPtr;
                *queuePtr = *queuePtr + 4;
                return;
            }
            **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01124b6c; // Default tag
            *queuePtr = *queuePtr + 4;
            *(int *)*queuePtr = thisPtr;
            *queuePtr = *queuePtr + 4;
        }
    }
    else {
        // Valid state and update allowed
        *(char *)(thisPtr + 0x5c) = 1;
        switch(*(char *)(stateObjPtr + 0x10)) { // Animation state enum
        case 0: // Idle
        case 1: // Idle 2?
        case 6: // Some action
        case 7:
        case 0xD:
        case 0x10:
            FUN_004e56c0(thisPtr, &local_a0); // Handle idle/wait states
            return;
        case 2: // Walking/Running
            local_70 = DAT_00e2b1a4; // Probably a constant (maybe 1.0 or some max speed)
            fStack_6c = DAT_00e2b1a4;
            fStack_68 = DAT_00e2b1a4;
            fStack_64 = DAT_00e445d0; // Another constant (maybe gravity? 0.0?)
            local_60 = 0.0;
            fStack_5c = 0.0;
            fStack_58 = 0.0;
            fStack_54 = DAT_00e445d0;
            local_90 = DAT_00e2b1a4;
            fStack_8c = DAT_00e2b1a4;
            fStack_88 = DAT_00e2b1a4;
            fStack_84 = 0.0;
            tempFloat1 = DAT_00e2b1a4;
            FUN_004ebc00(*(undefined4 *)(thisPtr + 4), 0); // Some initialisation (maybe clear movement)
            stateObjPtr = *(int *)(thisPtr + 0x24);
            if ((*(uint *)(stateObjPtr + 0x14) & 0x800000) == 0) {
                // Not in special movement mode
                uStack_94 = *(undefined4 *)(stateObjPtr + 0x4c);
                local_70 = *(float *)(stateObjPtr + 0x40); // +0x40: target position/velocity
                fStack_6c = *(float *)(stateObjPtr + 0x44);
                fStack_68 = *(float *)(stateObjPtr + 0x48);
                fStack_64 = tempFloat1;
            }
            else {
                // Special mode: swap inputs
                local_90 = local_a0;
                fStack_8c = fStack_9c;
                fStack_88 = fStack_98;
                fStack_84 = *(float *)(stateObjPtr + 0x4c);
                local_a0 = local_70;
                fStack_9c = fStack_6c;
                fStack_98 = fStack_68;
                uStack_94 = 0;
                local_60 = *(float *)(stateObjPtr + 0x40);
                fStack_5c = *(float *)(stateObjPtr + 0x44);
                fStack_58 = *(float *)(stateObjPtr + 0x48);
                fStack_54 = tempFloat1;
            }
            ecxOut = FUN_00414e30(*(int *)(thisPtr + 4) + 0x20); // Some transform update
            stateObjPtr = FUN_004e8920(ecxOut); // Query movement context
            if (stateObjPtr != 0) {
                if ((*(uint *)(stateObjPtr + 0x5c) >> 1 & 1) != 0) {
                    // Override position/velocity from movement context
                    local_70 = *(float *)(stateObjPtr + 0x30);
                    fStack_6c = *(float *)(stateObjPtr + 0x34);
                    fStack_68 = *(float *)(stateObjPtr + 0x38);
                    fStack_64 = *(float *)(stateObjPtr + 0x54);
                    uStack_94 = *(undefined4 *)(stateObjPtr + 0x50);
                }
                if ((*(uint *)(stateObjPtr + 0x5c) >> 2 & 1) != 0) {
                    // Override rotation/up vector
                    local_60 = *(float *)(stateObjPtr + 0x40);
                    fStack_5c = *(float *)(stateObjPtr + 0x44);
                    fStack_58 = *(float *)(stateObjPtr + 0x48);
                    fStack_54 = *(float *)(stateObjPtr + 0x58);
                    local_90 = *(float *)(stateObjPtr + 0x20);
                    fStack_8c = *(float *)(stateObjPtr + 0x24);
                    fStack_88 = *(float *)(stateObjPtr + 0x28);
                    fStack_84 = *(float *)(stateObjPtr + 0x60);
                }
            }
            FUN_004e5960(thisPtr, &local_a0, &local_90, &local_60, &local_70); // Apply walking movement
            return;
        case 3: // Diving? or special action
            stateObjPtr = *(int *)(*(int *)(thisPtr + 4) + 0xc4);
            if ((stateObjPtr != 0) && (stateObjPtr != 0x48)) { // Not null and not a specific value
                FUN_004e6720(); // Some preparation
                FUN_004e6c10(thisPtr, &local_a0, xmm0In); // Handle dive/tackle
                return;
            }
            break;
        case 4: // Sprinting?
            local_40 = local_a0;
            fStack_3c = fStack_9c;
            fStack_38 = fStack_98;
            uStack_34 = uStack_94;
            FUN_004ebc00(*(undefined4 *)(thisPtr + 4), 0);
            FUN_004e6200(); // Update speed multiplier?
            tempFloat1 = local_a0 * *(float *)(thisPtr + 0x2c); // Apply speed factor
            local_2c = tempFloat1;
            if (tempFloat1 < 0.0) {
                local_2c = 0.0;
            }
            FUN_004e6720();
            local_28 = tempFloat1;
            charResult = FUN_004e4cf0(); // Get random? or some condition
            if (charResult == '\0') {
                tempFloat1 = 0.0;
            }
            else {
                FUN_004ebc00(*(undefined4 *)(thisPtr + 4), 0);
            }
            tempFloat2 = tempFloat1;
            charResult = FUN_004e4cf0();
            if (charResult == '\0') {
                tempFloat2 = 0.0;
            }
            else {
                FUN_004ebc00(*(undefined4 *)(thisPtr + 4), 0);
            }
            // Build transform matrix from global skeleton
            stateObjPtr = *(int *)(**(int **)(fsOffset + 0x2c) + 8); // Global skeleton manager
            localIndex = *(int *)(thisPtr + 0x10); // Bone index?
            matrixPtr = (float *)(stateObjPtr + 0x60 + localIndex); // Matrices for bones
            matrixPtrB = (float *)(stateObjPtr + 0x70 + localIndex);
            fStack_88 = 0.0;
            matrixPtrC = (float *)(stateObjPtr + 0x50 + localIndex);
            fStack_84 = DAT_00e2b1a4;
            local_50 = matrixPtrC[12] * DAT_00e2b1a4 + matrixPtrC[0] * tempFloat2 + matrixPtr[0] * tempFloat1 + matrixPtrB[0] * 0.0;
            fStack_4c = matrixPtrC[13] * DAT_00e2b1a4 + matrixPtrC[1] * tempFloat2 + matrixPtr[1] * tempFloat1 + matrixPtrB[1] * 0.0;
            fStack_48 = matrixPtrC[14] * DAT_00e2b1a4 + matrixPtrC[2] * tempFloat2 + matrixPtr[2] * tempFloat1 + matrixPtrB[2] * 0.0;
            fStack_44 = matrixPtrC[15] * DAT_00e2b1a4 + matrixPtrC[3] * tempFloat2 + matrixPtr[3] * tempFloat1 + matrixPtrB[3] * 0.0;
            local_90 = tempFloat2;
            fStack_8c = tempFloat1;
            FUN_004e5b40(thisPtr, &local_50); // Apply sprint movement
            return;
        case 5: // Crouching?
            FUN_004e55c0(thisPtr, &local_a0);
            return;
        case 8: // Various action states
        case 10:
        case 12:
            FUN_004e5790(thisPtr, &local_a0, animSetBuffer);
            return;
        case 0xB: // Climbing? or mounting
            FUN_004e5890(thisPtr, &local_a0);
            return;
        case 0xE: // Strafing? or aimed walking
            local_90 = local_a0;
            fStack_8c = fStack_9c;
            fStack_88 = fStack_98;
            fStack_84 = (float)uStack_94;
            charResult = FUN_004e4cf0();
            if (charResult == '\0') {
                local_a0 = *(float *)(stateObjPtr + 0x4c);
            }
            else {
                FUN_004ebc00(*(undefined4 *)(thisPtr + 4), 0);
            }
            local_7c = local_a0;
            FUN_004e6200();
            local_80 = local_a0 * *(float *)(thisPtr + 0x2c);
            tempFloat1 = 0.0;
            if ((local_80 <= 0.0) || (tempFloat1 = DAT_00e2b1a4, DAT_00e2b1a4 <= local_80)) {
                local_80 = tempFloat1;
            }
            FUN_004e5c60(thisPtr, &local_90); // Apply strafe movement
            return;
        case 0xF: // Aiming while sprinting? (similar to case 4)
            local_40 = local_a0;
            fStack_3c = fStack_9c;
            fStack_38 = fStack_98;
            uStack_34 = uStack_94;
            charResult = FUN_004e4cf0();
            if (charResult == '\0') {
                local_a0 = *(float *)(stateObjPtr + 0x4c);
            }
            else {
                FUN_004ebc00(*(undefined4 *)(thisPtr + 4), 0);
            }
            local_2c = local_a0;
            FUN_004e6200();
            tempFloat1 = local_a0 * *(float *)(thisPtr + 0x2c);
            if (0.0 < tempFloat1) {
                local_30 = tempFloat1;
                if (DAT_00e2b1a4 <= tempFloat1) {
                    local_30 = DAT_00e2b1a4;
                }
            }
            else {
                local_30 = 0.0;
            }
            charResult = FUN_004e4cf0();
            if (charResult == '\0') {
                tempFloat1 = 0.0;
            }
            else {
                FUN_004ebc00(*(undefined4 *)(thisPtr + 4), 0);
            }
            tempFloat2 = tempFloat1;
            charResult = FUN_004e4cf0();
            if (charResult == '\0') {
                tempFloat2 = 0.0;
            }
            else {
                FUN_004ebc00(*(undefined4 *)(thisPtr + 4), 0);
            }
            stateObjPtr = *(int *)(**(int **)(fsOffset + 0x2c) + 8);
            localIndex = *(int *)(thisPtr + 0x10);
            matrixPtr = (float *)(stateObjPtr + 0x60 + localIndex);
            matrixPtrB = (float *)(stateObjPtr + 0x70 + localIndex);
            fStack_88 = 0.0;
            matrixPtrC = (float *)(stateObjPtr + 0x50 + localIndex);
            fStack_84 = DAT_00e2b1a4;
            local_50 = matrixPtrC[12] * DAT_00e2b1a4 + matrixPtrC[0] * tempFloat2 + matrixPtr[0] * tempFloat1 + matrixPtrB[0] * 0.0;
            fStack_4c = matrixPtrC[13] * DAT_00e2b1a4 + matrixPtrC[1] * tempFloat2 + matrixPtr[1] * tempFloat1 + matrixPtrB[1] * 0.0;
            fStack_48 = matrixPtrC[14] * DAT_00e2b1a4 + matrixPtrC[2] * tempFloat2 + matrixPtr[2] * tempFloat1 + matrixPtrB[2] * 0.0;
            fStack_44 = matrixPtrC[15] * DAT_00e2b1a4 + matrixPtrC[3] * tempFloat2 + matrixPtr[3] * tempFloat1 + matrixPtrB[3] * 0.0;
            local_90 = tempFloat2;
            fStack_8c = tempFloat1;
            FUN_004e5d70(thisPtr, &local_50); // Apply aim-sprint movement
            return;
        default:
            break;
        }
    }
    return;
}