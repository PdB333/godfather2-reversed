// FUNC_NAME: PlayerSM::update
undefined1 __thiscall PlayerSM::update(PlayerSM* thisPtr, int param2, float param3, int param4, float param5, undefined4 param6)
{
    bool bVar1;
    bool bVar2;
    char cVar3;
    undefined1 uVar4;
    int iVar5;
    undefined4 uVar6;
    float10 extraout_ST0;
    float fVar7;
    undefined4 local_20;
    float local_1c;
    undefined8 local_18;
    float local_10;
    undefined8 local_c;
    float local_4;

    uVar4 = 1;
    switch((int)param5 - 0xe) {
    case 0: // state 14
        FUN_00758620();
        cVar3 = FUN_00756f90();
        if (cVar3 == '\0') {
            iVar5 = *thisPtr;
            uVar6 = FUN_007484f0(1,0,0,0x3f800000,0x3f800000); // color? alpha?
            (**(code **)(iVar5 + 0x2c))(uVar6); // call virtual func at vtable+0x2c
            return 1;
        }
        break;
    case 1: // state 15
        FUN_00757960();
        return 1;
    case 2: // state 16
        if (thisPtr[0x42] != 0) {
            FUN_005f7860(thisPtr[0x42]);
            thisPtr[0x42] = 0;
        }
        cVar3 = FUN_007578c0();
        if (cVar3 != '\0') {
            FUN_007577a0();
            return 1;
        }
        break;
    case 3: // state 17
        thisPtr[0x2a] = thisPtr[0x2a] | 0x84000;
        FUN_006016e0(thisPtr + 0x18);
        FUN_00757770();
        return 1;
    default:
        uVar4 = FUN_0075e390(param2, param3, param4, param5, param6);
        break;
    case 7: // state 21
        FUN_00757e60(param3, &local_18);
        param5 = (float)((uint)param5 & 0xffffff00);
        FUN_0075d6e0(&local_c, &local_18, param3, &param5);
        if (param5._0_1_ != '\0') {
            thisPtr[0x2a] = thisPtr[0x2a] | 0x800000;
        }
        cVar3 = FUN_007448b0();
        if (cVar3 != '\0') {
            FUN_0075e480(param3, &local_c, *(byte *)((int)thisPtr + 0xaa) & 1); // +0xaa flag
            thisPtr[0x2a] = thisPtr[0x2a] & 0xfffeffff;
            thisPtr[0x2a] = thisPtr[0x2a] & 0xfff7ffff;
            return 1;
        }
        FUN_0075ded0(param3, &local_c);
        thisPtr[0x2a] = thisPtr[0x2a] & 0xfff7ffff;
        return 1;
    case 8: // state 22
        FUN_00757d00(param3);
        thisPtr[0x2a] = thisPtr[0x2a] | 0x8000;
        iVar5 = FUN_00471610(); // get some manager/player pointer
        *(undefined8 *)(thisPtr + 0x56) = *(undefined8 *)(iVar5 + 0x30); // copy position?
        thisPtr[0x58] = *(int *)(iVar5 + 0x38);
        return 1;
    case 9: // state 23
        FUN_004abdd0(0x4000); // trigger some event
        return 1;
    case 10: // state 24
        FUN_004abdd0(0x20);
        return 1;
    case 0xb: // state 25
        if (thisPtr[0x43] != 0) {
            thisPtr[0x2a] = thisPtr[0x2a] | 0x4000;
        }
        thisPtr[0x2a] = thisPtr[0x2a] & 0xfff7ffff;
        return 1;
    case 0xc: // state 26
        thisPtr[0x2a] = thisPtr[0x2a] | 0x8000;
        return 1;
    case 0xe: // state 28
        iVar5 = *thisPtr;
        thisPtr[0x4c] = 0;
        uVar6 = FUN_007484f0(1,0,0,0x3f800000,0x3f800000);
        (**(code **)(iVar5 + 0x2c))(uVar6);
        thisPtr[0x2a] = thisPtr[0x2a] & 0xffffdfff;
        FUN_005f5ce0();
        FUN_005f5ce0();
        iVar5 = FUN_00471610();
        FUN_0045c470(thisPtr + 0x56, (undefined8 *)(iVar5 + 0x30)); // copy transform
        if (extraout_ST0 < (float10)1) {
            *(undefined8 *)(thisPtr + 0x56) = *(undefined8 *)(iVar5 + 0x30);
            iVar5 = *(int *)(iVar5 + 0x38);
            thisPtr[0x54] = thisPtr[0x54] + 1;
            thisPtr[0x58] = iVar5;
            return 1;
        }
        thisPtr[0x54] = 0;
        return 1;
    case 0xf: // state 29
        iVar5 = *thisPtr;
        uVar6 = FUN_007484f0(1,0,0,0x3f800000,0x3f800000);
        (**(code **)(iVar5 + 0x2c))(uVar6);
        return 1;
    case 0x10: // state 30
        FUN_007f8980();
        return 1;
    case 0x11: // state 31
        if (thisPtr[0x2c] != 0) {
            local_1c = (float)thisPtr[0x1a];
            local_18 = *(undefined8 *)(thisPtr + 0x18);
            local_20 = (float)local_18;
            local_10 = local_1c;
            iVar5 = FUN_00471610();
            local_c = *(undefined8 *)(iVar5 + 0x30);
            local_4 = *(float *)(iVar5 + 0x38);
            iVar5 = thisPtr[0x2c];
            param5 = ((float)local_c - (float)local_18) * ((float)local_c - (float)local_18);
            param3 = local_4 - local_10;
            cVar3 = FUN_005fd7a0(&local_20);
            if ((cVar3 != '\0') &&
               (fVar7 = *(float *)(iVar5 + 0x18) * DAT_00d5eee4,
               param3 * param3 + param5 < fVar7 * fVar7)) {
                FUN_004abdd0(0x2000);
                return 1;
            }
        }
        break;
    case 0x12: // state 32
        thisPtr[0x2a] = thisPtr[0x2a] & 0xfffffffe;
        return 1;
    case 0x13: // state 33
        if ((int *)thisPtr[0x43] != (int *)0x0) {
            (**(code **)(*(int *)thisPtr[0x43] + 0xc))(thisPtr[0x53]); // virtual call
            param2 = 2;
            FUN_005fd860(&param2, &param5, &param4);
            cVar3 = FUN_005f5cb0(&param5, &param2);
            if ((cVar3 != '\0') && (param2 != param4)) {
                FUN_005ff280();
                return 1;
            }
        }
        break;
    case 0x14: // state 34
        FUN_00758fa0();
        return 1;
    case 0x15: // state 35
        if ((*(uint *)(thisPtr[0x16] + 0x1b94) >> 0x1e & 1) == 0) {
            FUN_00758e40();
        }
        thisPtr[0x45] = thisPtr[0x53];
        return 1;
    case 0x16: // state 36
        bVar1 = (byte)((uint)*(undefined4 *)(thisPtr[0x16] + 0x1b94) >> 0x1e);
        bVar2 = bVar1 & 1;
        param3 = (float)(CONCAT31(param3._1_3_, bVar1) & 0xffffff01);
        if (((byte)((uint)thisPtr[0x2a] >> 0x16) & 1) != bVar2) {
            if (bVar2 == 0) {
                FUN_007577a0();
            } else {
                FUN_00757770();
            }
            FUN_00508f40(0x400000, param3);
            return 1;
        }
        break;
    case 0x17: // state 37
        break;
    }
    return uVar4;
}