// FUNC_NAME: MorphDataSet::addMorphTarget
short* __thiscall MorphDataSet::addMorphTarget(void* thisPtr, int param2)
{
    float fVar1;
    float fVar2;
    float fVar3;
    int* piVar4;
    uint uVar5;
    short* psVar6;
    undefined4* puVar7;
    uint* puVar8;
    int iVar9;
    uint uVar10;
    int iVar11;
    int iVar12;
    undefined4* puVar13;
    int iVar14;
    uint* puVar15;
    int iVar16;
    int iVar17;
    float fVar18;
    int local_14;
    int local_10;
    int local_c;
    uint local_8;

    psVar6 = (short*)FUN_0049c9c0(); // Global resource/manager pointer
    if (*psVar6 != 3) {
        return (short*)0x0;
    }

    // Allocate new morph target object (0x24 bytes)
    puVar7 = (undefined4*)FUN_009c8e50(0x24);
    puVar13 = (undefined4*)0x0;
    if (puVar7 != (undefined4*)0x0) {
        puVar7[1] = 0;
        *puVar7 = &PTR_FUN_00d606b8; // vtable
        puVar7[2] = 0;
        puVar7[6] = 0;
        puVar7[5] = 0;
        puVar7[4] = 0;
        puVar7[3] = 0;
        puVar7[7] = 0;
        puVar7[8] = 0;
        puVar13 = puVar7;
    }
    puVar13[7] = (int)psVar6; // +0x1c? Actually index 7 is offset 0x1c

    // Copy 4 dwords from input data (param2+4)
    puVar7 = *(undefined4**)(param2 + 4);
    puVar13[3] = *puVar7;       // +0x0c
    puVar13[4] = puVar7[1];     // +0x10
    puVar13[5] = puVar7[2];     // +0x14
    puVar13[6] = puVar7[3];     // +0x18

    // Add new morph target to internal vector at this+0xc
    piVar4 = *(int**)((int)thisPtr + 0xc);
    iVar16 = piVar4[2]; // capacity
    if (piVar4[1] == iVar16) { // size == capacity
        if (iVar16 == 0) {
            iVar16 = 1;
        } else {
            iVar16 = iVar16 * 2;
        }
        FUN_006f4410(iVar16); // grow vector
    }
    puVar7 = (undefined4*)(*piVar4 + piVar4[1] * 4);
    piVar4[1] = piVar4[1] + 1; // size++
    if (puVar7 != (undefined4*)0x0) {
        *puVar7 = puVar13; // store pointer
    }

    // Adjust relative pointers in the global resource
    if (*(int*)(psVar6 + 2) != 0) {
        *(int*)(psVar6 + 2) = *(int*)(psVar6 + 2) + (int)psVar6;
    }

    local_8 = (uint)(ushort)psVar6[1]; // count from global resource
    if (local_8 != 0) {
        // Allocate array of morph target records (size 0x24 each)
        puVar8 = (uint*)FUN_009c8e80(-(uint)(0xfffffffb < local_8 * 0x24) | local_8 * 0x24 + 4);
        if (puVar8 == (uint*)0x0) {
            puVar15 = (uint*)0x0;
        } else {
            puVar15 = puVar8 + 1;
            *puVar8 = local_8;
            _vector_constructor_iterator_(puVar15, 0x24, local_8, (_func_void_ptr_void_ptr*)&LAB_006f41c0);
        }
        puVar13[8] = (int)puVar15; // +0x20

        if (local_8 != 0) {
            iVar16 = 0;
            local_14 = 0;
            do {
                // Process each morph target entry
                piVar4 = (int*)(*(int*)(psVar6 + 2) + 8 + iVar16);
                iVar11 = *piVar4;
                if (iVar11 != 0) {
                    *piVar4 = iVar11 + (int)psVar6;
                }
                iVar11 = *(int*)(*(int*)(psVar6 + 2) + 0xc + iVar16);
                if (iVar11 != 0) {
                    *(int*)(*(int*)(psVar6 + 2) + 0xc + iVar16) = iVar11 + (int)psVar6;
                }
                iVar11 = *(int*)(psVar6 + 2);
                iVar17 = (int)puVar15 + local_14; // base + index * 0x24
                *(int*)(iVar17 + 0x18) = iVar11 + iVar16; // +0x18: pointer to segment data

                uVar5 = *(uint*)(iVar11 + iVar16 + 4); // count of bone/weight pairs
                if (uVar5 != 0) {
                    uVar10 = -(uint)((int)((ulonglong)uVar5 * 0x10 >> 0x20) != 0) | (uint)((ulonglong)uVar5 * 0x10);
                    puVar8 = (uint*)FUN_009c8e80(-(uint)(0xfffffffb < uVar10) | uVar10 + 4);
                    if (puVar8 == (uint*)0x0) {
                        puVar8 = (uint*)0x0;
                    } else {
                        *puVar8 = uVar5;
                        puVar8 = puVar8 + 1;
                        _vector_constructor_iterator_(puVar8, 0x10, uVar5, (_func_void_ptr_void_ptr*)&LAB_006f4180);
                    }
                    fVar18 = 0.0;
                    *(uint**)(iVar17 + 0x1c) = puVar8; // +0x1c: pointer to weight array
                    if (puVar8 != (uint*)0x0) {
                        uVar10 = 0;
                        if (3 < (int)uVar5) {
                            // Process groups of 4
                            iVar11 = 0;
                            iVar12 = 0;
                            local_10 = (uVar5 - 4 >> 2) + 1;
                            uVar10 = local_10 * 4;
                            do {
                                iVar9 = (int)puVar8 + iVar12;
                                iVar14 = *(int*)(*(int*)(psVar6 + 2) + 0xc + iVar16) + iVar11;
                                *(int*)(iVar9 + 0xc) = iVar14;             // +0x0c: pointer
                                *(undefined4*)(iVar9 + 4) = *(undefined4*)(iVar14 + 0x14); // +0x04: weight
                                fVar1 = *(float*)(*(int*)(iVar9 + 0xc) + 0x14);
                                iVar9 = iVar12 + 0x10 + (int)puVar8;
                                iVar14 = *(int*)(*(int*)(psVar6 + 2) + 0xc + iVar16) + 0x20 + iVar11;
                                *(int*)(iVar9 + 0xc) = iVar14;
                                *(undefined4*)(iVar9 + 4) = *(undefined4*)(iVar14 + 0x14);
                                fVar2 = *(float*)(*(int*)(iVar9 + 0xc) + 0x14);
                                iVar9 = iVar12 + 0x20 + (int)puVar8;
                                iVar14 = *(int*)(*(int*)(psVar6 + 2) + 0xc + iVar16) + 0x40 + iVar11;
                                *(int*)(iVar9 + 0xc) = iVar14;
                                *(undefined4*)(iVar9 + 4) = *(undefined4*)(iVar14 + 0x14);
                                fVar3 = *(float*)(*(int*)(iVar9 + 0xc) + 0x14);
                                iVar14 = (int)puVar8 + iVar12 + 0x30;
                                iVar9 = *(int*)(*(int*)(psVar6 + 2) + 0xc + iVar16) + 0x60 + iVar11;
                                *(int*)(iVar14 + 0xc) = iVar9;
                                *(undefined4*)(iVar14 + 4) = *(undefined4*)(iVar9 + 0x14);
                                iVar12 = iVar12 + 0x40;
                                iVar11 = iVar11 + 0x80;
                                local_10 = local_10 + -1;
                                fVar18 = *(float*)(*(int*)(iVar14 + 0xc) + 0x14) + fVar3 + fVar2 + fVar1 + fVar18;
                            } while (local_10 != 0);
                        }
                        // Remaining entries (less than 4)
                        if (uVar10 < uVar5) {
                            iVar12 = uVar10 << 5;
                            iVar11 = uVar10 << 4;
                            local_c = uVar5 - uVar10;
                            do {
                                iVar9 = (int)puVar8 + iVar11;
                                iVar14 = *(int*)(*(int*)(psVar6 + 2) + 0xc + iVar16) + iVar12;
                                *(int*)(iVar9 + 0xc) = iVar14;
                                *(undefined4*)(iVar9 + 4) = *(undefined4*)(iVar14 + 0x14);
                                iVar11 = iVar11 + 0x10;
                                iVar12 = iVar12 + 0x20;
                                local_c = local_c + -1;
                                fVar18 = *(float*)(iVar14 + 0x14) + fVar18;
                            } while (local_c != 0);
                        }
                    }
                    *(float*)(iVar17 + 8) = fVar18; // +0x08: total weight sum
                }
                local_14 = local_14 + 0x24;
                iVar16 = iVar16 + 0x10;
                local_8 = local_8 - 1;
            } while (local_8 != 0);
        }
    }
    return psVar6;
}