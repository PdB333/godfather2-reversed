// FUNC_NAME: PlayerSM::updateBlendedMovement
void __thiscall PlayerSM::updateBlendedMovement(void)
{
    float fVar1;
    int iVar2;
    int unaff_ESI; // this
    int iVar3;
    int unaff_FS_OFFSET;
    double dVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    undefined4 uVar8;
    float fVar9;
    float blendedPosX;
    float blendedPosY;
    float minMaxResult;
    undefined **funcTable;
    float unusedFloat;
    int callbackResult;
    undefined4 unused1;
    undefined4 unused2;
    float blendFactorA; // from state component +0xa0
    float blendFactorB;
    float *vecAPtr;
    float *vecBPtr;
    undefined1 *matPtr1;
    undefined1 *matPtr2;
    undefined2 fsValue;
    int stateComponentBase;
    undefined4 unused3;
    float lerpFactor;
    float interpolatedX;
    float interpolatedY;
    float interpolatedZ;
    undefined4 unused4;
    float worldPosX2;
    float worldPosY2;
    float worldPosZ2;
    float worldPosW2;
    float lerpFactor2;
    float worldPosX1;
    float worldPosY1;
    float worldPosZ1;
    undefined4 unused5;
    undefined1 local_e0 [12];
    undefined4 unused6;
    float scaleFactor;
    float unused7;
    undefined4 unused8;
    undefined4 unused9;
    float rotY;
    float unused10;
    undefined4 unused11;
    undefined4 unused12;
    undefined4 unused13;
    undefined4 unused14;
    undefined4 unused15;
    undefined4 unused16;
    float rotX;
    float unused17;
    undefined4 unused18;
    undefined4 unused19;
    undefined1 matrixBuffer1 [64];
    undefined1 matrixBuffer2 [76];

    // Check if state component and state ID are valid
    if (((*(int *)(unaff_ESI + 0x120) != 0) && (*(int *)(unaff_ESI + 0x124) != 0)) &&
        (*(int *)(unaff_ESI + 0x124) != 4)) {
        
        fVar1 = *(float *)(*(int *)(unaff_ESI + 0x120) + 0xa4); // blend factor from state component
        fVar5 = *(float *)(unaff_ESI + 0x1c) * DAT_00e2cd54; // delta time scaled by 0.5
        
        FUN_00414aa0(); // fpu state save
        uVar8 = 0;
        fStack_f4 = 0.0;
        FUN_00414aa0(); // fpu state restore?
        
        fStack_cc = *(float *)(unaff_ESI + 0x3c); // Y velocity or rotation?
        blendedPosY = *(float *)(unaff_ESI + 0x38) * fVar5; // X velocity scaled
        fVar5 = fStack_cc * fVar5; // Y velocity scaled
        
        // Compute four candidate blend values using global constants
        fVar6 = (DAT_00e44564 - blendedPosY) + fVar5;
        fVar9 = (DAT_00e44564 - blendedPosY) + (DAT_00e44564 - fVar5);
        fVar7 = blendedPosY + fVar5;
        blendedPosY = blendedPosY + (DAT_00e44564 - fVar5);
        
        // Determine min and max of the four candidates
        minMaxResult = blendedPosY;
        if (blendedPosY < fVar7) {
            minMaxResult = fVar7;
        }
        if (minMaxResult < fVar6) {
            minMaxResult = fVar6;
        }
        if (minMaxResult < fVar9) {
            minMaxResult = fVar9;
        }
        
        fVar5 = blendedPosY;
        if (fVar9 < blendedPosY) {
            fVar5 = fVar9;
        }
        if (fVar7 <= fVar5) {
            fVar5 = fVar7;
        }
        
        blendedPosX = fVar6;
        if (fVar5 < fVar6) {
            blendedPosX = fVar5;
        }
        
        if (blendedPosY <= fVar9) {
            blendedPosY = fVar9;
        }
        if (blendedPosY < fVar7) {
            blendedPosY = fVar7;
        }
        if (blendedPosY < fVar6) {
            blendedPosY = fVar6;
        }
        // Now minMaxResult, blendedPosX, blendedPosY hold the clamped values
        
        // Initialize some local data
        unused8 = 0;
        unused9 = 0;
        unused11 = 0;
        unused12 = 0;
        unused13 = 0;
        unused14 = 0;
        unused15 = DAT_00e2b1a4; // some constant
        unused16 = 0;
        unused18 = 0;
        unused19 = DAT_00e2b1a4;
        
        scaleFactor = *(float *)(unaff_ESI + 0x38) * DAT_00e2cd54; // X velocity * 0.5
        rotX = DAT_00e2cd54; // 0.5
        unused17 = DAT_00e2cd54; // 0.5
        
        rotY = fStack_cc * DAT_00e44718; // Y velocity * some constant
        fStack_cc = fStack_cc * DAT_00e2cd54; // Y velocity * 0.5
        
        // First interpolation: world position with (1 - fVar1) factor
        fVar5 = DAT_00e44564 - fVar1; // 1.0 - blendFactor
        interpolatedX = fVar5 * worldPosX2 + *(float *)(unaff_ESI + 0x80);
        interpolatedY = fVar5 * worldPosY2 + *(float *)(unaff_ESI + 0x84);
        interpolatedZ = fVar5 * worldPosZ2 + *(float *)(unaff_ESI + 0x88);
        
        // Second interpolation: world position with fVar1 * constant factor
        fVar5 = fVar1 * DAT_00e445ac; // blendFactor * some constant
        lerpFactor2 = worldPosX2;
        worldPosY2 = worldPosY2;
        worldPosZ2 = worldPosZ2;
        worldPosX1 = fVar5 * worldPosX2 + *(float *)(unaff_ESI + 0x80);
        worldPosY1 = fVar5 * worldPosY2 + *(float *)(unaff_ESI + 0x84);
        worldPosZ1 = fVar5 * worldPosZ2 + *(float *)(unaff_ESI + 0x88);
        worldPosW2 = fVar5 * worldPosW2 + *(float *)(unaff_ESI + 0x8c);
        
        unused5 = 0;
        unused4 = 0;
        unused6 = uVar8;
        unused10 = scaleFactor;
        
        // Convert blended vectors to matrix/quaternion
        FUN_006138b0(&interpolatedX, &worldPosX1, local_e0, matrixBuffer1);
        
        // Clamp the blend values with a global threshold
        FUN_006145f0(minMaxResult, blendedPosX, blendedPosY, DAT_00e2e780);
        
        iVar2 = DAT_012234d0; // global singleton pointer
        fVar5 = fVar1 * DAT_00e2d99c; // blendFactor * some constant
        iVar3 = DAT_012234d0 + 0x43080; // offset into singleton
        
        // Update transform or renderable with the blended result
        FUN_0066e3f0(iVar3, &interpolatedX, &lerpFactor2, fVar5);
        
        dVar4 = (double)*(float *)(*(int *)(unaff_ESI + 0x120) + 0xa0); // another float from state component
        FUN_00b99e20(); // double conversion?
        
        // Set up callback arguments
        vecAPtr = &interpolatedX;
        vecBPtr = &lerpFactor2;
        matPtr1 = matrixBuffer1;
        matPtr2 = matrixBuffer2;
        fsValue = *(undefined2 *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x10); // thread-local storage value
        
        blendFactorA = (float)dVar4;
        funcTable = &PTR_LAB_00e3839c; // global function table
        callbackResult = -1;
        unused1 = 0xffffffff;
        unused2 = 0;
        unused3 = 0;
        unusedFloat = fVar5;
        blendFactorB = fVar1;
        stateComponentBase = iVar3;
        
        // Post callback (likely event/scheduler)
        FUN_0049f960(FUN_0049ead0, &funcTable);
        
        if (callbackResult != -1) {
            *(undefined4 *)(DAT_012234d0 + 0x43098) = 0; // clear flag
            uVar8 = FUN_0066ea80(iVar3, unusedFloat, blendFactorA, &scaleFactor); // spawn effect/handle
            *(undefined4 *)(unaff_ESI + 0xd0) = uVar8; // store handle
        }
        
        if (*(int *)(unaff_ESI + 0xd0) != 0) {
            // Set up a state callback for the handle
            if (*(int *)(unaff_ESI + 0x124) == 0) {
                iVar2 = 0;
            }
            else {
                iVar2 = *(int *)(unaff_ESI + 0x124) + -4;
            }
            *(undefined1 **)(iVar2 + 0xa8) = &LAB_0051f860; // set function pointer
            FUN_0049f960(&LAB_00524c50, *(undefined4 *)(unaff_ESI + 0xd0)); // post another callback
        }
    }
    return;
}