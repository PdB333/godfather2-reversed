// FUNC_NAME: AnimatedSkin::computeBoneMatrices
// Address: 0x005764e0
// Computes blended bone matrices for skinning, handling multiple bone influences per vertex.

#include <cstdint>

// Constants used in matrix computation
static const float kIdentityW = 1.0f; // DAT_00e2b1a4
static const float kScaleFactor = 2.0f; // DAT_00e2b04c (not exactly, but used as multiplier)

// Global free list head (DAT_01205560)
struct FreeListNode {
    FreeListNode* prev;
    FreeListNode* next;
    // ... possibly more fields
};
static FreeListNode* freeListHead; // DAT_01205560
static int freeListNodeCount; // DAT_0120557c

// Helper functions (callees)
extern void* allocateMemory(int size); // FUN_0056ef10 - size in units? (size+1)*0x10/0xc
extern void transformVectorByMatrix(); // FUN_00417560 - likely vector * matrix
extern void multiplyMatrices(); // FUN_00414aa0 - matrix multiply
extern void computeBlendMatrix(); // FUN_00574760 - blend two matrices
extern void computeShiftedBlend(); // FUN_00574860 - blending with shift

// Bone influence data (per vertex)
struct BoneInfluence {
    uint8_t boneIndex;    // 0xFF means none
};

// Bone data per skin entry
struct BoneData {
    float matrix[16];  // 4x4 matrix
};

// Internal bone entry (from param_1+0x70)
struct BoneEntryArray {
    int count;          // +0x18
    int dummy;          // +0x1c? actually array pointer
    int* entries;       // +0x1c actually? No: the code does *(int*)(iVar18+0x1c) + sVar5*0x18
    // Actually it's: (base) + offset of entry * 0x18
    // Entry structure:
    // +0x00: ?
    // +0x04: ?
    // +0x08: numBones (uint)
    // +0x0c: array of BoneSubData (each 16 bytes)
};

struct BoneSubData {
    int unknown0;      // +0x00
    int blendType;     // +0x04: 0,1,2,3
    int unknown8;      // +0x08
    int unknownC;      // +0x0c
};

