// FUNC_NAME: PlayerActionableInfo::canPerformAction
byte __thiscall PlayerActionableInfo::canPerformAction(int thisPtr, undefined4 param2, undefined4 param3, int actionId, undefined4 param5)
{
    int *piVar1;
    char cVar2;
    byte bVar3;
    int iVar4;
    int iVar5;
    undefined4 uVar6;
    int iVar7;
    short sVar8;
    undefined2 uVar9;
    float fVar10;

    bVar3 = false;
    iVar7 = *(int *)(thisPtr + 0x58); // +0x58: some pointer (maybe character/entity)
    switch(actionId) {
    case 0x13: // Action 19
        if ((*(int *)(thisPtr + 0x1b4) != 0) && (*(int *)(thisPtr + 0x1b4) != 0x48)) break;
        goto LAB_007cc525;
    case 0x14: // Action 20
        if ((*(int *)(thisPtr + 0x1b4) != 0) && (*(int *)(thisPtr + 0x1b4) != 0x48)) {
            iVar4 = FUN_00624bd0(0x27a0f69c); // hash lookup
            if (*(int *)(thisPtr + 0x1b4) == 0) {
                iVar5 = 0;
            } else {
                iVar5 = *(int *)(thisPtr + 0x1b4) + -0x48;
            }
            cVar2 = FUN_007cbcd0(iVar7, iVar5, iVar4 == 0, *(undefined4 *)(thisPtr + 0x1d0));
            bVar3 = cVar2 == '\0';
            break;
        }
        goto LAB_007cc5bc;
    case 0x15: // Action 21
        bVar3 = ((byte)(*(uint *)(iVar7 + 0x8e0) >> 10) & 1) != 1;
        break;
    case 0x16: // Action 22
        cVar2 = FUN_00690150(0x37); // check game state flag
        if (cVar2 != '\0') break;
        uVar6 = 0x39;
LAB_007cc5ad:
        cVar2 = FUN_00690150(uVar6);
        if (cVar2 != '\0') break;
LAB_007cc5bc:
        bVar3 = 1;
        break;
    case 0x17: // Action 23
        cVar2 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0x18))(); // vtable+0x18: isFinished?
        if (((cVar2 == '\0') &&
            (cVar2 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0x14))(), cVar2 != '\0')) && // vtable+0x14: isActive?
           ((iVar7 = *(int *)(thisPtr + 0x1a0) * 0x2c +
                     *(int *)(*(int *)(*(int *)(thisPtr + 0x1c0) + 0x10) + 4), iVar7 != 0 &&
            ((*(uint *)(iVar7 + 0x24) >> 6 & 1) != 0)))) {
            uVar6 = FUN_00798f50(0x2c); // get action by ID
            cVar2 = FUN_0079e970(uVar6); // is action active?
            if ((cVar2 != '\0') && (_DAT_00d577a0 < *(float *)(thisPtr + 0x30))) {
                bVar3 = 1;
                break;
            }
        }
        goto LAB_007cc5d4;
    case 0x18: // Action 24
        if (((((*(byte *)(thisPtr + 0x1d0) & 1) == 0) && (cVar2 = FUN_00690150(0x25), cVar2 == '\0')) &&
            (cVar2 = FUN_00690150(0x27), cVar2 == '\0')) && (_DAT_00d577a0 < *(float *)(thisPtr + 0x30))
           ) {
            bVar3 = 1;
            cVar2 = FUN_006fd7b0(); // some global check
            if (cVar2 == '\0') {
                bVar3 = 0;
            }
        }
        break;
    case 0x19: // Action 25
        cVar2 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0x14))(); // isActive?
        if (cVar2 != '\0') {
            piVar1 = *(int **)(thisPtr + 0x1c0);
            cVar2 = (**(code **)(*piVar1 + 0x24))(); // vtable+0x24: isBlocked?
            if (((cVar2 == '\0') && ((*(byte *)(*(int *)(piVar1[4] + 4) + 0x20) & 1) == 0)) &&
               ((*(byte *)(thisPtr + 0x1d0) & 1) == 0)) {
                bVar3 = 1;
            }
        }
        break;
    case 0x1a: // Action 26
        cVar2 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0x18))(); // isFinished?
        if ((cVar2 != '\0') &&
           ((cVar2 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0x20))(), cVar2 == '\0' || // vtable+0x20: isInterruptible?
            (iVar7 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0xc))(3), iVar7 == 0)))) { // vtable+0xc: getState?
            bVar3 = 1;
        }
        break;
    case 0x1b: // Action 27
        cVar2 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0x18))(); // isFinished?
        if (((cVar2 != '\0') &&
            (cVar2 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0x20))(), cVar2 != '\0')) && // isInterruptible?
           (iVar7 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0xc))(3), iVar7 != 0)) { // getState?
            bVar3 = 1;
        }
        break;
    case 0x1c: // Action 28
        if (*(float *)(thisPtr + 0x1c4) <= 0.0) {
            bVar3 = 1;
            *(undefined2 *)(thisPtr + 0x1d4) = 3;
            break;
        }
        goto LAB_007cc5d4;
    case 0x1d: // Action 29
        cVar2 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0x14))(); // isActive?
        if ((cVar2 != '\0') &&
           ((*(byte *)(*(int *)(*(int *)(*(int *)(thisPtr + 0x1c0) + 0x10) + 4) + 0x20) & 1) == 0)) {
            bVar3 = 1;
        }
        break;
    case 0x1e: // Action 30
        if (*(float *)(thisPtr + 0x30) <= _DAT_00d577a0) break;
        bVar3 = 1;
        uVar6 = FUN_00798f50(0x2d); // get action by ID
        cVar2 = FUN_0079e970(uVar6); // is active?
        if (cVar2 == '\0') {
            uVar6 = FUN_00798f50(0x2e);
            cVar2 = FUN_0079e970(uVar6);
            if (cVar2 == '\0') {
                uVar6 = FUN_00798f50(0x2f);
                cVar2 = FUN_0079e970(uVar6);
                if (cVar2 == '\0') {
                    uVar6 = FUN_00798f50(0x30);
                    cVar2 = FUN_0079e970(uVar6);
                    if (cVar2 == '\0') goto LAB_007cc5d4;
                    sVar8 = 1;
                } else {
                    sVar8 = 0;
                }
            } else {
                sVar8 = 2;
            }
        } else {
            sVar8 = 4;
        }
        iVar7 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0xc))(sVar8); // getState?
        if ((iVar7 != 0) &&
           (iVar7 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0xc))(sVar8),
           iVar7 != *(int *)(thisPtr + 0x1c0))) {
            *(short *)(thisPtr + 0x1d4) = sVar8;
            if ((*(int *)(thisPtr + 0x1b4) == 0) || (*(int *)(thisPtr + 0x1b4) == 0x48)) break;
            if (*(int *)(thisPtr + 0x1b4) == 0) {
                iVar7 = 0;
            } else {
                iVar7 = *(int *)(thisPtr + 0x1b4) + -0x48;
            }
            if ((*(uint *)(iVar7 + 0x1f98) >> 7 & 1) != 0) {
                if (sVar8 == 0) {
                    uVar6 = 0x7d541a24;
                } else {
                    if (sVar8 != 1) goto LAB_007cc8fa;
                    uVar6 = 0x4f2ec11b;
                }
                FUN_00894c90(uVar6); // play sound
            }
LAB_007cc8fa:
            *(int *)(iVar7 + 0x1f48) = (int)*(short *)(thisPtr + 0x1d4);
            break;
        }
        goto LAB_007cc5d4;
    default:
        bVar3 = FUN_007ab790(param2, param3, actionId, param5);
        break;
    case 0x20: // Action 32
        if ((*(int **)(thisPtr + 0x1c0) != (int *)0x0) &&
           (cVar2 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0x14))(), cVar2 != '\0')) { // isActive?
            cVar2 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0x24))(); // isBlocked?
            if (cVar2 != '\0') {
                *(int *)(thisPtr + 0x78) =
                     *(int *)(thisPtr + 0x1a0) * 0x2c +
                     *(int *)(*(int *)(*(int *)(thisPtr + 0x1c0) + 0x10) + 4);
                if (*(int *)(thisPtr + 0x1b4) == 0) {
                    iVar7 = 0;
                } else {
                    iVar7 = *(int *)(thisPtr + 0x1b4) + -0x48;
                }
                bVar3 = FUN_007ca9e0(*(undefined4 *)(thisPtr + 0x30), *(undefined4 *)(thisPtr + 0x58), iVar7);
            }
            break;
        }
        goto LAB_007cc525;
    case 0x21: // Action 33
        cVar2 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0x1c))(); // vtable+0x1c: some check
        if (cVar2 != '\0') {
            bVar3 = 1;
        }
        break;
    case 0x22: // Action 34
        bVar3 = (byte)(*(uint *)(thisPtr + 0x1d0) >> 1) & 1;
        break;
    case 0x23: // Action 35
        if ((*(int *)(thisPtr + 0x1b4) != 0) && (*(int *)(thisPtr + 0x1b4) != 0x48)) {
            if (*(int *)(thisPtr + 0x1b4) == 0) {
                iVar7 = 0;
            } else {
                iVar7 = *(int *)(thisPtr + 0x1b4) + -0x48;
            }
            if ((*(int *)(iVar7 + 0x1f3c) != 0) && (cVar2 = FUN_006f97f0(iVar7), cVar2 != '\0')) { // isAlive?
                *(undefined4 *)(thisPtr + 0x1bc) = *(undefined4 *)(iVar7 + 0x1f3c);
                bVar3 = 1;
            }
        }
        break;
    case 0x24: // Action 36
        cVar2 = FUN_007cb580(iVar7); // check distance?
        if ((cVar2 != '\0') && (_DAT_00d577a0 < *(float *)(thisPtr + 0x30))) {
            bVar3 = 1;
            break;
        }
        goto LAB_007cc5d4;
    case 0x25: // Action 37
        cVar2 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0x14))(); // isActive?
        if ((cVar2 != '\0') &&
           ((*(byte *)(*(int *)(*(int *)(*(int *)(thisPtr + 0x1c0) + 0x10) + 4) + 0x20) & 1) != 0)) {
            bVar3 = 1;
        }
        break;
    case 0x2b: // Action 43
        if ((*(int *)(thisPtr + 0x1b4) != 0) && (*(int *)(thisPtr + 0x1b4) != 0x48)) {
            if (*(int *)(thisPtr + 0x1b4) == 0) {
                iVar7 = 0;
            } else {
                iVar7 = *(int *)(thisPtr + 0x1b4) + -0x48;
            }
            bVar3 = *(int *)(iVar7 + 0x1f3c) == 0;
            if ((bool)bVar3) break;
            cVar2 = FUN_00690150(0x30);
            if (cVar2 != '\0') {
                uVar6 = 0x30;
                goto LAB_007cc5ad;
            }
            goto LAB_007cc5bc;
        }
        goto LAB_007cc525;
    case 0x2c: // Action 44
        if ((*(int *)(thisPtr + 0x1b4) != 0) && (*(int *)(thisPtr + 0x1b4) != 0x48)) {
            if (*(int *)(thisPtr + 0x1b4) == 0) {
                iVar7 = 0;
            } else {
                iVar7 = *(int *)(thisPtr + 0x1b4) + -0x48;
            }
            cVar2 = FUN_006f97f0(iVar7); // isAlive?
            bVar3 = cVar2 == '\0';
            break;
        }
