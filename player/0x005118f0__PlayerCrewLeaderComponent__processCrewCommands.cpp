// FUNC_NAME: PlayerCrewLeaderComponent::processCrewCommands
void __thiscall processCrewCommands(uint param_1)
{
    int *piVar1;
    uint uVar2;
    float fVar3;
    float fVar4;
    char cVar5;
    int iVar6;
    int iVar7;
    int iVar8;
    int in_EAX;
    int iVar9;
    int iVar10;
    bool bVar11;
    int iVar12;
    int iVar13;
    byte bVar14;
    int iVar15;
    uint uVar16;
    int unaff_EDI;
    int unaff_FS_OFFSET;
    float fVar17;
    byte local_48;
    uint local_44;
    float local_40;
    int local_34;
    float local_20;
    float fStack_1c;
    float fStack_18;
    float fStack_14;
    
    iVar6 = **(int **)(unaff_FS_OFFSET + 0x2c);
    *(float *)(unaff_EDI + 0x2c) = *(float *)(unaff_EDI + 0x4c) * *(float *)(unaff_EDI + 0x2c);
    cVar5 = *(char *)(*(int *)(DAT_012233a8 + 4) + 0x84);
    bVar14 = (byte)((uint)*(undefined4 *)(*(int *)(unaff_EDI + 8) + *(int *)(iVar6 + 8)) >> 0x1a) & 1;
    if ((bVar14 != 0) || (local_48 = 1, *(char *)(*(int *)(unaff_EDI + 0x10) + 0x171) == '\0')) {
        local_48 = 0;
    }
    if (DAT_012058d0 < 0x19) {
        DAT_012058d0 = 0x19;
    }
    if (0x19 < DAT_00f15988) {
        DAT_00f15988 = 0x19;
    }
    _DAT_011f3a3c = 7;
    if (DAT_012058d0 < 0x18) {
        DAT_012058d0 = 0x18;
    }
    if (0x18 < DAT_00f15988) {
        DAT_00f15988 = 0x18;
    }
    _DAT_011f3a38 = (uint)*(byte *)(*(int *)(unaff_EDI + 0x10) + 0x171);
    if (DAT_012058d0 < 0xf) {
        DAT_012058d0 = 0xf;
    }
    if (0xf < DAT_00f15988) {
        DAT_00f15988 = 0xf;
    }
    _DAT_011f3a14 = (uint)local_48;
    if (DAT_012058d0 < 7) {
        DAT_012058d0 = 7;
    }
    if (7 < DAT_00f15988) {
        DAT_00f15988 = 7;
    }
    _DAT_011f39f4 = (uint)(~*(byte *)(*(int *)(unaff_EDI + 0x10) + 0x10c) & 1);
    if (DAT_012058d0 < 0xe) {
        DAT_012058d0 = 0xe;
    }
    if (0xe < DAT_00f15988) {
        DAT_00f15988 = 0xe;
    }
    _DAT_011f3a10 = (uint)((byte)((uint)*(undefined4 *)(*(int *)(unaff_EDI + 0x10) + 0x108) >> 0x1c) & 1);
    if (DAT_012058d0 < 0x1b) {
        DAT_012058d0 = 0x1b;
    }
    if (0x1a < DAT_00f15988) {
        DAT_00f15988 = 0x1b;
    }
    _DAT_011f3a44 = (uint)(bVar14 == 0);
    FUN_004ec7a0();
    local_44 = param_1;
    if (bVar14 == 0) {
        PTR_FUN_0110ac14 = FUN_006124c0;
        PTR_FUN_0110ac18 = FUN_006124b0;
        _DAT_0110ac24 = DAT_00e2b1a4;
    }
    local_34 = in_EAX;
    if (in_EAX != 0) {
        do {
            iVar13 = *(int *)(iVar6 + 8);
            uVar16 = local_44 & 7;
            piVar1 = (int *)(unaff_EDI + 0x80 + ((int)local_44 >> 3) * 8);
            iVar7 = *piVar1;
            iVar10 = uVar16 * 0x50 + iVar13;
            if ((*(byte *)(iVar7 + iVar10 + 0x54) & 1) == 0) {
                FUN_0050a810(unaff_EDI + 0x10, piVar1, 0x3f800000);
                local_20 = *(float *)(unaff_EDI + 0x20) * local_20;
                fStack_1c = *(float *)(unaff_EDI + 0x24) * fStack_1c;
                fStack_18 = *(float *)(unaff_EDI + 0x28) * fStack_18;
                fStack_14 = *(float *)(unaff_EDI + 0x2c) * fStack_14;
                bVar11 = DAT_00e2af44 < fStack_14;
                if (bVar14 != 0) {
                    if (fStack_14 <= DAT_00e2af44) goto LAB_00511da4;
                    if (cVar5 == '\0') {
                        if (DAT_012058d0 < 0x1b) {
                            DAT_012058d0 = 0x1b;
                        }
                        if (0x1a < DAT_00f15988) {
                            DAT_00f15988 = 0x1b;
                        }
                        _DAT_011f3a44 = (uint)(_DAT_0110ac24 > fStack_14);
                    }
                    else {
                        bVar11 = bVar11 && _DAT_0110ac24 <= fStack_14;
                    }
                }
                if (bVar11) {
                    iVar8 = *piVar1;
                    fVar17 = *(float *)(iVar8 + uVar16 * 4 + iVar13);
                    if ((*(uint *)(*(int *)(unaff_EDI + 0x10) + 0x108) & 0x20000000) != 0) {
                        fVar17 = fVar17 - (*(float *)(iVar8 + 0x58 + iVar10) - DAT_00e2b1a4) *
                                          *(float *)(*(int *)(unaff_EDI + 0x14) + 0xc);
                    }
                    iVar13 = *(int *)(unaff_EDI + 0x14);
                    local_40 = *(float *)(iVar13 + 0x70) * fVar17;
                    fVar17 = *(float *)(iVar13 + 0x74) * fVar17;
                    if ((*(byte *)(*(int *)(unaff_EDI + 0x10) + 0x10c) & 0x80) == 0) {
                        local_40 = (float)(int)((local_40 - (float)(int)local_40) * *(float *)(iVar13 + 0x80)) *
                                   *(float *)(iVar13 + 0x88);
                        fVar17 = (float)(int)((fVar17 - (float)(int)fVar17) * *(float *)(iVar13 + 0x84)) *
                                 *(float *)(iVar13 + 0x8c);
                    }
                    uVar2 = (uint)local_40 | (*(byte *)(iVar8 + 0x5c + iVar10) & 0xffffff80) << 0x18;
                    fVar3 = *(float *)(iVar8 + 0x40 + iVar10);
                    fVar4 = *(float *)(unaff_EDI + 0x34);
                    if (*(int *)(unaff_EDI + 0x54) != 0) {
                        iVar8 = *(int *)(*(int *)(unaff_EDI + 0x50) + 0x90);
                        _DAT_012278b0 = *(undefined4 *)(iVar13 + 0x88);
                        _DAT_012278b4 = *(undefined4 *)(*(int *)(unaff_EDI + 0x14) + 0x8c);
                        iVar13 = *(int *)(iVar8 + 0x34);
                        _DAT_012278b8 = uVar2;
                        _DAT_012278bc = fVar17;
                        _DAT_012278c0 = local_20;
                        _DAT_012278c4 = fStack_1c;
                        _DAT_012278c8 = fStack_18;
                        _DAT_012278cc = fStack_14;
                        if (iVar13 != 0) {
                            iVar12 = 0;
                            iVar15 = iVar13;
                            do {
                                iVar9 = *(int *)(iVar8 + 0x50) + iVar12;
                                if (*(int *)(iVar9 + 0x80) == 0) {
                                    *(undefined **)(iVar9 + 0x80) = &DAT_012278b0;
                                }
                                iVar12 = iVar12 + 0xb0;
                                iVar15 = iVar15 + -1;
                            } while (iVar15 != 0);
                        }
                        FUN_00510b50(unaff_EDI, piVar1, uVar16,
                                     *(undefined4 *)(*(int *)(unaff_EDI + 0x54) + (uint)*(ushort *)(iVar7 + iVar10 + 0x56) * 4));
                        FUN_00511800(unaff_EDI, fVar3 * fVar4, &local_20);
                        if (iVar13 != 0) {
                            iVar10 = 0;
                            do {
                                *(undefined4 *)(*(int *)(iVar8 + 0x50) + 0x80 + iVar10) = 0;
                                iVar10 = iVar10 + 0xb0;
                                iVar13 = iVar13 + -1;
                            } while (iVar13 != 0);
                        }
                    }
                }
            }
LAB_00511da4:
            local_44 = local_44 + 1;
            if ((int)*(short *)(unaff_EDI + 0x6e) <= (int)local_44) {
                local_44 = local_44 - (int)*(short *)(unaff_EDI + 0x6e);
            }
            local_34 = local_34 + -1;
        } while (local_34 != 0);
    }
    if (bVar14 == 0) {
        PTR_FUN_0110ac14 = PTR_FUN_0110ac1c;
        PTR_FUN_0110ac18 = PTR_FUN_0110ac20;
        _DAT_0110ac24 = DAT_0110ac28;
    }
    if (DAT_012058d0 < 0x1b) {
        DAT_012058d0 = 0x1b;
    }
    if (0x1a < DAT_00f15988) {
        DAT_00f15988 = 0x1b;
    }
    _DAT_011f3a44 = 0;
    if (DAT_012058d0 < 0x19) {
        DAT_012058d0 = 0x19;
    }
    if (0x19 < DAT_00f15988) {
        DAT_00f15988 = 0x19;
    }
    _DAT_011f3a3c = 7;
    if (DAT_012058d0 < 0x18) {
        DAT_012058d0 = 0x18;
    }
    if (0x18 < DAT_00f15988) {
        DAT_00f15988 = 0x18;
    }
    _DAT_011f3a38 = 0;
    if (DAT_012058d0 < 0xf) {
        DAT_012058d0 = 0xf;
    }
    if (0xf < DAT_00f15988) {
        DAT_00f15988 = 0xf;
    }
    _DAT_011f3a14 = 0;
    if (DAT_012058d0 < 7) {
        DAT_012058d0 = 7;
    }
    if (7 < DAT_00f15988) {
        DAT_00f15988 = 7;
    }
    _DAT_011f39f4 = 1;
    if (DAT_012058d0 < 0xe) {
        DAT_012058d0 = 0xe;
    }
    if (0xe < DAT_00f15988) {
        DAT_00f15988 = 0xe;
    }
    _DAT_011f3a10 = 1;
    FUN_00417cf0(1, 5, 6);
    return;
}