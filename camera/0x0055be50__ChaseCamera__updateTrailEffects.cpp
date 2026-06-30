// FUNC_NAME: ChaseCamera::updateTrailEffects

void __thiscall ChaseCamera::updateTrailEffects(int* this, float deltaTime, char isActive)
{
    // Call virtual function at vtable+0x198 to check something (maybe camera active?)
    char cVar1 = (*(code**)(*this + 0x198))();
    if (cVar1 == 0) {
        return;
    }

    // If isActive == false, destroy all trails (4 slots)
    if (isActive == 0) {
        int* trailSlotArray = this + 0x1d1; // +0x744 = offset 0x1d1*4 = 0x744
        for (int i = 0; i < 4; i++) {
            // Call cleanup function for each slot (likely decrements refcount or releases)
            FUN_0055af20();
            int* trailObjPtr = (int*)*trailSlotArray;
            if (trailObjPtr != 0) {
                int* refCount = trailObjPtr + 1;
                *refCount = *refCount - 1;
                if (*refCount == 0) {
                    (*(code**)(*trailObjPtr + 4))(); // destructor
                }
                *trailSlotArray = 0;
            }
            trailSlotArray += 5; // advance to next slot (20 bytes per slot)
        }
        return;
    }

    // Update trails when active
    uint* puStack_110 = (uint*)(this + 0xe9);   // offset 0x3a4 (some flag array)
    int* piVar6 = this + 0x1d2;                 // offset 0x748: array of trail control structs (5 ints each)
    float fStack_60 = DAT_00e2b334;            // likely 0.0f
    float fStack_5c = DAT_00e2b334;
    float fStack_58 = DAT_00e2b334;
    float fStack_54 = DAT_00e2b334;
    int iStack_118 = 0;
    int iStack_10c = 0;
    int iStack_108 = 0;
    float fVar12 = DAT_00e2b1a4;                // likely 1.0f

    do {
        float fVar9 = DAT_00e44564;             // some constant (maybe 0.0f?)
        float* pfVar7 = (float*)(*(int*)(this[0xd8] + 0x48) + iStack_108); // pointer to trail point data (stride 0xc0)
        float fVar10;
        float fVar11;
        if (pfVar7[9] == 0.0) {
            fVar11 = 0.0f;
            fVar10 = fVar11;
        } else {
            fVar10 = pfVar7[0x2a] - (float)this[0x1e6]; // some delta
            if (fVar10 <= 0.0) {
                fVar11 = 0.0f;
                fVar10 = fVar11;
            } else {
                fVar10 = fVar10 / ((float)this[0x1e7] - (float)this[0x1e6]); // normalized alpha
                fVar11 = fVar12;
                if (fVar12 < fVar10) {
                    fVar10 = fVar11;
                }
            }
        }

        // State machine for this trail slot
        // piVar6[-2] is the state (0=inactive, 1=fading in, 2=active)
        if (piVar6[-2] == 1) {
            if (fVar10 > 0.0) {
                fVar9 = (float)piVar6[2];
                piVar6[2] = (int)(fVar9 + deltaTime);
                if (fVar9 + deltaTime > 0.0) {
                    piVar6[-2] = 2;
                }
            } else {
                piVar6[-2] = 0;
            }
        } else if (piVar6[-2] == 2) {
            if (fVar10 <= 0.0) {
                piVar6[-2] = 0;
            }
        } else {
            if (fVar10 > 0.0) {
                piVar6[-2] = 1;
                piVar6[2] = (int)(fVar9 - (float)this[0x1e4]); // initial timer
            }
        }

        // Get camera target transform (position + orientation)
        float afStack_a0[7] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
        (*(code**)(*this + 0x250))(iStack_118, afStack_a0); // virtual function gets target transform for this slot

        // Get some time factor from another object
        fVar12 = *(float*)(*(int*)(this[0xda] + 0x8c) + 8 + iStack_10c); // stride 0x28 (40 bytes)

        // Blend current trail point with the target transform
        float fStack_b0 = pfVar7[4] * fStack_60 + *pfVar7;   // lerp x
        float fStack_ac = pfVar7[5] * fStack_5c + pfVar7[1]; // lerp y
        float fStack_a8 = pfVar7[6] * fStack_58 + pfVar7[2]; // lerp z

        float fStack_e0 = afStack_a0[0];
        float fStack_dc = afStack_a0[1];
        float fStack_d8 = afStack_a0[2];
        float fStack_d4 = afStack_a0[3]; // w? (quaternion)

        float fVar9 = fVar12 * DAT_00e44718; // scale factor
        float fVar12_2 = fVar12 * DAT_00e2cd54; // another scale factor

        // Two interpolated positions
        float fStack_c0 = fVar9 * afStack_a0[0] + fStack_b0;
        float fStack_bc = fVar9 * afStack_a0[1] + fStack_ac;
        float fStack_b8 = fVar9 * afStack_a0[2] + fStack_a8;
        float fStack_b0_2 = fVar12_2 * afStack_a0[0] + fStack_b0;
        float fStack_ac_2 = fVar12_2 * afStack_a0[1] + fStack_ac;
        float fStack_a8_2 = fVar12_2 * afStack_a0[2] + fStack_a8;

        // Create or manage the visual trail object (e.g., ribbon)
        if (piVar6[-2] == 2) {
            // State 2: active trail
            if (piVar6[-1] == 0) {
                // Allocate a new trail object (size 0x40)
                int* allocator = (int*)FUN_009c8f80();
                int aiStack_100[5];
                aiStack_100[1] = 2; // allocation type?
                aiStack_100[2] = 0x10; // alignment?
                aiStack_100[3] = 0;
                void* mem = (void*)(**(code**)*allocator)(0x40, aiStack_100 + 1);
                if (mem == 0) {
                    piVar6[-1] = 0;
                    // Increment global allocation counter?
                    _DAT_00000004 = _DAT_00000004 + 1;
                } else {
                    // Initialize trail object
                    int* trailObj = (int*)mem;
                    trailObj[1] = 0; // ref count?
                    trailObj[0] = (int)&PTR_LAB_00e3a070; // vtable
                    trailObj[0xc] = 0;
                    trailObj[7] = 0;
                    trailObj[6] = 0;
                    trailObj[5] = 0;
                    trailObj[4] = 0;
                    trailObj[0xb] = 0;
                    trailObj[10] = 0;
                    trailObj[9] = 0;
                    trailObj[8] = 0;
                    piVar6[-1] = (int)trailObj;
                    trailObj[1] = trailObj[1] + 1; // increment ref count
                }
            }

            // Insert trail node into linked list
            if (*piVar6 == 0) {
                char auStack_50[76]; // buffer for copy
                FUN_0044b4e0(auStack_50, this + 0x34); // copy 64 bytes (matrix?) from this+0x34
                int uStack_e8 = 0xffffffff;
                int uStack_e4 = 0;
                aiStack_100[4] = 1;
                int* piStack_ec = this;
                int uVar3 = (*(code**)(*this + 0x58))(0, aiStack_100 + 4); // virtual: get some object
                int* piVar4 = (int*)FUN_004df270(&iStack_104, this + 0x1c8, auStack_50, uVar3); // linked list insertion
                if (*piVar6 != 0) {
                    *(int*)(*piVar6 + 8) = 0;
                    *piVar6 = 0;
                }
                int iVar5 = *piVar4;
                *piVar6 = iVar5;
                if (iVar5 != 0) {
                    *(int**)(iVar5 + 8) = piVar6;
                    *piVar4 = 0;
                }
                if (iStack_104 != 0) {
                    *(int*)(iStack_104 + 8) = 0;
                    iStack_104 = 0;
                }
                FUN_004df830(piVar6[-1]); // link trail object to node?
            }
        } else {
            // State 0 or 1: trail not active
            if (piVar6[1] != 0) {
                int iVar5 = piVar6[1];
                if (iVar5 != 0) {
                    // Clear a flag and call something
                    if ((*(uint*)(iVar5 + 0xc) & 0x20000) == 0) {
                        *(uint*)(iVar5 + 0xc) |= 0x20000;
                        FUN_0051b120();
                    }
                    *(uint*)(iVar5 + 0xc) &= 0xfffbffff;
                }
            }
            fVar10 = 0.0f;
        }

        // Update visual trail object positions
        int iVar5 = piVar6[-1];
        if (iVar5 != 0) {
            *(float*)(iVar5 + 0x10) = fStack_c0;
            *(float*)(iVar5 + 0x14) = fStack_bc;
            *(float*)(iVar5 + 0x18) = fStack_b8;
            *(int*)(iVar5 + 0x1c) = uStack_b4; // maybe color?
            *(float*)(iVar5 + 0x20) = fStack_b0_2;
            *(float*)(iVar5 + 0x24) = fStack_ac_2;
            *(float*)(iVar5 + 0x28) = fStack_a8_2;
            *(int*)(iVar5 + 0x2c) = uStack_a4; // maybe color?
            *(float*)(iVar5 + 0x30) = fVar10; // alpha? (0 if not active)
        }

        // Possibly create additional trail child for other wheels?
        fVar12 = DAT_00e2b1a4; // reset to 1.0
        if (((((piVar6[1] == 0) && (1 < iStack_118)) && (piVar6[-2] == 2)) &&
            (((this[0x1cc] != 0 || this[0x1cd] != 0) || (this[0x1ce] != 0 || this[0x1cf] != 0)))) &&
            ((fVar9 = (fVar10 - (float)this[0x1e5]) / (DAT_00e2b1a4 - (float)this[0x1e5]),
              0.0 < fVar9 && ((DAT_00e2b1a4 <= fVar9 || (0.0 < fVar9)))))) {
            // Copy current target transform and create another trail node
            float* pfVar7_2 = (float*)(this + 0x34);
            float* pfVar8 = afStack_a0;
            for (int i = 0x10; i != 0; i--) {
                *pfVar8 = *pfVar7_2;
                pfVar7_2++;
                pfVar8++;
            }
            char auStack_50[76];
            FUN_0044b4e0(auStack_50, afStack_a0);
            uint uStack_c8 = *puStack_110 >> 2; // some index
            int uStack_d0 = 2;
            int uStack_c4 = 0;
            int* piStack_cc = this;
            int uVar3_2 = (*(code**)(*this + 0x58))(0, &uStack_d0);
            int* uVar3_3 = (int*)FUN_004df270(aiStack_100, this + 0x1cc, auStack_50, uVar3_2);
            FUN_00414db0(uVar3_3);
            fVar12 = DAT_00e2b1a4;
            if (aiStack_100[0] != 0) {
                *(int*)(aiStack_100[0] + 8) = 0;
                aiStack_100[0] = 0;
            }
        }

        iStack_118++;
        puStack_110++;
        iStack_10c += 0x28; // stride for time factor array
        iStack_108 += 0xc0; // stride for trail point data
        piVar6 += 5; // next slot (20 bytes)
    } while (iStack_108 < 0x300); // 4 iterations (0x300/0xc0 = 4)
}