void __fastcall FUN_005764e0(int param_1, int param_2) {
    float fVar1, fVar2, fVar3, fVar4, fVar13, fVar21;
    short sVar5;
    uint8_t uVar6;
    int* piVar7;
    uint uVar8, uVar15;
    int iVar9, iVar17, iVar18, iVar20;
    float* pfVar10, *pfVar19;
    bool bVar11, bVar12;
    int local_214, local_1d8, local_1e8;
    float* local_218, *local_20c, *local_1e4, *local_1c4;
    uint8_t* local_1c8;
    float local_e0, fStack_dc, fStack_d8;
    float local_c0[4]; // quaternion?
    float local_a4, local_a0, fStack_64, fStack_64_2;
    int iStack_9c, iStack_98, iStack_94, local_90, iStack_88, iStack_84, local_80, iStack_7c;
    int iStack_74, local_70, iStack_6c, iStack_68;
    float fStack_8c, fStack_78;
    int iStack_5c, iStack_58, iStack_54;

    // Get bone entry pointer from param_1+0x70
    iVar18 = *(int*)(param_1 + 0x70);
    if (iVar18 == 0 || *(int*)(iVar18 + 0x18) < 1 || *(int*)(iVar18 + 0x1c) == 0) {
        iVar18 = 0;
    } else {
        sVar5 = *(short*)(param_1 + 0x76);
        if (sVar5 < 0 || sVar5 >= *(int*)(iVar18 + 0x18)) {
            iVar18 = 0;
        } else {
            iVar18 = *(int*)(iVar18 + 0x1c) + sVar5 * 0x18;
        }
    }
    if (iVar18 == 0) return;

    // Get bone subdata array (each entry 0x10 = 16 bytes)
    piVar7 = *(int**)(iVar18 + 0xC);

    // Initialize some values (likely identity or default rotation)
    iStack_9c = 0; iStack_98 = 0; iStack_94 = 0;
    float defaultW = kIdentityW; // DAT_00e2b1a4
    local_60 = defaultW;
    iStack_5c = 0; iStack_58 = 0; iStack_54 = 0;
    local_90 = 0; iStack_88 = 0; iStack_84 = 0;
    local_80 = 0; iStack_7c = 0; iStack_74 = 0;
    local_70 = 0; iStack_6c = 0; iStack_68 = 0;
    fStack_64 = defaultW;

    // Get pointers from param_2 (likely a render state)
    local_1c8 = (uint8_t*)(*(int*)(param_2 + 0x34) + 0x15);  // +0x15 offset into some data
    local_1c4 = (float*)(*(int*)(param_2 + 0x38) + 0x30);    // matrix array?

    uVar8 = *(uint*)(iVar18 + 8);  // number of bones
    local_a0 = *(float*)(param_1 + 0x104); // some scale/weight factor

    // Determine max bone index to allocate space
    iVar17 = uVar8 * 2;
    if (*(int*)(param_1 + 0xB4) != 0) {
        // Scan for highest non-0xFF index
        local_218 = 0; // as float*, but used as byte* index
        local_200 = uVar8;
        if ((int)uVar8 > 0) {
            do {
                uVar15 = *(uint8_t*)(*(int*)(param_1 + 0xB4) + (int)local_218);
                if (uVar15 != 0xFF && (int)local_200 < (int)uVar15) {
                    local_200 = uVar15;
                }
                local_218 = (float*)((int)local_218 + 1);
            } while ((int)local_218 < (int)uVar8);
        }
        iVar17 = local_200 * 2 + 2;
    }

    fStack_8c = local_a0;
    fStack_78 = local_a0;

    // Allocate memory for output matrices (each matrix 16 floats, but the allocation formula is weird)
    int allocSize = ((iVar17 + 1) * 0x10) / 0xC; // size in some units for FUN_0056ef10
    int* piVar14 = (int*)FUN_0056ef10(allocSize);

    // Initialize a quaternion/rotation (local_c0: 4 floats, but used as 3 + w)
    local_c0[0] = 0.0f; local_c0[1] = 0.0f; local_c0[2] = 0.0f; local_c0[3] = defaultW;
    // Also another set (local_b0, local_ac, local_a8, local_a4)
    local_a8 = 0; local_ac = 0; local_b0 = 0;
    local_a4 = defaultW;

    iVar17 = *(int*)(*(int*)(param_2 + 0x38) + 0xC); // some count from render state
    local_1d8 = 0; // counter for influence list
    bVar12 = false; // flag for blend type 3
    local_200 = 1; // current bone index (start from 1)
    if (1 < *(int*)(iVar18 + 8)) { // if more than 1 bone
        local_218 = (float*)(piVar14 + 0x14); // output matrix pointer (skip header?)
        fVar21 = 0.5f; // DAT_00e2b04c (maybe 2.0? Actually used as multiplier for 1 - sum squares)
        do {
            // Determine source matrix for this bone
            iVar20 = *(int*)(param_1 + 0xB4); // influence array base
            pfVar19 = local_218; // default output location
            if (iVar20 != 0 && *(uint8_t*)(iVar20 + local_200) != 0xFF) {
                // Use influence index to get vertex matrix from param_1+0xB8
                uint8_t idx = *(uint8_t*)(iVar20 + local_200);
                pfVar19 = (float*)((int)idx * 0x40 + *(int*)(param_1 + 0xBB8)); // 0x40 = 64 = 16 floats
            }

            // Determine blend type for this bone
            iVar9 = piVar7[4]; // blend type
            if (iVar9 == 0) {
                // Direct copy of default values
                local_1e4 = (float*)(piVar14 + 4);
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
            } else if (iVar20 == 0 || *(uint8_t*)(iVar9 + iVar20) == 0xFF) {
                // No influence for this bone: use default location in allocated memory
                local_1e4 = (float*)(piVar14 + iVar9 * 0x10 + 4);
            } else {
                // Use influenced matrix
                uint8_t idx = *(uint8_t*)(iVar9 + iVar20);
                local_1e4 = (float*)((int)idx * 0x40 + *(int*)(param_1 + 0xBB8));
            }

            // Determine input matrix (local_20c) based on blend type and other conditions
            iVar20 = piVar7[7]; // blend type again?
            local_20c = local_c0;
            if (iVar20 == 2) {
                // Use from a different array
                int base = *(int*)(*(int*)(param_1 + 0x70) + 0x58);
                local_20c = (float*)(piVar7[5] * 0x20 + base);
            } else if ((int)local_200 < iVar17 && *local_1c8 == 0x02) {
                if (iVar20 == 1) {
                    local_20c = local_1c4;
                } else if (iVar20 == 3) {
                    bVar12 = true;
                }
            }

            bVar11 = false;
            if (*(char*)(param_1 + 0xAE) == '\0') {
                // Simple path: direct matrix creation
                goto directMatrix;
            } else {
                // Complex path: check influence list at param_1+0xA0
                local_214 = local_1d8 * 0x20; // size of each entry
                int* piVar16 = (int*)(*(int*)(param_1 + 0xA0) + local_214);
                if (local_1d8 >= *(short*)(param_1 + 0xA8)) {
                    goto directMatrix;
                }
                do {
                    if (local_200 != (int)(short)piVar16[1]) break; // bone index mismatch
                    uint16_t uVar6 = *(uint16_t*)((int)piVar16 + 6); // flags
                    if ((char)uVar6 < 0) {
                        bVar11 = true;
                        if ((uVar6 & 1) == 0) {
                            // Handle flag bits: 2,4,8,16, etc.
                            if ((uVar6 & 0x10) == 0) {
                                if ((uVar6 & 0x20) == 0) {
                                    if ((uVar6 & 4) == 0) {
                                        // No extra transformation: compute matrix from local_20c rotation
                                        // (similar to directMatrix but with different order)
                                    } else {
                                        // Use pointer in piVar16[0] as matrix source
                                        pfVar10 = (float*)*piVar16;
                                        // compute matrix from pfVar10
                                    }
                                    // Apply some extra transformations (calls to FUN_00414aa0/multiply)
                                    goto handleFlags;
                                } else {
                                    FUN_00574760(pfVar19, local_1e4); // blend two matrices
                                    fVar21 = 0.5f; // reset
                                }
                            } else {
                                FUN_00574860(local_1e4, CONCAT44(*piVar16, local_20c), piVar16[2], uVar6);
                                fVar21 = 0.5f;
                            }
                        } else {
                            // Bit 0 set: compute matrix from local_20c quaternion
                            // Then apply additional transformations based on flags
                            // and possibly adjust position
                        }
                    }
                    local_214 += 0x20;
                    piVar16 = (int*)(*(int*)(param_1 + 0xA0) + local_214);
                    local_1d8++;
                } while (local_1d8 < *(short*)(param_1 + 0xA8));
                if (!bVar11) goto directMatrix;
            }

            // Continue loop
            local_1c8++;
            local_1c4 += 8; // advance to next matrix
            local_218 += 0x10; // next output matrix
            local_200++;
            piVar7 += 4; // next bone subdata
        } while ((int)local_200 < *(int*)(iVar18 + 8));
    }

    // After main loop, process extra entries (param_1+0xAA)
    local_1e8 = 0;
    if (0 < *(short*)(param_1 + 0xAA)) {
        do {
            // Reset defaults and call some functions (likely cleanup)
            local_a0 = local_60;
            iStack_9c = iStack_5c; iStack_98 = iStack_58; iStack_94 = iStack_54;
            local_90 = iStack_54;
            fStack_8c = local_60;
            iStack_88 = iStack_54; iStack_84 = iStack_54;
            local_80 = iStack_54; iStack_7c = iStack_54;
            fStack_78 = local_60;
            iStack_74 = iStack_54;
            local_70 = iStack_54; iStack_6c = iStack_54; iStack_68 = iStack_54;
            fStack_64 = local_60;
            // Call identity? multiplyMatrices, transform
            FUN_00414aa0(); // multiply
            FUN_00417560(); // transform
            FUN_00417560(); // another transform
            local_1e8++;
        } while (local_1e8 < *(short*)(param_1 + 0xAA));
    }

    if (bVar12) {
        // Handle blend type 3 entries
        iVar17 = 1;
        if (1 < *(int*)(iVar18 + 8)) {
            int* pEntry = (int*)(*(int*)(iVar18 + 0xC) + 0x18);
            do {
                if (pEntry[4] == 3) {
                    // apply some transform
                    // FUN_00417560(); // transform?
                }
                iVar17++;
                pEntry += 0x10 / 4; // advance 16 bytes
            } while (iVar17 < *(int*)(iVar18 + 8));
        }
    }

    // Free list management (similar to memory pool deallocation)
    // The allocated block piVar14 is returned to a free list if not in use.
    *(char*)((int)piVar14 + 9) -= 1; // decrement ref count?
    if (*(char*)(int*)piVar14 == '\0' && *(char*)((int)piVar14 + 9) == '\0') {
        // Remove from linked list
        iVar18 = *piVar14;
        int* piVar7 = (int*)piVar14[1];
        if (iVar18 != 0) {
            *(int**)(iVar18 + 4) = piVar7;
        }
        int* head = (int*)DAT_01205560;
        if (piVar7 == 0) {
            *(uint32_t*)(DAT_01205560 + 8) = *(uint32_t*)(DAT_01205560 + 4);
            *(int*)(head + 1) = iVar18;
            DAT_0120557c = 0;
            if (iVar18 == 0) {
                *(uint32_t*)(head + 2) = *(uint32_t*)(head + 3);
                return;
            }
        } else {
            *piVar7 = iVar18;
        }
    }
    DAT_0120557c = 0;
    return;

directMatrix:
    // Compute matrix from local_20c quaternion and scale
    fVar13 = kIdentityW;
    fVar1 = local_20c[2]; fVar2 = *local_20c; fVar3 = local_20c[1]; fVar4 = local_20c[3];
    *pfVar19 = kIdentityW - (fVar3*fVar3 + fVar1*fVar1) * fVar21;
    pfVar19[4] = (fVar2*fVar3 - fVar4*fVar1) * fVar21;
    pfVar19[1] = (fVar4*fVar1 + fVar2*fVar3) * fVar21;
    pfVar19[5] = kIdentityW - (fVar2*fVar2 + fVar1*fVar1) * fVar21;
    pfVar19[2] = (fVar2*fVar1 - fVar4*fVar3) * fVar21;
    pfVar19[3] = 0.0f;
    pfVar19[6] = (fVar1*fVar3 + fVar2*fVar4) * fVar21;
    pfVar19[7] = 0.0f;
    pfVar19[8] = (fVar4*fVar3 + fVar2*fVar1) * fVar21;
    pfVar19[9] = (fVar1*fVar3 - fVar2*fVar4) * fVar21;
    pfVar19[10] = kIdentityW - (fVar3*fVar3 + fVar2*fVar2) * fVar21;
    pfVar19[11] = 0.0f;
    // Translate
    pfVar19[12] = local_20c[4];
    pfVar19[13] = local_20c[5];
    pfVar19[14] = local_20c[6];
    pfVar19[15] = local_20c[7];
    pfVar19[15] = fVar13; // override W to 1.0
    // Call some function
    FUN_00417560(); // likely finalize matrix (transpose? multiply?)
}