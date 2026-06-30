// FUNC_NAME: SkinDeformer::blendBoneMatrices

void SkinDeformer::blendBoneMatrices(void* thisObj, int* boneMatrixArray, int boneIndex)
{
    int* piVar1;
    float* pfVar2;
    float* pfVar3;
    int iVar4;
    float fVar5, fVar6, fVar7, fVar8;
    float fVar9, fVar10, fVar11;
    int iVar14;
    uint uVar15, uVar20;
    byte* pbVar16;
    float* pfVar17, * pfVar19;
    int iVar18;
    float fVar21, fVar22, fVar25;
    double dVar23;
    float local_weights[4]; // local_70, 4 floats - probably bone weights
    // The next 4 undefined4 are likely a temporary matrix (local_60, uStack_5c, uStack_58, uStack_54)
    // Actually the code manipulates them as part of matrix copy
    float tmpMatrix[4][4]; // represents local_60, uStack_5c, uStack_58, uStack_54
    byte local_50[76]; // unused blob maybe stack padding

    // Thread-local storage base (FS segment offset 0x2c -> often TIB)
    iVar4 = **(int**)(__readfsdword(0x2c) + 0x2c); // GetTLS base?
    // Compute pointer to input bone matrix from the array
    iVar14 = boneIndex * 0x50 + *boneMatrixArray + *(int*)(iVar4 + 8);

    // Call some subroutines (likely stack setup / context save)
    FUN_00414aa0(); // unknown setup
    // Load global constant (likely identity matrix's last column or some default)
    tmpMatrix[3][0] = *(float*)&DAT_00e2b1a4; // uStack_54 = DAT_00e2b1a4
    // Actually the decompiler shows uStack_54 = DAT_00e2b1a4 and later used as 4th row?
    // The matrix copy later: *(undefined4*)(unaff_EDI+0x30)=local_60 etc.
    // So local_60..uStack_54 form a 4x4 matrix stored horizontally.
    // For simplicity treat as float mat[4][4].

    FUN_00414aa0();
    // local_weights[3] set to the global float (probably w component)
    local_weights[3] = *(float*)&DAT_00e2b1a4;

    // Call function with boneMatrixArray parameter (maybe get current frame data)
    FUN_0050a940(boneMatrixArray);

    // Get pointer to thisObj+0x10 (likely a pointer to another object, e.g., animState)
    piVar1 = (int*)((char*)thisObj + 0x10);
    iVar18 = *piVar1; // deref to get object pointer

    // Check flag at iVar18+0x108 bit 0x4000 (14th bit). If not set, use blend path A.
    if ((*(uint*)(iVar18 + 0x108) & 0x4000) == 0) {
        // --- Blend path A: weighted matrix blending using bone weight indices ---
        // Extract three bone indices from a byte at iVar18+0x157
        iVar14 = (int)*(char*)(iVar18 + 0x157); // first bone index
        // Compute second bone index via some bit manipulation (likely from a table)
        uVar15 = 0x21 >> ((*(char*)(iVar18 + 0x157) * 4) & 0x1f) & 0xf;
        // Compute third bone index
        uVar20 = 0x21 >> ((uVar15 * 4) & 0x1f) & 0xf;

        // Check another flag at iVar18+0x104 bit 2
        if ((*(byte*)(iVar18 + 0x104) & 2) == 0) {
            // Simple case: set weight for first bone to input, others to 0
            local_weights[iVar14] = in_XMM0_Da; // interpolation factor from XMM0
            local_weights[uVar15] = 0.0f;
            local_weights[uVar20] = 0.0f;
            // Call function to apply these weights (probably transform bone?)
            FUN_0056b8a0(local_weights[1], local_weights[0], local_weights[2]);
        } else {
            // Weighted blend case: use two interpolation factors (fVar21 and fVar25)
            dVar23 = (double)in_XMM0_Da;
            FUN_00b99fcb(); // some math function (maybe sin/cos?)
            fVar21 = (float)dVar23; // first weight
            dVar23 = (double)in_XMM0_Da;
            FUN_00b99e20(); // another math function
            fVar25 = (float)dVar23; // second weight

            // Get pointer to bone matrix for first index (iVar14) from the input array
            puVar2 = (float*)((iVar14 + 5) * 0x10 + *(int*)((char*)thisObj + 8) + *(int*)(iVar4 + 8));
            // Copy that matrix to temporary storage (pointed to by unaff_EDI? Actually unaff_EDI is a local register)
            // For clarity, we assume unaff_EDI points to an output matrix
            // Copy 4 floats from puVar2 to unaff_EDI + iVar14*0x10
            float* destMat = (float*)((char*)unaff_EDI + iVar14 * 0x10);
            destMat[0] = puVar2[0];
            destMat[1] = puVar2[1];
            destMat[2] = puVar2[2];
            destMat[3] = puVar2[3];

            // Now process second bone (uVar15) with weight fVar21
            // Get its input matrix from the array (index uVar15+5)
            pfVar17 = (float*)((char*)thisObj + 8 + (uVar20 + 5) * 0x10 + *(int*)(iVar4 + 8)); // Wait, this is for uVar20? Let's re-read decomp.
            // Actually the decomp shows: iVar14 = (uVar20 + 5) * 0x10; pfVar17 = *(int*)(thisObj+8) + iVar14 + *(int*)(iVar4+8);
            // Then it loads 4 floats from pfVar17 and stores scaled version to unaff_EDI+uVar15*0x10 with factor fVar21.

            // To avoid confusion, I'll reconstruct step by step with clearer names:
            float* srcMat2 = (float*)(*(int*)((char*)thisObj + 8) + (uVar20 + 5) * 0x10 + *(int*)(iVar4 + 8));
            float s0 = srcMat2[0];
            float s1 = srcMat2[1];
            float s2 = srcMat2[2];
            float s3 = srcMat2[3];
            // Store scaled by fVar21 into output for index uVar15
            float* outMat2 = (float*)((char*)unaff_EDI + uVar15 * 0x10);
            outMat2[0] = fVar21 * s0;
            outMat2[1] = fVar21 * s1;
            outMat2[2] = fVar21 * s2;
            outMat2[3] = fVar21 * s3;

            // Then blend with another matrix from index (uVar15+5) using fVar25
            float* srcMat3 = (float*)(*(int*)((char*)thisObj + 8) + (uVar15 + 5) * 0x10 + *(int*)(iVar4 + 8));
            fVar9 = srcMat3[1]; fVar10 = srcMat3[2]; fVar11 = srcMat3[3];
            // Add weighted contribution to existing outMat2
            outMat2[0] = srcMat3[0] * fVar25 + outMat2[0];
            outMat2[1] = fVar9 * fVar25 + outMat2[1];
            outMat2[2] = fVar10 * fVar25 + outMat2[2];
            outMat2[3] = fVar11 * fVar25 + outMat2[3];

            // Next, process third bone (uVar20) with weight fVar25 and also blend another matrix
            // Get its input matrix from array (index uVar20+5)
            srcMat2 = (float*)(*(int*)((char*)thisObj + 8) + (uVar20 + 5) * 0x10 + *(int*)(iVar4 + 8));
            s0 = srcMat2[0]; s1 = srcMat2[1]; s2 = srcMat2[2]; s3 = srcMat2[3];
            // Store scaled by fVar25 into output for index uVar20
            float* outMat3 = (float*)((char*)unaff_EDI + uVar20 * 0x10);
            outMat3[0] = s0 * fVar25;
            outMat3[1] = s1 * fVar25;
            outMat3[2] = s2 * fVar25;
            outMat3[3] = s3 * fVar25;

            // Then blend with another matrix from index (uVar15+5) using (1-fVar21) ??? Actually fVar22 = DAT_00e44564 - fVar21
            fVar22 = *(float*)&DAT_00e44564 - fVar21; // global constant minus fVar21
            float* srcMat4 = (float*)(*(int*)((char*)thisObj + 8) + (uVar15 + 5) * 0x10 + *(int*)(iVar4 + 8));
            fVar9 = srcMat4[1]; fVar10 = srcMat4[2]; fVar11 = srcMat4[3];
            outMat3[0] = fVar22 * srcMat4[0] + s0 * fVar25;
            outMat3[1] = fVar22 * fVar9 + s1 * fVar25;
            outMat3[2] = fVar22 * fVar10 + s2 * fVar25;
            outMat3[3] = fVar22 * fVar11 + s3 * fVar25;
        }
    } else {
        // --- Blend path B: Linear interpolation of position/rotation values ---
        // Interpolate between current stored values and new target values using global slerp factor
        local_weights[0] = (*(float*)(iVar14 + 0x30) - local_weights[0]) * *(float*)&_DAT_00e2e084 + local_weights[0];
        local_weights[1] = (*(float*)(iVar14 + 0x34) - local_weights[1]) * *(float*)&_DAT_00e2e084 + local_weights[1];
        local_weights[2] = (*(float*)(iVar14 + 0x38) - local_weights[2]) * *(float*)&_DAT_00e2e084 + local_weights[2];
        // Call another function to apply interpolation to bone matrix?
        FUN_0050fe90(piVar1, in_XMM0_Da);
    }

    // After blending, check condition based on a byte at thisObj+0x70
    if ((*(char*)((char*)thisObj + 0x70) == 4) &&
        (pbVar16 = (byte*)(*(int*)(iVar4 + 8) + *(int*)((char*)thisObj + 8)), (*pbVar16 & 4) != 0)) {
        // Special case: call matrix conversion function
        FUN_0056b420(pbVar16 + 0x50, &tmpMatrix, (float*)unaff_EDI + 0x30); // +0x30 offset in output
    } else {
        // Default: copy the temporary matrix to output at unaff_EDI+0x30
        *(float*)((char*)unaff_EDI + 0x30) = tmpMatrix[0][0];
        *(float*)((char*)unaff_EDI + 0x34) = tmpMatrix[0][1]; // Note: uStack_5c corresponds to mat[0][1]? Actually layout is mat[0][0], mat[0][1], mat[0][2], mat[0][3]?
        *(float*)((char*)unaff_EDI + 0x38) = tmpMatrix[0][2];
        *(float*)((char*)unaff_EDI + 0x3c) = tmpMatrix[0][3]; // uStack_54
    }

    // Check another flag for final cleanup
    if ((*(uint*)(*piVar1 + 0x10c) & 0x180000) != 0) {
        FUN_004e9fa0(); // unknown
        FUN_004eb6a0((float*)unaff_EDI + 0x30, *(uint*)(*piVar1 + 0x10c) >> 0x14 & 0xffffff01);
        FUN_0056b230(local_50);
        // Zero out some fields in output
        *(int*)((char*)unaff_EDI + 0xc) = 0;
        *(int*)((char*)unaff_EDI + 0x1c) = 0;
        *(int*)((char*)unaff_EDI + 0x2c) = 0;
    }
    return;
}