// FUNC_NAME: CEAAnimationManager::ComputeBlendedSkinMatrices
// Function at 0x00574bd0: Computes blended skin matrices for animated meshes.
// Builds world matrices per bone from local transforms, applies blending weights, and outputs to temporary buffers.

void CEAAnimationManager::ComputeBlendedSkinMatrices(int param_1) // param_1: likely a bone transform container (e.g., BoneContext*)
{
    float fVar1, fVar2, fVar3, fVar4, fVar12, fVar13, fVar14, fVar15, fVar16, fVar17, fVar18;
    float fVar21, fVar31, fVar32, fVar33, fVar34, fVar35;
    short sVar5;
    ushort uVar6;
    uint uVar8, uVar25;
    int iVar9, iVar10, iVar26, iVar27, iVar29;
    float *pfVar11, *pfVar28, *pfVar30;
    bool bVar19, bVar20;
    int *piVar7, *piVar22, *piVar23, *piVar24;
    float *local_248, *local_250, *local_244, *local_208, *local_204;
    char *local_20c;
    int *local_264, *local_238;
    int local_260, local_230, local_1b0, local_214;
    float local_100, fStack_fc, fStack_f8, fStack_f4;
    float local_d0[4], local_b0, fStack_ac, fStack_a8, fStack_a4, local_a0;
    float local_104; // fVar21 stored as constant
    float fStack_7c, fStack_68, fStack_54;
    float fStack_fc2, fStack_f8_2;

    // Known constants
    fVar21 = DAT_00e2b1a4; // likely 1.0 or identity quaternion value
    fVar35 = DAT_00e2b04c; // likely 2.0 or scaling factor

    // Get bone list from param_1 (m_boneList at +0x70)
    iVar27 = *(int *)(param_1 + 0x70);
    // Validate bone list and current bone index (+0x76 is m_currentBoneIndex)
    if (((iVar27 == 0) || (*(int *)(iVar27 + 0x18) < 1)) || (*(int *)(iVar27 + 0x1c) == 0)) ||
       ((sVar5 = *(short *)(param_1 + 0x76), sVar5 < 0 || (*(int *)(iVar27 + 0x18) <= (int)sVar5)))) {
        iVar27 = 0;
    } else {
        // Get bone data for current bone index (bone size 0x18)
        iVar27 = *(int *)(iVar27 + 0x1c) + sVar5 * 0x18;
    }

    // Access member data: this->m_meshData (+0x3c), m_boneWeights (+0x38), m_boneIndices (+0x34)
    iVar29 = *(int *)(in_EAX + 0x3c);   // in_EAX is this (class context)
    piVar7 = *(int **)(iVar27 + 0xc);   // piVar7 = bone data array (each bone has 0x10 bytes?)
    local_a0 = DAT_00e2b1a4; // identity quaternion (w=1)
    uStack_9c = 0;
    uStack_98 = 0;
    uStack_94 = 0;

    fVar33 = *(float *)(param_1 + 0x104); // scaling factor (maybe m_scale)
    fVar31 = *(float *)(iVar29 + 0x10) * fVar33; // scale translation x
    fVar32 = *(float *)(iVar29 + 0x14) * fVar33; // scale translation y
    local_208 = (float *)(*(int *)(in_EAX + 0x38) + 0x30); // pointer to weight data array
    local_204 = (float *)(iVar29 + 0x20); // pointer to scale factors (x,y,z)
    local_20c = (char *)(*(int *)(in_EAX + 0x34) + 0x15); // pointer to bone index list

    uVar8 = *(uint *)(iVar27 + 8); // number of bones in this set
    fVar33 = *(float *)(iVar29 + 0x18) * fVar33; // scale translation z

    // Determine the maximum weight index if using weight mapping (+0xb4 is m_weightMap)
    iVar29 = uVar8 * 2;
    if (*(int *)(param_1 + 0xb4) != 0) {
        iVar29 = 0;
        local_248 = (float *)uVar8;
        if (0 < (int)uVar8) {
            do {
                uVar25 = (uint)*(byte *)(*(int *)(param_1 + 0xb4) + iVar29);
                if ((uVar25 != 0xff) && ((int)local_248 < (int)uVar25)) {
                    local_248 = (float *)uVar25;
                }
                iVar29 = iVar29 + 1;
            } while (iVar29 < (int)uVar8);
        }
        iVar29 = (int)local_248 * 2 + 2;
    }

    // Allocate temporary matrices (size = ((iVar29+1)*0x10)/0xc = roughly 4*4 matrix per bone)
    iVar29 = ((iVar29 + 1) * 0x10) / 0xc;
    piVar22 = (int *)FUN_0056ef10(iVar29); // m_tempMatrix1
    DAT_0120557c = piVar22 + 4; // store pointer to internal buffer
    piVar23 = (int *)FUN_0056ef10(iVar29); // m_tempMatrix2
    piVar24 = (int *)FUN_0056ef10(iVar29); // m_tempMatrix3

    // Initialize identity quaternions and matrices
    local_d0[2] = 0.0;
    local_d0[1] = 0.0;
    local_d0[0] = 0.0;
    local_d0[3] = DAT_00e2b1a4; // identity quaternion (w=1)
    local_b8 = 0;
    local_bc = 0;
    local_c0 = 0;
    local_b4 = DAT_00e2b1a4;

    iVar29 = *(int *)(*(int *)(in_EAX + 0x38) + 0xc); // number of bones
    local_1b0 = 0;
    bVar20 = false;
    local_230 = 1; // bone index start at 1? (0 is root?)

    if (1 < *(int *)(iVar27 + 8)) { // iterate over bones
        local_248 = (float *)(piVar24 + 0x14); // pointer to next bone in matrix 3
        iVar26 = (int)DAT_0120557c - (int)(piVar24 + 4);
        do {
            local_238 = piVar7 + 4; // current bone entry
            iVar9 = *(int *)(param_1 + 0xb4); // weight remap table
            if (iVar9 == 0 || *(byte *)(iVar9 + local_230) == 0xff) {
                pfVar30 = (float *)(iVar26 + (int)local_248); // use default buffer
            } else {
                pfVar30 = (float *)((uint)*(byte *)(iVar9 + local_230) * 0x40 + *(int *)(param_1 + 0xb8)); // use weight-specific buffer
            }
            pfVar28 = local_248;
            if (iVar9 != 0 && *(byte *)(iVar9 + local_230) != 0xff) {
                pfVar28 = (float *)(piVar23 + (uint)*(byte *)(iVar9 + local_230) * 0x10 + 4);
            }

            iVar10 = *local_238; // bone parent index (or type)
            if (iVar10 == 0) {
                // Root bone: set identity and scale
                local_244 = (float *)(piVar22 + 4);
                *local_244 = fVar31;
                // ... set rest of matrix to identity and zero translation except z
                // (see original code for full matrix initialization)
            } else if ((iVar9 == 0) || (*(byte *)(iVar10 + iVar9) == 0xff)) {
                local_244 = (float *)(piVar22 + iVar10 * 0x10 + 4);
            } else {
                local_244 = (float *)((uint)*(byte *)(iVar10 + iVar9) * 0x40 + *(int *)(param_1 + 0xb8));
            }

            // Similar initialization for piVar24 entry (if first bone)
            if (*local_238 == 0) {
                piVar24[4] = (int)fVar31; // set translation x
                // ... etc.
            }

            // Determine source matrix for blending (local_250)
            local_250 = local_d0; // default identity
            iVar9 = piVar7[7]; // bone type (e.g., 1=rotation, 2=orient, 3=world)
            if (iVar9 == 2) {
                local_250 = (float *)(piVar7[5] * 0x20 + *(int *)(*(int *)(param_1 + 0x70) + 0x58));
            } else if ((local_230 < iVar29) && (*local_20c == '\x02')) {
                if (iVar9 == 1) {
                    local_250 = local_208; // use weight data from mesh
                } else if (iVar9 == 3) {
                    bVar20 = true; // flag for extra transformation later
                }
            }

            // Main transformation path: if no override from special bone (m_boneFlags at +0xae)
            if (*(char *)(param_1 + 0xae) == '\0') {
                // Default path: build rotation matrix from quaternion (local_250) and apply scaling
                // Compute rotation matrix from quaternion: R = I - 2*(qy^2+qz^2), etc.
                // Then multiply by scale matrix from local_204.
                // Then multiply by bone's world matrix (local_244) to get final matrix.
                // This is standard skinning math.
                // (See original code for details)
            } else {
                // Custom bone path: check special bone flags (m_boneSpecialList at +0xa0)
                local_260 = local_1b0 * 0x20;
                local_264 = (int *)(*(int *)(param_1 + 0xa0) + local_260);
                if (*(short *)(param_1 + 0xa8) <= local_1b0) goto LAB_005759e4; // fallback to default
                do {
                    if (local_230 != (short)local_264[1]) break; // bone index match?
                    uVar6 = *(ushort *)((int)local_264 + 6); // flags
                    if ((char)uVar6 < '\0') {
                        bVar19 = true;
                        // Handle different flag combinations: (uVar6 & 1), (uVar6 & 0x10), (uVar6 & 0x20), etc.
                        // These apply different transformations: quaternion, matrix, or direct world.
                        // (See original for full branching)
                    }
                    local_260 += 0x20;
                    local_264 = (int *)(*(int *)(param_1 + 0xa0) + local_260);
                    local_1b0++;
                } while (local_1b0 < *(short *)(param_1 + 0xa8));
                if (!bVar19) goto LAB_005759e4;
            }

            // Advance pointers for next bone
            local_20c += 1;
            local_208 += 8;
            local_248 += 0x10;
            local_204 += 4;
            local_230 += 1;
            piVar7 = local_238;
        } while (local_230 < *(int *)(iVar27 + 8));
    }

    // Second loop: apply extra scaling? (based on m_additionalScaleCount at +0xaa)
    local_214 = 0;
    if (0 < *(short *)(param_1 + 0xaa)) {
        do {
            // Apply some identity matrix transformation
            // (likely multiplying by identity to no effect, maybe for padding)
            local_90 = local_a0;
            // ... set local variables
            FUN_00414aa0();
            FUN_00417560();
            FUN_00417560();
            local_214++;
        } while (local_214 < *(short *)(param_1 + 0xaa));
    }

    // If bVar20 set (bone type 3 encountered), apply additional transform to all bones of type 3
    if (bVar20) {
        iVar29 = 1;
        if (1 < *(int *)(iVar27 + 8)) {
            iVar26 = *(int *)(iVar27 + 0xc) + 0x18;
            do {
                if (*(int *)(iVar26 + 4) == 3) {
                    FUN_00417560();
                }
                iVar29++;
                iVar26 += 0x10;
            } while (iVar29 < *(int *)(iVar27 + 8));
        }
    }

    // Cleanup: decrement reference counts and free temporary buffers (if count reaches zero)
    iVar27 = DAT_01205560; // global memory manager?
    // Decrement reference count of piVar24, piVar23, piVar22 (each has ref count at offset +9)
    *(char *)((int)piVar24 + 9) -= 1;
    if (((char)piVar24[2] == '\0') && (*(char *)((int)piVar24 + 9) == '\0')) {
        // Free block (linked list management)
        // ... similar for piVar23 and piVar22
    }
    *(char *)((int)piVar23 + 9) -= 1;
    DAT_01205584 = 0;
    // ... free check
    *(char *)((int)piVar22 + 9) -= 1;
    _DAT_01205580 = 0;
    // ... free check
    DAT_0120557c = 0;
    return;
}