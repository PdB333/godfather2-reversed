// FUNC_NAME: DebugRenderer::processDrawList
int* DebugRenderer::processDrawList(int* thisPtr, int param_2, bool param_3, undefined4 param_4, float param_5)
{
    undefined4 uVar1;
    bool bVar2;
    int* piVar3;
    int iVar4;
    int* piVar5;
    int iVar6;
    float in_XMM0_Da;
    float fVar7;
    float fVar8;
    int local_7c;
    int local_78;
    int local_70;
    int local_68;
    int local_60;
    int iStack_5c;
    int iStack_58;
    undefined4 uStack_54;
    undefined1 local_50 [16];
    undefined1 local_40 [16];
    int local_30;
    int iStack_2c;
    int iStack_28;
    float fStack_24;
    int local_20;
    int iStack_1c;
    int iStack_18;
    int iStack_14;

    piVar3 = (int *)*thisPtr;
    if ((piVar3 != (int *)0x0) && (piVar3 = piVar3 + -1, piVar3 != (int *)0x0)) {
        piVar3 = (int *)someAllocFunction(); // likely frame allocation
        fVar7 = in_XMM0_Da * DAT_00e2b04c - DAT_00e2b1a4;
        if (fVar7 < 0.0) {
            fVar7 = 0.0;
        }
        fVar7 = fVar7 * param_5;
        if (DAT_00e2af44 <= fVar7) {
            if (*(int *)(&DAT_011253f4 + (uint)DAT_01125388 * 0x38) != 0) {
                FUN_0060b020(DAT_011252e8, *(int *)(&DAT_011253f4 + (uint)DAT_01125388 * 0x38), &DAT_01218e00);
            }
            if ((*(byte *)(param_2 + 0x44) & 0x20) != 0) {
                FUN_0053b690(DAT_01163840 != '\0');
            }
            if ((param_3 != '\0') || ((*(byte *)(param_2 + 0x44) & 0x20) != 0)) {
                FUN_0053b610();
            }
            fVar8 = DAT_00e2b1a4;
            if (*(char *)(param_2 + 0x48) == '\x01') {
                fVar8 = 0.0;
            }
            FUN_0053b780(param_4, fVar8);
            FUN_0053b550();
            piVar3 = (int *)((short)thisPtr[4] * 0x55555556);
            local_68 = (int)(short)thisPtr[4] / 3;
            iVar6 = 0;
            if (0 < local_68) {
                piVar3 = (int *)(thisPtr[2] + 0xc);
                iVar4 = local_68;
                do {
                    if ((((piVar3[4] == 0) || ((*(byte *)(piVar3[4] + 0xb2) & 1) != 0)) && (*piVar3 != 0)) &&
                       ((*(byte *)(*piVar3 + 8) & 2) != 0)) {
                        iVar6 = iVar6 + 1;
                    }
                    piVar3 = piVar3 + 0x18;
                    iVar4 = iVar4 + -1;
                } while (iVar4 != 0);
            }
            if (param_3 != '\0') {
                local_60 = thisPtr[0x18];
                iStack_5c = thisPtr[0x19];
                iStack_58 = thisPtr[0x1a];
                piVar3 = *(int **)(&DAT_01125410 + (uint)DAT_01125388 * 0x38);
                uStack_54 = *(undefined4 *)(param_2 + 0x40);
                if (piVar3 != (int *)0x0) {
                    piVar3 = (int *)FUN_0060add0(DAT_011252e8, piVar3, &local_60);
                }
            }
            if ((0 < iVar6) && (piVar3 = (int *)FUN_0060cd00(4, iVar6 * 3, 0, 1, 0), piVar3 != (int *)0x0)) {
                iStack_28 = 0;
                iStack_2c = 0;
                local_30 = 0;
                iStack_14 = 0;
                iStack_18 = 0;
                iStack_1c = 0;
                local_7c = (param_3 != '\0') - 1;
                local_20 = 0;
                bVar2 = false;
                fStack_24 = fVar7;
                if (0 < local_68) {
                    piVar5 = piVar3 + 4;
                    local_78 = -0x10;
                    local_70 = 0;
                    do {
                        if (local_7c == 0) {
                            local_78 = local_78 + 0x10;
                            local_7c = (int)*(float *)(thisPtr[3] + 0xc + local_78);
                            bVar2 = true;
                        }
                        iVar6 = *(int *)(local_70 + 0x1c + thisPtr[2]);
                        local_7c = local_7c + -3;
                        iVar4 = local_70 + thisPtr[2];
                        if (((iVar6 == 0) || ((*(byte *)(iVar6 + 0xb2) & 1) != 0)) &&
                           ((*(int *)(iVar4 + 0xc) != 0 && ((*(byte *)(*(int *)(iVar4 + 0xc) + 8) & 2) != 0)))) {
                            uVar1 = *(undefined4 *)(iVar4 + 0x18);
                            if (bVar2) {
                                FUN_0044c4c0(uVar1, thisPtr[3] + local_78, &local_60);
                                iStack_14 = FUN_00522b00();
                                bVar2 = false;
                            }
                            FUN_0056b480(uVar1, iVar4, &local_60);
                            FUN_00414aa0();
                            local_20 = *(int *)(iVar4 + 0x10);
                            iStack_1c = *(int *)(iVar4 + 0x14);
                            *piVar3 = local_30;
                            piVar3[1] = iStack_2c;
                            piVar3[2] = iStack_28;
                            piVar3[3] = (int)fStack_24;
                            *piVar5 = local_20;
                            piVar5[1] = iStack_1c;
                            piVar5[2] = iStack_18;
                            piVar5[3] = iStack_14;
                            iVar6 = thisPtr[2] + local_70 + 0x20;
                            FUN_0056b480(uVar1, iVar6, local_50);
                            FUN_00414aa0();
                            local_20 = *(int *)(iVar6 + 0x10);
                            iStack_1c = *(int *)(iVar6 + 0x14);
                            piVar3[8] = local_30;
                            piVar3[9] = iStack_2c;
                            piVar3[10] = iStack_28;
                            piVar3[0xb] = (int)fStack_24;
                            piVar5[8] = local_20;
                            piVar5[9] = iStack_1c;
                            piVar5[10] = iStack_18;
                            piVar5[0xb] = iStack_14;
                            iVar6 = local_70 + 0x40 + thisPtr[2];
                            FUN_0056b480(uVar1, iVar6, local_40);
                            FUN_00414aa0();
                            local_20 = *(int *)(iVar6 + 0x10);
                            iStack_1c = *(int *)(iVar6 + 0x14);
                            piVar3[0x10] = local_30;
                            piVar3[0x11] = iStack_2c;
                            piVar3[0x12] = iStack_28;
                            piVar3[0x13] = (int)fStack_24;
                            piVar5[0x10] = local_20;
                            piVar5[0x11] = iStack_1c;
                            piVar5[0x12] = iStack_18;
                            piVar5[0x13] = iStack_14;
                            piVar3 = piVar3 + 0x18;
                            piVar5 = piVar5 + 0x18;
                        }
                        local_70 = local_70 + 0x60;
                        local_68 = local_68 + -1;
                    } while (local_68 != 0);
                }
                piVar3 = (int *)FUN_0060cde0();
            }
        }
    }
    return piVar3;
}