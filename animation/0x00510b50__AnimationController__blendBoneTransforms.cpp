// FUNC_NAME: AnimationController::blendBoneTransforms
// Function address: 0x00510b50
// Role: Blends bone transformation matrices (rotation/position) from animation data.
// Uses sin/cos interpolation for quaternion-based blending and additive layers.

void __thiscall AnimationController::blendBoneTransforms(void *this, void *matrixData, void *param3, void *outputMatrices)
{
    // Thread-local storage base pointer (used for security cookie / global data)
    int *fsBase = *(int **)(*(uint *)(&__security_cookie) + 0x2c); 
    // Actually FS:0x2c -> thread local storage pointer
    int *globalPtr = *(int **)((char*)fsBase + 0x2c); // ?? might be global animation manager

    // Lock animation data (critical section)
    lockAnimationData(); // FUN_00414aa0
    undefined4 *puVar1;
    char cVar2;
    int iVar3;
    float fVar4, fVar5, fVar6, fVar7, fVar8, fVar9;
    undefined4 uVar10, uVar11;
    bool bVar12 = false;
    uint uVar13, uVar20;
    byte* pbVar14;
    int iVar15, iVar16;
    undefined4 *puVar17;
    float *pfVar18, *pfVar19;
    float fVar21, fVar22, fVar23, fVar25;
    double dVar24;
    undefined4 uVar27 = 0;
    undefined *in_XMM0_Da; // Actually float from XMM register, passed in?

    // Get pointer to animation control block
    iVar15 = *(int *)((int)this + 0x10); // this->animControlBlock

    // Check flags for blend type
    if ((*(uint *)(iVar15 + 0x108) & 0x4000) == 0) 
    {
        // Type B: not root motion? Check another flag
        if ((*(uint *)(iVar15 + 0x10c) & 0x80000) != 0) 
        {
            // Use velocity/position from entity
            iVar15 = getEntityComponent(); // FUN_004e9fa0
            iVar15 = *(int *)((uint)(*(int *)((int)globalPtr + 0x34) != 0) * 0x98 + 0xc + iVar15);
            // Get position/rotation from entity
            in_XMM0_Da = *(undefined **)(iVar15 + 0x60); // maybe blend weight
            local_80 = in_XMM0_Da; // Actually a float vector (x,y,z) - reinterpret?
            fStack_7c = *(float *)(iVar15 + 100);
            fStack_78 = *(float *)(iVar15 + 0x68);
            uStack_74 = *(undefined4 *)(iVar15 + 0x6c);
        }
    }
    else 
    {
        // Type A: root motion flag set
        fVar21 = local_68 * local_68 + (float)local_70 * (float)local_70 + (float)local_6c * (float)local_6c;
        if (fVar21 <= kZeroThreshold) // DAT_00e2cbe0 (likely 0.0f)
        {
            fStack_7c = 0.0f;
            fVar21 = 0.0f;
        }
        else 
        {
            fVar21 = sqrtf(fVar21); // SQRT
            fStack_7c = kOneFloat / fVar21; // Reciprocal? Actually DAT_00e2b1a4 = 1.0f?
        }
        local_80 = (undefined *)((float)local_70 * fStack_7c); // Normalize?
        fStack_78 = local_68 * fStack_7c;
        fStack_7c = fStack_7c * (float)local_6c;
        uStack_74 = 0;
        in_XMM0_Da = kSomeFloatPtr; // PTR_FUN_00e4462c (maybe 0.0f?)
        if (fVar21 < *(float*)kSomeFloatPtr) 
        {
            fStack_78 = 0.0f;
            fStack_7c = 0.0f;
            local_80 = (undefined *)0x0;
            char boneIdx = *(char *)(iVar15 + 0x157); // bone index
            (&local_80)[boneIdx] = (undefined *)kOneFloat; // Maybe set one component?
        }
    }
    bVar12 = true;

    // Common code after flag check
LAB_00510c9e:
    computeWorldTransform(matrixData); // FUN_0050a940

    if (bVar12) 
    {
        // Initialize output matrix to identity? Set translation to zero
        fStack_4c = 0.0f;
        uStack_48 = 0;
        uStack_44 = 0;
        local_40 = 0.0f;
        uStack_38 = 0;
        uStack_34 = 0;
        local_30 = 0;
        uStack_2c = 0;
        uStack_24 = 0;
        dVar24 = (double)(float)in_XMM0_Da; // Blend factor
        local_50 = kOneFloat;
        puStack_3c = kOneFloat;
        puStack_28 = kOneFloat;
        sinf((float)dVar24); // FUN_00b99fcb - likely sin
        fStack_4c = (float)dVar24; // sin value
        dVar24 = (double)(float)in_XMM0_Da;
        cosf((float)dVar24); // FUN_00b99e20 - likely cos
        local_40 = kOneMinusSin; // DAT_00e44564 - fStack_4c; (1 - sin)
        uVar27 = 0;
        local_50 = (undefined *)(float)dVar24; // cos?
        local_70 = (undefined *)0x0;
        local_6c = kOneFloat;
        local_68 = 0.0f;
        local_64 = 0;
        if (kSomeThreshold <= (float)((uint)fStack_7c & kMask)) { // DAT_00e44854, DAT_00e44680
            local_70 = kOneFloat;
        }
        puStack_3c = local_50;
        buildTransformFromQuaternion(&local_80, &local_70, outputMatrices); // FUN_0056c6b0
        blendMatrices(&local_50, outputMatrices, outputMatrices, 3); // FUN_0056b230 - blend?
        // zero out translation components (row 0 col 3, row 1 col 3, row 2 col 3)
        *(undefined4 *)((int)outputMatrices + 0xc) = uVar27;
        *(undefined4 *)((int)outputMatrices + 0x1c) = uVar27;
        *(undefined4 *)((int)outputMatrices + 0x2c) = uVar27;

        if ((*(byte *)(*(int *)((int)this + 0x10) + 0x104) & 2) != 0) 
        {
            // Additive blend layer
            int additivePtr = *(int *)((int)this + 8) + 0x50 + (int)globalPtr + 8; // globalPtr+8? Actually *(int*)(iVar3+8)
            blendMatrices(outputMatrices, additivePtr, outputMatrices, 3); // FUN_0056b230
            *(undefined4 *)((int)outputMatrices + 0xc) = uVar27;
            *(undefined4 *)((int)outputMatrices + 0x1c) = uVar27;
            *(undefined4 *)((int)outputMatrices + 0x2c) = uVar27;
        }
    }
    else 
    {
        // More complex blend using bone indices and sin/cos interpolation
        iVar15 = *(int *)((int)this + 0x10);
        cVar2 = *(char *)(iVar15 + 0x157); // bone index 0? Actually some byte used as index
        uVar13 = (0x21 >> (cVar2 * 4 & 0x1f)) & 0xf;
        uVar20 = (0x21 >> ((char)uVar13 * 4 & 0x1f)) & 0xf;

        if ((*(byte *)(iVar15 + 0x104) & 2) == 0) 
        {
            computeMatrixFromPose(in_XMM0_Da); // FUN_0056bf40
        }
        else 
        {
            double sinVal, cosVal;
            sinVal = (double)(float)in_XMM0_Da;
            sinf((float)sinVal); // FUN_00b99fcb
            fVar22 = (float)sinVal; // sin
            cosVal = (double)(float)in_XMM0_Da;
            cosf((float)cosVal); // FUN_00b99e20
            fVar25 = (float)cosVal; // cos

            // Calculate source matrix pointer based on bone index
            int srcIdx = (cVar2 + 5) * 0x10;
            int baseAddr = *(int *)((int)this + 8) + (int)globalPtr + 8; // Actually *(int*)(iVar3+8)
            undefined4 *srcMat = (undefined4 *)(srcIdx + baseAddr);
            uVar27 = srcMat[1];
            uVar10 = srcMat[2];
            uVar11 = srcMat[3];
            undefined4 *dstMat = (undefined4 *)(cVar2 * 0x10 + (int)outputMatrices);
            dstMat[0] = srcMat[0];
            dstMat[1] = uVar27;
            dstMat[2] = uVar10;
            dstMat[3] = uVar11;

            // Second bone (uVar13)
            int srcIdx2 = (uVar20 + 5) * 0x10;
            float *srcMat2 = (float *)(baseAddr + srcIdx2);
            fVar21 = srcMat2[0];
            fVar4 = srcMat2[1];
            fVar5 = srcMat2[2];
            fVar6 = srcMat2[3];
            float *dstMat2 = (float *)(uVar13 * 0x10 + (int)outputMatrices);
            dstMat2[0] = fVar22 * fVar21;
            dstMat2[1] = fVar22 * fVar4;
            dstMat2[2] = fVar22 * fVar5;
            dstMat2[3] = fVar22 * fVar6;

            // Third bone (uVar13+5)
            int srcIdx3 = (uVar13 + 5) * 0x10;
            float *srcMat3 = (float *)(baseAddr + srcIdx3);
            fVar7 = srcMat3[1];
            fVar8 = srcMat3[2];
            fVar9 = srcMat3[3];
            dstMat2[0] = srcMat3[0] * fVar25 + fVar22 * fVar21;
            dstMat2[1] = fVar7 * fVar25 + fVar22 * fVar4;
            dstMat2[2] = fVar8 * fVar25 + fVar22 * fVar5;
            dstMat2[3] = fVar9 * fVar25 + fVar22 * fVar6;

            // Fourth bone (uVar20)
            float *srcMat4 = (float *)(baseAddr + srcIdx2); // reusing same pointer?
            float *dstMat3 = (float *)(uVar20 * 0x10 + (int)outputMatrices);
            fVar21 = srcMat4[0];
            fVar4 = srcMat4[1];
            fVar5 = srcMat4[2];
            fVar6 = srcMat4[3];
            dstMat3[0] = fVar21 * fVar25;
            dstMat3[1] = fVar4 * fVar25;
            dstMat3[2] = fVar5 * fVar25;
            dstMat3[3] = fVar6 * fVar25;

            float blendRemain = kOneFloat - fVar22; // DAT_00e44564 = 1.0f
            float *srcMat5 = (float *)(baseAddr + srcIdx3);
            fVar7 = srcMat5[1];
            fVar8 = srcMat5[2];
            fVar9 = srcMat5[3];
            dstMat3[0] = blendRemain * srcMat5[0] + fVar21 * fVar25;
            dstMat3[1] = blendRemain * fVar7 + fVar4 * fVar25;
            dstMat3[2] = blendRemain * fVar8 + fVar5 * fVar25;
            dstMat3[3] = blendRemain * fVar9 + fVar6 * fVar25;
        }
    }

    // Final step: check flag for additive blending
    pbVar14 = (byte *)(*(int *)((int)this + 8) + (int)globalPtr + 8); // actually *(int*)(iVar3+8)
    if ((*pbVar14 & 4) != 0) 
    {
        additiveBlendMatrix(pbVar14 + 0x50, &local_60, (unsigned int)outputMatrices + 0x30); // FUN_0056b420
        return;
    }
    // Copy matrix to output (four floats)
    *(undefined4 *)((int)outputMatrices + 0x30) = local_60;
    *(undefined4 *)((int)outputMatrices + 0x34) = uStack_5c;
    *(undefined4 *)((int)outputMatrices + 0x38) = uStack_58;
    *(undefined **)((int)outputMatrices + 0x3c) = puStack_54;
    return;
}