LAB_007cc525:
        bVar3 = 1;
        break;
    case 0x2d: // Action 45
        if ((*(int **)(thisPtr + 0x1c0) != (int *)0x0) &&
           (cVar2 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0x14))(), cVar2 != '\0')) { // isActive?
            cVar2 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0x24))(); // isBlocked?
            if (cVar2 == '\0') {
                if (((*(int *)(thisPtr + 0x1b4) != 0) && (*(int *)(thisPtr + 0x1b4) != 0x48)) &&
                   (iVar7 = FUN_00625050(0x187b7e2b,0), iVar7 != 0)) {
                    bVar3 = FUN_007caac0(*(undefined4 *)(thisPtr + 0x30));
                }
            } else {
                bVar3 = FUN_007caac0(*(undefined4 *)(thisPtr + 0x30));
            }
        }
        break;
    case 0x2e: // Action 46
        cVar2 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0x18))(); // isFinished?
        if ((cVar2 != '\0') && (DAT_0112ba54 != '\0')) {
            bVar3 = 1;
        }
        break;
    case 0x2f: // Action 47
        if (*(float *)(thisPtr + 0x30) <= _DAT_00d577a0) break;
        uVar6 = FUN_00798f50(0x2e);
        cVar2 = FUN_0079e970(uVar6);
        if (cVar2 == '\0') {
            uVar6 = FUN_00798f50(0x2f);
            cVar2 = FUN_0079e970(uVar6);
            if (cVar2 == '\0') {
                uVar6 = FUN_00798f50(0x30);
                cVar2 = FUN_0079e970(uVar6);
                if (cVar2 != '\0') {
                    DAT_0112ba58 = *(int *)(thisPtr + 0x1e0);
                }
            } else {
                DAT_0112ba58 = *(int *)(thisPtr + 0x1dc);
            }
            bVar3 = 0;
            if (DAT_0112ba58 == 0) break;
            uVar9 = 0;
        } else {
            DAT_0112ba58 = 0;
            uVar9 = 1;
        }
        bVar3 = 1;
        iVar7 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0xc))(uVar9);
        if ((iVar7 != 0) &&
           (iVar7 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0xc))(uVar9),
           iVar7 != *(int *)(thisPtr + 0x1c0))) {
            *(undefined2 *)(thisPtr + 0x1d4) = uVar9;
            DAT_0112ba54 = '\0';
            break;
        }
        goto LAB_007cc5d4;
    case 0x30: // Action 48
        bVar3 = 0;
        if ((_DAT_00d577a0 < *(float *)(thisPtr + 0x30)) && (2 < DAT_0112ba5c)) {
            uVar6 = FUN_00798f50(0x2d);
            cVar2 = FUN_0079e970(uVar6);
            if (cVar2 != '\0') {
                bVar3 = 1;
            }
        }
        break;
    case 0x31: // Action 49
        if ((*(int **)(thisPtr + 0x1c0) != (int *)0x0) &&
           (cVar2 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0x14))(), cVar2 != '\0')) { // isActive?
            cVar2 = (**(code **)(**(int **)(thisPtr + 0x1c0) + 0x24))(); // isBlocked?
            if (cVar2 == '\0') {
                if (*(int *)(thisPtr + 0x1b4) == 0) {
                    bVar3 = FUN_007f7b90();
                } else {
                    bVar3 = FUN_007f7b90();
                }
            }
            break;
        }
LAB_007cc5d4:
        bVar3 = 0;
    }
    if (*(char *)(DAT_01223394 + 0x54) != '\0') {
        if (*(float *)(DAT_01223394 + 0x5c) <= *(float *)(DAT_01223394 + 0x70)) {
            if (*(int *)(DAT_01223394 + 0x58) == 0) {
                return bVar3;
            }
            *(uint *)(thisPtr + 0x1d0) = *(uint *)(thisPtr + 0x1d0) & 0xfffffdff;
            return bVar3;
        }
        fVar10 = *(float *)(DAT_01223394 + 0x70) / *(float *)(DAT_01223394 + 0x5c);
        if (*(int *)(DAT_01223394 + 0x58) != 0) {
            fVar10 = _DAT_00d5780c - fVar10;
        }
        if (DAT_00e44598 < fVar10) {
            return bVar3;
        }
    }
    *(uint *)(thisPtr + 0x1d0) = *(uint *)(thisPtr + 0x1d0) & 0xfffffdff;
    return bVar3;
}