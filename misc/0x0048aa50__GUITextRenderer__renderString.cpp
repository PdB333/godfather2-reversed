// FUNC_NAME: GUITextRenderer::renderString

void __thiscall GUITextRenderer::renderString(int textObject, int fontObject, int param3, float param4, char *inputString, float param6, float param7, float param8, undefined *param9, int param10, char param11, undefined4 param12, undefined4 param13, float *clipRect, int maxLines, char param16)
{
    undefined *puVar1;
    char cVar2;
    int iVar3;
    bool bVar4;
    undefined1 *puVar5;
    ushort uVar6;
    int iVar7;
    uint uVar8;
    int iVar9;
    float fVar10;
    float fVar11;
    float fVar12;
    float fVar13;
    float fVar14;
    char local_38f2;
    char local_38f1;
    undefined *local_38f0;
    int local_38ec;
    int local_38e8;
    ushort local_38e4;
    int local_38e0;
    char local_38d9;
    undefined *local_38d8;
    int local_38d4;
    int local_38d0;
    ushort local_38cc;
    int local_38c8;
    char *local_38c4;
    float local_38c0;
    float local_38bc;
    float local_38b8;
    uint local_38b4;
    float local_38b0;
    float local_38ac;
    float local_38a8;
    int local_38a4;
    float local_38a0;
    uint local_389c;
    uint local_3898;
    float local_3894;
    float local_3890;
    float local_388c;
    int local_3888;
    float local_3884;
    undefined4 local_3880;
    undefined4 local_387c;
    undefined4 local_3878;
    undefined4 local_3874;
    float local_3870;
    float local_386c;
    float local_3868;
    float local_3860;
    int local_385c;
    float local_3858;
    float local_3854;
    float local_3850;
    float local_384c;
    float local_3848;
    float local_3844;
    undefined1 local_3840[14396]; // Temporary buffer for string processing
    undefined4 uStack_4;

    uStack_4 = 0x48aa5a;
    // param_5 is actually the input string? But it's being cast as float? Probably a mistake.
    // inputString is param_5. It gets modified as a position offset? Weird cast.
    inputString = (char *)(DAT_00e2b1a4 - (float)inputString);
    local_3888 = *(int *)(fontObject + 0x20); // +0x20: pointer to something
    local_38c4 = (char *)0x0;
    fVar12 = 0.0;
    if (*(int *)(fontObject + 0x1c) != 0) {
        fVar12 = (float)*(int *)(*(int *)(fontObject + 0x1c) + 0x18) * *(float *)(fontObject + 0x2c);
    }
    fVar12 = fVar12 * param8;
    fVar13 = fVar12;
    if ((local_3888 != 0) &&
        (fVar13 = (float)*(int *)(local_3888 + 0x18) * *(float *)(fontObject + 0x2c) * param8,
         *(int *)(local_3888 + 0x444) == 0)) {
        return;
    }
    fVar10 = *(float *)(fontObject + 0x34) * fVar12; // +0x34: some multiplier
    local_3858 = (fVar12 - fVar10) * DAT_00e2cd54;
    local_3854 = (fVar10 / fVar13) * param8;
    if (*(int *)(param3 + 0x444) == 0) {
        return;
    }
    local_3894 = DAT_00e2b04c;
    local_3884 = DAT_00e2b04c;
    local_38d9 = '\x01';
    local_38f2 = '\0';
    local_3898 = 0;
    local_38b4 = 0;
    local_38b0 = 0.0;
    local_38f1 = '\0';
    fVar12 = DAT_00e2b04c;
    FUN_004883b0(param9, param6, &local_38b4, param8, fontObject + 0x1c, &local_38c4, &local_38b0,
                 &local_38f1, 0);
    local_3890 = (float)*(int *)(param3 + 0x1c) * param8 * *(float *)(fontObject + 0x2c);
    local_3880 = DAT_01163d98;
    local_387c = DAT_01163d9c;
    local_3878 = DAT_01163da0;
    local_3874 = DAT_01163da4;
    local_38c0 = fVar12;
    if (textObject != 0) {
        cVar2 = *local_38c4;
        local_38ac = 0.0;
        local_38b8 = local_38b0;
        while (cVar2 != '\0') {
            local_388c = 0.0;
            FUN_004883b0(local_38c4, param6, &local_388c, param8, fontObject + 0x1c, &local_38c4, &local_38ac, 0, 0);
            local_38b8 = local_38ac + local_38b8;
            cVar2 = *local_38c4;
        }
        if (textObject == 1) {
            fVar12 = (param7 - local_38b8) * DAT_00e2cd54;
        } else {
            if (textObject != 2) goto LAB_0048acad;
            fVar12 = param7 - local_38b8;
        }
        inputString = (char *)(fVar12 + (float)inputString);
    }

LAB_0048acad:
    local_38bc = 0.0;
    if (param10 != 0) {
        local_38bc = param6 - local_38c0;
        if (local_38bc < 0.0) {
            local_38bc = 0.0;
        }
        if (param10 == 1) {
            local_38bc = local_38bc * DAT_00e2cd54;
        }
    }
    local_38bc = local_38bc + param4;
    local_38a8 = local_3890 + (float)inputString;
    local_38c4 = inputString;
    if (param16 != '\0') {
        fVar12 = *(float *)(fontObject + 0x2c);
        local_38a8 = (float)(int)(fVar12 * DAT_00e2cd54 + local_38a8 / fVar12) * fVar12;
    }

    *(undefined1 **)(fontObject + 0x4c) = local_3840; // +0x4c: buffer pointer
    *(undefined2 *)(fontObject + 0x50) = 0;
    *(undefined2 *)(fontObject + 0x52) = 600;
    local_38f0 = param9;
    local_38ec = 0;
    local_38e8 = 0;
    local_38e4 = 0;
    local_38e0 = FUN_004dd960(); // getRandomOrAdvance? 
    local_38b8 = 0.0;
    iVar9 = local_38ec;
    uVar6 = local_38e4;
    if (param14 != (float *)0x0) {
        local_38b8 = (float)((int)param14[2] + 1);
    }

joined_r0x0048ad9a:
    if (uVar6 != 0) {
        if (uVar6 != 10) {
            local_38d8 = local_38f0 + iVar9;
            local_38d4 = 0;
            local_38d0 = 0;
            local_38cc = 0;
            FUN_004dd960();
            if (local_38cc != 0x5c) {
LAB_0048ae24:
                local_389c = 0;
                do {
                    if (local_38b4 <= local_389c) {
                        if (local_38b8 == 0.0) goto LAB_0048b5c3;
                        local_38b8 = (float)((int)local_38b8 + -1);
                        local_38d4 = 0;
                        local_38d0 = 0;
                        local_38cc = 0;
                        if (local_38b8 == 0.0) {
                            local_38d8 = param9;
                            FUN_004dd960();
                            local_389c = 0;
                        } else {
                            local_38d8 = &DAT_00e337ec;
                            FUN_004dd960();
                            local_389c = local_38b4 - 1;
                        }
                        local_38e4 = local_38cc;
                        iVar9 = local_38d4;
                        uVar6 = local_38cc;
                        local_38f0 = local_38d8;
                        local_38e8 = local_38d0;
                    }
                    local_38c0 = (float)FUN_00487c70(&local_38a4, &local_385c);
                    iVar7 = local_38a4;
                    if (0 < local_38a4) {
                        do {
                            local_38ec = iVar9 + local_38e0;
                            local_38e0 = FUN_004dd960();
                            local_38e8 = local_38e8 + 1;
                            iVar7 = iVar7 + -1;
                            iVar9 = local_38ec;
                            uVar6 = local_38e4;
                        } while (iVar7 != 0);
                    }
                    local_38ac = (float)(uint)uVar6;
                    if (uVar6 == 0) goto LAB_0048b5c3;
                    if (local_38c0 == 0.0) {
                        if (param11 == '\0') {
                            local_38c0 = *(float *)(&DAT_0110a4b8 + local_385c * 8);
                            FUN_00487b30();
                        }
                    } else if (local_38c0 == 1.4013e-45) {
                        DAT_01163d98 = local_3880;
                        DAT_01163d9c = local_387c;
                        DAT_01163da0 = local_3878;
                        DAT_01163da4 = local_3874;
                    }
                    local_38c0 = -NAN;
                    if (local_3888 != 0) {
                        FUN_00487d50(&local_38a4, &local_38c0, *(undefined4 *)(fontObject + 0x30));
                    }
                    fVar12 = local_38c0;
                    iVar7 = local_38a4;
                    if (0 < local_38a4) {
                        do {
                            local_38ec = iVar9 + local_38e0;
                            local_38e0 = FUN_004dd960();
                            local_38e8 = local_38e8 + 1;
                            iVar7 = iVar7 + -1;
                            iVar9 = local_38ec;
                        } while (iVar7 != 0);
                    }
                    if ((int)fVar12 < 0) {
                        if (local_38f2 != '\0') {
                            local_38d9 = '\x01';
                        }
                        local_38f2 = '\0';
                    } else {
                        local_38ac = (float)((uint)fVar12 & 0xffff);
                        if (local_38f2 == '\0') {
                            local_38d9 = '\x01';
                        }
                        local_38f2 = '\x01';
                    }
                    if ((int)fVar12 < 0) {
                        local_38a0 = param8;
                    } else {
                        local_38a0 = local_3854;
                    }
                    if (local_38d9 != '\0') {
                        FUN_0048ba40();
                        if (local_38f2 == '\0') {
                            uVar8 = *(uint *)(param3 + 0x444);
                        } else {
                            uVar8 = *(uint *)(local_3888 + 0x444);
                        }
                        *(char *)(fontObject + 0x24) = local_38f2;
                        if (uVar8 < 0x1000) {
                            puVar5 = &DAT_011a0f28 + uVar8 * 0x38;
                        } else {
                            puVar5 = (undefined1 *)0x0;
                        }
                        local_3894 = DAT_00e2b1a4 / (float)*(ushort *)(puVar5 + 2);
                        if (uVar8 < 0x1000) {
                            puVar5 = &DAT_011a0f28 + uVar8 * 0x38;
                        } else {
                            puVar5 = (undefined1 *)0x0;
                        }
                        local_3884 = DAT_00e2b1a4 / (float)*(ushort *)(puVar5 + 4);
                        if (*(int *)(fontObject + 0x54) == 0) {
                            FUN_00612e00();
                            _DAT_01127804 = 0;
                            _DAT_01127808 = 0;
                            _DAT_0112780c = 0;
                            _DAT_01127810 = 0;
                            _DAT_01127814 = 0;
                            _DAT_01127818 = 0;
                            _DAT_0112781c = 0;
                            if (local_38f2 == '\0') {
                                DAT_01127774 = DAT_01127878;
                                DAT_01127868 = FUN_0060a580(DAT_01127878, "lodBias");
                                if (DAT_012058e8 == &PTR_PTR_01127760) {
                                    FUN_0060a460(DAT_01127774);
                                    FUN_0060aa90(DAT_01127774, DAT_01127868, DAT_01127840);
                                }
                                FUN_00619950();
                            } else {
                                DAT_01127774 = DAT_01127874;
                                DAT_01127868 = FUN_0060a580(DAT_01127874, "lodBias");
                                if (DAT_012058e8 == &PTR_PTR_01127760) {
                                    FUN_0060a460(DAT_01127774);
                                    FUN_0060aa90(DAT_01127774, DAT_01127868, DAT_01127840);
                                }
                                FUN_00619900();
                            }
                            FUN_00619650();
                        }
                        local_38d9 = '\0';
                    }
                    fVar12 = local_38ac;
                    fVar11 = 0.0;
                    local_388c = 0.0;
                    fVar13 = local_38a0;
                    fVar10 = local_3894;
                    fVar14 = local_3884;
                    if (local_38f2 == '\0') {
                        iVar3 = *(int *)(param3 + 0x44 + (((uint)local_38ac & 0xffff) >> 8) * 4);
                        iVar7 = 0;
                        if (iVar3 != 0) {
                            iVar7 = *(int *)(iVar3 + ((uint)local_38ac & 0xff) * 4);
                        }
                        if (iVar7 != 0) {
                            FUN_004cfec0(local_38ac);
                            local_388c = fVar11 * *(float *)(fontObject + 0x28) * fVar13;
                            goto LAB_0048b2b0;
                        }
                    } else if (local_3888 != 0) {
                        iVar3 = *(int *)(local_3888 + 0x44 + (((uint)local_38ac & 0xffff) >> 8) * 4);
                        iVar7 = 0;
                        if (iVar3 != 0) {
                            iVar7 = *(int *)(iVar3 + ((uint)local_38ac & 0xff) * 4);
                        }
LAB_0048b2b0:
                        if (iVar7 != 0) {
                            local_3860 = (float)*(ushort *)(iVar7 + 4) * *(float *)(fontObject + 0x2c) * fVar13;
                            local_3870 = (float)(int)*(short *)(iVar7 + 8) * *(float *)(fontObject + 0x28) * fVar13 + local_388c + local_38bc;
                            local_3868 = (float)*(ushort *)(iVar7 + 2) * *(float *)(fontObject + 0x28) * fVar13;
                            if ((local_38f2 != '\0') || (fVar11 = local_3858, local_38f1 == '\0')) {
                                fVar11 = 0.0;
                            }
                            local_386c = (((float)(int)*(short *)(iVar7 + 10) * *(float *)(fontObject + 0x2c) * fVar13 + local_38a8) - fVar11) - local_3890;
                            local_384c = (float)*(ushort *)(iVar7 + 0xe) * fVar14 * DAT_00e2e638;
                            local_3850 = (float)*(ushort *)(iVar7 + 0xc) * fVar10 * DAT_00e2e638;
                            local_3848 = (float)*(ushort *)(iVar7 + 0x10) * local_3894 * DAT_00e2e638;
                            local_3844 = (float)*(ushort *)(iVar7 + 0x12) * fVar14 * DAT_00e2e638;
                            bVar4 = true;
                            if (clipRect != (float *)0x0) {
                                fVar14 = *clipRect * param6;
                                fVar10 = local_3870 + local_3868;
                                if ((fVar10 < fVar14) || (fVar11 = clipRect[1] * param6 + fVar14, fVar11 < local_3870)) {
                                    bVar4 = false;
                                } else if (fVar14 <= local_3870) {
                                    if (fVar11 < fVar10) {
                                        fVar10 = (fVar11 - local_3870) / local_3868;
                                        local_3848 = local_3848 - (local_3848 - local_3850) * (DAT_00e2b1a4 - fVar10);
                                        local_3868 = fVar10 * local_3868;
                                    }
                                    local_3870 = local_3870 - fVar14;
                                } else {
                                    fVar11 = (fVar10 - fVar14) / local_3868;
                                    fVar13 = DAT_00e2b1a4 - fVar11;
                                    fVar10 = fVar13 * local_3868;
                                    local_3850 = (local_3848 - local_3850) * fVar13 + local_3850;
                                    local_3868 = fVar11 * local_3868;
                                    local_3870 = (fVar10 + local_3870) - fVar14;
                                    fVar13 = local_38a0;
                                }
                            }
                            if ((((maxLines < 0) || (local_38e8 <= maxLines)) && (bVar4)) && ((local_38f2 == '\0' || (param11 == '\0')))) {
                                FUN_0048bab0(local_3870, local_386c, local_3868, local_3860, &local_3850, local_38f2 == '\0', param13);
                                fVar13 = local_38a0;
                            }
                            if (*(float *)(fontObject + 0x3c) == DAT_00e2b05c) {
                                local_38bc = ((float)*(ushort *)(iVar7 + 6) + *(float *)(fontObject + 0x38)) * fVar13 * *(float *)(fontObject + 0x28) + local_38bc + local_388c;
                            } else {
                                local_38bc = *(float *)(fontObject + 0x3c) * fVar13 * *(float *)(fontObject + 0x28) + local_38bc;
                            }
                            local_3898 = (uint)fVar12 & 0xffff;
                        }
                    }
                    local_38ec = iVar9 + local_38e0;
                    local_38e0 = FUN_004dd960();
                    local_38e8 = local_38e8 + 1;
                    local_389c = local_389c + 1;
                    iVar9 = local_38ec;
                    uVar6 = local_38e4;
                } while (true);
            }
            local_38d8 = local_38f0 + iVar9;
            local_38d4 = 0;
            local_38d0 = 0;
            local_38cc = 0;
            local_38c8 = FUN_004dd960();
            local_38d4 = local_38d4 + local_38c8;
            FUN_004dd960();
            if (local_38cc != 0x6e) goto LAB_0048ae24;
        }
        puVar1 = local_38f0 + iVar9;
        local_38d4 = 0;
        local_38d0 = 0;
        local_38cc = 0;
        local_38d8 = puVar1;
        FUN_004dd960();
        if (local_38cc == 0x5c) {
            local_38d4 = 0;
            local_38d0 = 0;
            local_38cc = 0;
            local_38d8 = puVar1;
            local_38c8 = FUN_004dd960();
            local_38d4 = local_38d4 + local_38c8;
            FUN_004dd960();
            if (local_38cc == 0x6e) {
                local_38ec = iVar9 + local_38e0;
                local_38e0 = FUN_004dd960();
                local_38e8 = local_38e8 + 1;
                iVar9 = local_38ec;
            }
        }
        local_38ec = iVar9 + local_38e0;
        local_38e0 = FUN_004dd960();
        iVar9 = local_38ec;
        uVar6 = local_38e4;
        while (local_38e8 = local_38e8 + 1, local_38e4 = uVar6, uVar6 == 0x20) {
            local_38ec = iVar9 + local_38e0;
            local_38e0 = FUN_004dd960();
            iVar9 = local_38ec;
            uVar6 = local_38e4;
        }
        local_38c4 = (char *)((float)local_38c4 + local_38b0);
        fVar12 = (float)local_38c4 + local_3890;
        local_38b4 = 0;
        if (param16 != '\0') {
            fVar13 = *(float *)(fontObject + 0x2c);
            fVar12 = (float)(int)(fVar13 * DAT_00e2cd54 + fVar12 / fVar13) * fVar13;
        }
        local_38f1 = '\0';
        local_38ec = iVar9;
        local_38a8 = fVar12;
        FUN_004883b0(local_38f0 + iVar9, param6, &local_38b4, param8, fontObject + 0x1c, 0, &local_38b0, &local_38f1, 0);
        local_38bc = 0.0;
        if (param10 != 0) {
            local_38bc = param6 - fVar12;
            if (local_38bc < 0.0) {
                local_38bc = 0.0;
            }
            if (param10 == 1) {
                local_38bc = local_38bc * DAT_00e2cd54;
            }
        }
        local_38bc = local_38bc + param4;
        goto LAB_0048b9ce;
    }

LAB_0048b9d7:
    FUN_0048ba40();
    *(undefined4 *)(fontObject + 0x4c) = 0;
    *(undefined2 *)(fontObject + 0x50) = 0;
    *(undefined2 *)(fontObject + 0x52) = 0;
    DAT_01163da4 = local_3874;
    DAT_01163da0 = local_3878;
    DAT_01163d9c = local_387c;
    DAT_01163d98 = local_3880;
    return;

LAB_0048b5c3:
    if ((uVar6 == 10) || (uVar6 == 0xd)) {
        local_38ec = iVar9 + local_38e0;
        local_38e0 = FUN_004dd960();
        local_38e8 = local_38e8 + 1;
        iVar9 = local_38ec;
        uVar6 = local_38e4;
    }
    puVar1 = local_38f0 + iVar9;
    local_38d4 = 0;
    local_38d0 = 0;
    local_38cc = 0;
    local_38d8 = puVar1;
    FUN_004dd960();
    if (local_38cc == 0x5c) {
        local_38d4 = 0;
        local_38d0 = 0;
        local_38cc = 0;
        local_38d8 = puVar1;
        local_38c8 = FUN_004dd960();
        local_38d4 = local_38d4 + local_38c8;
        FUN_004dd960();
        if (local_38cc == 0x6e) {
            iVar7 = 2;
            local_38ec = iVar9;
            do {
                local_38ec = local_38ec + local_38e0;
                local_38e0 = FUN_004dd960();
                local_38e8 = local_38e8 + 1;
                iVar7 = iVar7 + -1;
                iVar9 = local_38ec;
                uVar6 = local_38e4;
            } while (iVar7 != 0);
        }
    }
    while (uVar6 == 0x20) {
        local_38ec = iVar9 + local_38e0;
        local_38e0 = FUN_004dd960();
        local_38e8 = local_38e8 + 1;
        iVar9 = local_38ec;
        uVar6 = local_38e4;
    }
    local_38c4 = (char *)((float)local_38c4 + local_38b0);
    fVar12 = (float)local_38c4 + local_3890;
    local_38b4 = 0;
    if (param16 != '\0') {
        fVar13 = *(float *)(fontObject + 0x2c);
        fVar12 = (float)(int)(fVar13 * DAT_00e2cd54 + fVar12 / fVar13) * fVar13;
    }
    local_38f1 = '\0';
    local_38a8 = fVar12;
    FUN_004883b0(local_38f0 + iVar9, param6, &local_38b4, param8, fontObject + 0x1c, 0, &local_38b0, &local_38f1, 0);
    local_38bc = 0.0;
    if (param10 != 0) {
        local_38bc = param6 - fVar12;
        if (local_38bc < 0.0) {
            local_38bc = 0.0;
        }
        if (param10 == 1) {
            local_38bc = local_38bc * DAT_00e2cd54;
        }
    }
    local_38bc = local_38bc + param4;
    local_3898 = 0;
    if ((float)inputString + param7 < (float)local_38c4) goto LAB_0048b9d7;

LAB_0048b9ce:
    local_3898 = 0;
    goto joined_r0x0048ad9a;
}