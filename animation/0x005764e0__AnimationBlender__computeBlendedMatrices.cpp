// FUNC_NAME: AnimationBlender::computeBlendedMatrices
void AnimationBlender::computeBlendedMatrices(int param_2) {
    float fVar1, fVar2, fVar3, fVar4;
    short sVar5;
    ushort uVar6;
    int *piVar7;
    uint uVar8;
    int iVar9;
    float *pfVar10;
    bool bVar11;
    bool bVar12;
    float fVar13;
    int *piVar14;
    uint uVar15;
    int *piVar16;
    int iVar17;
    int iVar18;
    float *pfVar19;
    int iVar20;
    float fVar21;
    float *local_218;
    int local_214;
    float *local_20c;
    uint local_200;
    int local_1e8;
    float *local_1e4;
    int local_1d8;
    char *local_1c8;
    float *local_1c4;
    float local_e0;
    float fStack_dc;
    float fStack_d8;
    float fStack_d4;
    float local_c0[4];
    undefined4 local_b0;
    undefined4 local_ac;
    undefined4 local_a8;
    float local_a4;
    float local_a0;
    int iStack_9c;
    int iStack_98;
    int iStack_94;
    int local_90;
    float fStack_8c;
    int iStack_88;
    int iStack_84;
    int local_80;
    int iStack_7c;
    float fStack_78;
    int iStack_74;
    int local_70;
    int iStack_6c;
    int iStack_68;
    float fStack_64;
    float local_60;
    int iStack_5c;
    int iStack_58;
    int iStack_54;

    // Get skeleton data (offset +0x70)
    iVar18 = *(int *)(this + 0x70);
    if ((((iVar18 == 0) || (*(int *)(iVar18 + 0x18) < 1)) || (*(int *)(iVar18 + 0x1c) == 0)) ||
        ((sVar5 = *(short *)(this + 0x76), sVar5 < 0 || (*(int *)(iVar18 + 0x18) <= (int)sVar5)))) {
        iVar18 = 0;
    }
    else {
        iVar18 = *(int *)(iVar18 + 0x1c) + sVar5 * 0x18;
    }

    // PiVar7 points to an array of bone descriptor structures (each 0x10 bytes)
    piVar7 = *(int **)(iVar18 + 0xc);

    // Initialize stack vectors to zero (identity quaternion/translation)
    iStack_9c = 0;
    iStack_98 = 0;
    iStack_94 = 0;
    local_60 = DAT_00e2b1a4; // likely 1.0f (identity quaternion w)
    iStack_5c = 0;
    iStack_58 = 0;
    iStack_54 = 0;
    local_90 = 0;
    iStack_88 = 0;
    iStack_84 = 0;
    local_1c8 = (char *)(*(int *)(param_2 + 0x34) + 0x15); // stream pointer for bone commands?
    local_80 = 0;
    iStack_7c = 0;
    iStack_74 = 0;
    local_1c4 = (float *)(*(int *)(param_2 + 0x38) + 0x30); // pointer to per-bone transform data?
    uVar8 = *(uint *)(iVar18 + 8); // number of bones in this animation
    local_70 = 0;
    iStack_6c = 0;
    iStack_68 = 0;
    fStack_64 = DAT_00e2b1a4; // identity w
    local_a0 = *(float *)(this + 0x104); // start scale? (actually a quaternion component?)
    iVar17 = uVar8 * 2;

    // If bone remap table exists, find max bone index
    if (*(int *)(this + 0xb4) != 0) {
        local_218 = (float *)0x0;
        local_200 = uVar8;
        if (0 < (int)uVar8) {
            do {
                uVar15 = (uint)*(byte *)(*(int *)(this + 0xb4) + (int)local_218);
                if ((uVar15 != 0xff) && ((int)local_200 < (int)uVar15)) {
                    local_200 = uVar15;
                }
                local_218 = (float *)((int)local_218 + 1);
            } while ((int)local_218 < (int)uVar8);
        }
        iVar17 = local_200 * 2 + 2;
    }

    fStack_8c = local_a0;
    fStack_78 = local_a0;

    // Allocate memory for output matrices (aligned to 0x10 bytes?)
    piVar14 = (int *)FUN_0056ef10(((iVar17 + 1) * 0x10) / 0xc);

    // Initialize identity quaternion (0,0,0,1)
    local_c0[2] = 0.0f;
    local_c0[1] = 0.0f;
    local_c0[0] = 0.0f;
    local_c0[3] = DAT_00e2b1a4; // 1.0f

    // Also identity matrix? (local_b0..local_a4)
    local_a8 = 0;
    local_ac = 0;
    local_b0 = 0;
    local_a4 = DAT_00e2b1a4;

    iVar17 = *(int *)(*(int *)(param_2 + 0x38) + 0xc); // some count from animation stream?
    local_1d8 = 0;
    bVar12 = false;
    local_200 = 1; // start from bone index 1? (skip root?)

    if (1 < *(int *)(iVar18 + 8)) {
        local_218 = (float *)(piVar14 + 0x14); // offset 0x50 in piVar14? (matrix start?)
        fVar21 = DAT_00e2b04c; // likely 2.0f? (constant for matrix computation)

        // Loop over bones (index from 1 to max)
        do {
            iVar20 = *(int *)(this + 0xb4); // bone remap table
            pfVar19 = local_218;
            if ((iVar20 != 0) && (*(byte *)(iVar20 + local_200) != 0xff)) {
                // If remapped, get pointer to actual bone transform data
                pfVar19 = (float *)((uint)*(byte *)(iVar20 + local_200) * 0x40 + *(int *)(this + 0xb8));
            }

            iVar9 = piVar7[4]; // seems to be a bone index from the animation descriptor
            if (iVar9 == 0) {
                // Copy identity (scale/translation) into output
                local_1e4 = (float *)(piVar14 + 4);
                *local_1e4 = local_a0;
                piVar14[5] = iStack_9c;
                piVar14[6] = iStack_98;
                piVar14[7] = iStack_94;
                piVar14[8] = local_90;
                piVar14[9] = (int)fStack_8c;
                piVar14[10] = iStack_88;
                piVar14[11] = iStack_84;
                piVar14[12] = local_80;
                piVar14[13] = iStack_7c;
                piVar14[14] = (int)fStack_78;
                piVar14[15] = iStack_74;
                piVar14[16] = local_70;
                piVar14[17] = iStack_6c;
                piVar14[18] = iStack_68;
                piVar14[19] = (int)fStack_64;
            }
            else if ((iVar20 == 0) || (*(byte *)(iVar9 + iVar20) == 0xff)) {
                // No remap, take directly from output array at index iVar9
                local_1e4 = (float *)(piVar14 + iVar9 * 0x10 + 4);
            }
            else {
                // Remapped input
                local_1e4 = (float *)((uint)*(byte *)(iVar9 + iVar20) * 0x40 + *(int *)(this + 0xb8));
            }

            iVar20 = piVar7[7]; // transformation type
            local_20c = local_c0;
            if (iVar20 == 2) {
                // use skeleton's local transform
                local_20c = (float *)(piVar7[5] * 0x20 + *(int *)(*(int *)(this + 0x70) + 0x58));
            }
            else if (((int)local_200 < iVar17) && (*local_1c8 == '\x02')) {
                if (iVar20 == 1) {
                    local_20c = local_1c4;
                }
                else if (iVar20 == 3) {
                    bVar12 = true;
                }
            }

            bVar11 = false;
            if (*(char *)(this + 0xae) == '\0') {
                // Non-dynamic path: compute matrix from quaternion
LAB_005770d9:
                fVar13 = DAT_00e2b1a4;
                fVar1 = local_20c[2];
                fVar2 = *local_20c;
                fVar3 = local_20c[1];
                fVar4 = local_20c[3];
                *pfVar19 = DAT_00e2b1a4 - (fVar3 * fVar3 + fVar1 * fVar1) * fVar21;
                pfVar19[4] = (fVar2 * fVar3 - fVar4 * fVar1) * fVar21;
                pfVar19[1] = (fVar4 * fVar1 + fVar2 * fVar3) * fVar21;
                pfVar19[5] = fVar13 - (fVar2 * fVar2 + fVar1 * fVar1) * fVar21;
                pfVar19[2] = (fVar2 * fVar1 - fVar4 * fVar3) * fVar21;
                pfVar19[3] = 0.0f;
                pfVar19[6] = (fVar1 * fVar3 + fVar2 * fVar4) * fVar21;
                pfVar19[7] = 0.0f;
                pfVar19[8] = (fVar4 * fVar3 + fVar2 * fVar1) * fVar21;
                pfVar19[9] = (fVar1 * fVar3 - fVar2 * fVar4) * fVar21;
                pfVar19[10] = fVar13 - (fVar3 * fVar3 + fVar2 * fVar2) * fVar21;
                pfVar19[0xb] = 0.0f;
                fVar1 = local_20c[5];
                fVar2 = local_20c[6];
                fVar3 = local_20c[7];
                pfVar19[0xc] = local_20c[4];
                pfVar19[0xd] = fVar1;
                pfVar19[0xe] = fVar2;
                pfVar19[0xf] = fVar3;
                pfVar19[0xf] = fVar13; // overwrite translation w with 1.0?
                FUN_00417560(); // likely matrix multiply/transform
            }
            else {
                // Dynamic (runtime) bone override path
                local_214 = local_1d8 * 0x20;
                piVar16 = (int *)(*(int *)(this + 0xa0) + local_214);
                if (*(short *)(this + 0xa8) <= local_1d8) goto LAB_005770d9;

                do {
                    if (local_200 != (int)(short)piVar16[1]) break;
                    uVar6 = *(ushort *)((int)piVar16 + 6);
                    if ((char)uVar6 < '\0') {
                        bVar11 = true;
                        // Various flag combinations determine matrix construction
                        if ((uVar6 & 1) == 0) {
                            // ... (similar quaternion to matrix conversion)
                        }
                        else {
                            // ... (another quaternion matrix pattern)
                        }
                    }
                    local_214 = local_214 + 0x20;
                    piVar16 = (int *)(*(int *)(this + 0xa0) + local_214);
                    local_1d8 = local_1d8 + 1;
                } while (local_1d8 < *(short *)(this + 0xa8));

                if (!bVar11) goto LAB_005770d9;
            }

            // Advance to next bone
            local_1c8 = local_1c8 + 1;
            local_1c4 = local_1c4 + 8;
            local_218 = local_218 + 0x10;
            local_200 = local_200 + 1;
            piVar7 = piVar7 + 4;
        } while ((int)local_200 < *(int *)(iVar18 + 8));
    }

    // Extra loop for additional transforms (quaternion blending?)
    local_1e8 = 0;
    if (0 < *(short *)(this + 0xaa)) {
        do {
            FUN_00417560();
            local_a0 = local_60;
            // Reset stack vectors to identity
            iStack_9c = iStack_5c;
            iStack_98 = iStack_58;
            iStack_94 = iStack_54;
            local_90 = iStack_54;
            fStack_8c = local_60;
            iStack_88 = iStack_54;
            iStack_84 = iStack_54;
            local_80 = iStack_54;
            iStack_7c = iStack_54;
            fStack_78 = local_60;
            iStack_74 = iStack_54;
            local_70 = iStack_54;
            iStack_6c = iStack_54;
            iStack_68 = iStack_54;
            fStack_64 = local_60;
            FUN_00414aa0();
            FUN_00417560();
            FUN_00417560();
            local_1e8 = local_1e8 + 1;
        } while (local_1e8 < *(short *)(this + 0xaa));
    }

    // Handle type 3 bones (special case)
    if (bVar12) {
        iVar17 = 1;
        if (1 < *(int *)(iVar18 + 8)) {
            iVar20 = *(int *)(iVar18 + 0xc) + 0x18;
            do {
                if (*(int *)(iVar20 + 4) == 3) {
                    FUN_00417560();
                }
                iVar17 = iVar17 + 1;
                iVar20 = iVar20 + 0x10;
            } while (iVar17 < *(int *)(iVar18 + 8));
        }
    }

    // Decrement reference count on allocated block (piVar14 is the header)
    *(char *)((int)piVar14 + 9) = *(char *)((int)piVar14 + 9) + -1;

    if (((char)piVar14[2] == '\0') && (*(char *)((int)piVar14 + 9) == '\0')) {
        // Deallocate from global free list
        iVar18 = *piVar14;
        piVar7 = (int *)piVar14[1];
        if (iVar18 != 0) {
            *(int **)(iVar18 + 4) = piVar7;
        }
        iVar17 = DAT_01205560;
        if (piVar7 == (int *)0x0) {
            *(undefined4 *)(DAT_01205560 + 8) = *(undefined4 *)(DAT_01205560 + 4);
            *(int *)(iVar17 + 4) = iVar18;
            DAT_0120557c = 0;
            if (iVar18 == 0) {
                *(undefined4 *)(iVar17 + 8) = *(undefined4 *)(iVar17 + 0xc);
                return;
            }
        }
        else {
            *piVar7 = iVar18;
        }
    }
    DAT_0120557c = 0;
    return;
}