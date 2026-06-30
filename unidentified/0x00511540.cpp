// FUN_00511540: CharacterAnimController::blendBoneTransform

void CharacterAnimController::blendBoneTransform(int boneIndex, int* blendSourceArray, int destTransform, int flags)
{
    float* pfVar2;
    float* pfVar3;
    char boneAxisIndex;
    int iVar5;
    float fVar6, fVar7, fVar8, fVar9, fVar10, fVar11, fVar12;
    float fCosAngle, fSinAngle;
    undefined4 uVar13, uVar14;
    int* piVar17;
    uint uVar18, uVar19;
    int iVar20;
    float blendFactor = in_XMM0_Da; // passed in XMM0
    float tempQuat[4];
    undefined4 outQuatW; // +0xE2B1A4 constant likely 0
    undefined4 uStack_5c, uStack_58; // for quaternion components
    undefined1 local_50[76]; // unused buffer

    // Thread-local storage access (per-thread data)
    iVar5 = **(int**)(__readfsdword(0x2c) + 0x2c); // thread-local current task pointer

    // Calculate address in blend source array (each entry 0x50 bytes)
    int srcAddr = boneIndex * 0x50 + *blendSourceArray + *(int*)(iVar5 + 8);
    // Profiling enter/leave
    FUN_00414aa0();
    outQuatW = DAT_00e2b1a4; // likely identity w component (0.0f for quaternion?)
    FUN_00414aa0();

    piVar17 = (int*)(this + 0x24); // pointer to animation state structure
    tempQuat[3] = (float)outQuatW;
    FUN_0050a940(blendSourceArray); // acquire lock or similar

    iVar20 = *piVar17; // dereference to get animation state
    if ((*(uint*)(iVar20 + 0x108) & 0x4000) == 0) {
        // Standard blending path
        boneAxisIndex = *(char*)(iVar20 + 0x157); // axis index (0-3)
        // Extract nibbles from constant 0x21 to determine which axes to blend
        uVar19 = (0x21 >> (boneAxisIndex * 4)) & 0xF;
        uVar18 = (0x21 >> (uVar19 * 4)) & 0xF;

        if ((*(byte*)(iVar20 + 0x104) & 2) == 0) {
            // Simple axis setting (no blending)
            tempQuat[boneAxisIndex] = blendFactor;
            tempQuat[uVar19] = 0.0f;
            tempQuat[uVar18] = 0.0f;
            // Set transform from three floats (maybe Euler angles)
            FUN_0056b8a0(tempQuat[1], tempQuat[0], tempQuat[2]); // order likely X,Y,Z
        } else {
            // Full quaternion blending (slerp-like)
            fCosAngle = (float)((double)blendFactor); // cos(angle)?
            FUN_00b99fcb(); // likely cosf
            fSinAngle = (float)((double)blendFactor); // sin(angle)?
            FUN_00b99e20(); // likely sinf

            // Copy source quaternion (boneAxisIndex offset)
            int iVar15 = boneAxisIndex * 0x10;
            uVar24 = *(undefined4*)(destTransform + iVar15 + 0);
            uVar13 = *(undefined4*)(destTransform + iVar15 + 4);
            uVar14 = *(undefined4*)(destTransform + iVar15 + 8);
            *(undefined4*)(resultTransform + iVar15 + 0) = uVar24;
            *(undefined4*)(resultTransform + iVar15 + 4) = uVar13;
            *(undefined4*)(resultTransform + iVar15 + 8) = uVar14;
            *(undefined4*)(resultTransform + iVar15 + 12) = *(undefined4*)(destTransform + iVar15 + 12);

            // Blend first axis (uVar19)
            iVar15 = uVar18 * 0x10; // note: uVar18 used as index? Actually there is uVar18 and uVar19 mix-up in decompile. Correct based on code.
            pfVar2 = (float*)(destTransform + iVar15);
            fVar6 = *pfVar2;
            fVar7 = pfVar2[1];
            fVar8 = pfVar2[2];
            fVar9 = pfVar2[3];
            iVar20 = uVar19 * 0x10;
            pfVar2 = (float*)(resultTransform + iVar20);
            *pfVar2 = fCosAngle * fVar6;
            pfVar2[1] = fCosAngle * fVar7;
            pfVar2[2] = fCosAngle * fVar8;
            pfVar2[3] = fCosAngle * fVar9;

            // Blend second axis (uVar19) combined with first (uVar18)
            pfVar2 = (float*)(destTransform + iVar20);
            fVar10 = pfVar2[1];
            fVar11 = pfVar2[2];
            fVar12 = pfVar2[3];
            pfVar3 = (float*)(resultTransform + iVar20);
            *pfVar3 = fSinAngle * *pfVar2 + fCosAngle * fVar6;
            pfVar3[1] = fSinAngle * fVar10 + fCosAngle * fVar7;
            pfVar3[2] = fSinAngle * fVar11 + fCosAngle * fVar8;
            pfVar3[3] = fSinAngle * fVar12 + fCosAngle * fVar9;

            // Blend third axis (uVar18)
            pfVar2 = (float*)(destTransform + iVar15);
            fVar6 = *pfVar2;
            fVar7 = pfVar2[1];
            fVar8 = pfVar2[2];
            fVar9 = pfVar2[3];
            fCosAngle = DAT_00e44564 - fCosAngle; // 1.0f - cosAngle
            pfVar2 = (float*)(resultTransform + iVar15);
            *pfVar2 = fSinAngle * fVar6;
            pfVar2[1] = fSinAngle * fVar7;
            pfVar2[2] = fSinAngle * fVar8;
            pfVar2[3] = fSinAngle * fVar9;

            // Blend third axis combined with second (uVar19)
            pfVar2 = (float*)(destTransform + iVar20);
            fVar10 = pfVar2[1];
            fVar11 = pfVar2[2];
            fVar12 = pfVar2[3];
            pfVar3 = (float*)(resultTransform + iVar15);
            *pfVar3 = fCosAngle * *pfVar2 + fSinAngle * fVar6;
            pfVar3[1] = fCosAngle * fVar10 + fSinAngle * fVar7;
            pfVar3[2] = fCosAngle * fVar11 + fSinAngle * fVar8;
            pfVar3[3] = fCosAngle * fVar12 + fSinAngle * fVar9;
        }
    } else {
        // Lerp mode for position (flag 0x4000)
        tempQuat[0] = (*(float*)(srcAddr + 0x30) - tempQuat[0]) * _DAT_00e2e084 + tempQuat[0];
        tempQuat[1] = (*(float*)(srcAddr + 0x34) - tempQuat[1]) * _DAT_00e2e084 + tempQuat[1];
        tempQuat[2] = (*(float*)(srcAddr + 0x38) - tempQuat[2]) * _DAT_00e2e084 + tempQuat[2];
        FUN_0050fe90(piVar17, blendFactor); // blend position
    }

    // If animation type is 0x04 and has control flag, do alternative transform copy
    if ((*(char*)(this + 0x5b) == '\x04') &&
        ((*(byte*)(*(int*)(this + 0x10) + *(int*)(iVar5 + 8)) & 4) != 0)) {
        FUN_0056b420(destTransform, &local_60, resultTransform + 0x30);
    } else {
        // Copy local quaternion to result
        *(undefined4*)(resultTransform + 0x30) = local_60;
        *(undefined4*)(resultTransform + 0x34) = uStack_5c;
        *(undefined4*)(resultTransform + 0x38) = uStack_58;
        *(undefined4*)(resultTransform + 0x3c) = outQuatW;
    }

    // If extra processing requested and animation state has certain flags
    if ((flags != 0) && ((*(uint*)(*piVar17 + 0x10c) & 0x180000) != 0)) {
        // Apply mask and reset some transform components
        FUN_004eb6a0(resultTransform + 0x30, *(uint*)(*piVar17 + 0x10c) >> 0x14 & 0xffffff01);
        FUN_0056b230(local_50);
        *(undefined4*)(resultTransform + 0xc) = 0;
        *(undefined4*)(resultTransform + 0x1c) = 0;
        *(undefined4*)(resultTransform + 0x2c) = 0;
    }
    return;
}