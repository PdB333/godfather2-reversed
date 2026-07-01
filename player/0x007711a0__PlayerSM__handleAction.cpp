// FUNC_NAME: PlayerSM::handleAction
uint __thiscall PlayerSM::handleAction(int *this, int param_2, undefined4 param_3, undefined4 param_4, int actionId, undefined4 param_6)
{
    code *pcVar1;
    float fVar2;
    char cVar3;
    uint uVar4;
    undefined4 uVar5;
    int iVar6;
    uint unaff_EDI;
    float10 extraout_ST0;
    float10 extraout_ST0_00;
    float10 fVar7;
    float10 extraout_ST0_01;
    float10 extraout_ST0_02;
    undefined4 unaff_retaddr;
    byte bVar8;
    undefined4 uVar9;
    byte local_11;
    undefined4 uStack_4;
    
    local_11 = 1;
    switch(actionId + -10) {
    case 0: // actionId == 10
        uVar4 = FUN_006252f0();
        *(uint *)(this[0x14] + 0x1b94) = *(uint *)(this[0x14] + 0x1b94) & ~uVar4;
        return 1;
    case 1: // actionId == 11
        FUN_0076f870();
        return 1;
    case 2: // actionId == 12
        FUN_0076ffd0();
        return 1;
    case 3: // actionId == 13
        FUN_00770240(param_2, param_3);
        return 1;
    case 4: // actionId == 14
        (**(code **)(*(int *)this[0x14] + 0x234))(1, 1);
        FUN_00770240(uStack_4, unaff_retaddr);
        return unaff_EDI >> 0x18;
    case 5: // actionId == 15
        bVar8 = 0;
        (**(code **)(*this + 0x2c))(0xbf5e4f87, 1, 1, 0, 0x3f800000, 0x3f800000);
        return (uint)bVar8;
    case 6: // actionId == 16
        FUN_007704f0();
        return 1;
    case 7: // actionId == 17
        FUN_0076e8f0();
        *(byte *)(this + 0x15) = *(byte *)(this + 0x15) & 0xfe;
        uVar5 = (**(code **)(*(int *)this[0x29] + 0x34))();
        FUN_0084d5f0(uVar5);
        return 1;
    case 8: // actionId == 18
        FUN_007f6420(0x10);
        return 1;
    case 9: // actionId == 19
        FUN_007f6420(0x23);
        FUN_007f6420(0x24);
        return 1;
    case 10: // actionId == 20
        if (((*(byte *)(this + 0x15) & 2) == 0) && (*(char *)(this[0x14] + 0x1b8c) == '\x01')) {
            uVar9 = 0;
            uVar5 = FUN_006fbc40(0, 0);
            FUN_007f96a0(0, 0, uVar5, uVar9);
            FUN_006fbc70();
            *(byte *)(this + 0x15) = *(byte *)(this + 0x15) | 2;
            return 1;
        }
        break;
    case 0xb: // actionId == 21
        FUN_00770980(0);
        return 1;
    case 0xc: // actionId == 22
        if ((*(byte *)(this + 0x15) & 4) == 0) {
            *(uint *)(this[0x14] + 0x1b94) = *(uint *)(this[0x14] + 0x1b94) | 0x40;
            return 1;
        }
        break;
    case 0xd: // actionId == 23
        cVar3 = FUN_0076ec60();
        bVar8 = 0;
        if ((*(uint *)(this[0x14] + 0x1f58) >> 10 & 1) == 0) {
            pcVar1 = *(code **)(*this + 0x2c);
            if (cVar3 == '\0') {
                (*pcVar1)(0x8460e652, 1, 1, 0, 0x3f800000, 0x3f800000);
                return (uint)bVar8;
            }
            (*pcVar1)(0x82cdc9c, 1, 1, 0, 0x3f800000, 0x3f800000);
            return (uint)bVar8;
        }
        pcVar1 = *(code **)(*this + 0x2c);
        if (cVar3 == '\0') {
            (*pcVar1)(0xcdb88ef5);
            return (uint)bVar8;
        }
        (*pcVar1)(0xf918662b);
        return (uint)bVar8;
    case 0xe: // actionId == 24
        (**(code **)(*(int *)this[0x14] + 0xc0))();
        fVar7 = extraout_ST0;
        goto LAB_0077143a;
    case 0xf: // actionId == 25
        if (((uint)((int *)this[0x14])[0x6e5] >> 4 & 1) == 0) break;
        (**(code **)(*(int *)this[0x14] + 0xc0))();
        fVar7 = extraout_ST0_00;
LAB_0077143a:
        if (((float10)0 < fVar7) && (cVar3 = FUN_004abe10(1), cVar3 != '\0')) {
            FUN_0076ed30();
            return 1;
        }
        break;
    case 0x10: // actionId == 26
        if ((*(byte *)(this + 0x15) & 8) == 0) {
            FUN_007f4490(1, 0, DAT_00d5ef90);
            *(byte *)(this + 0x15) = *(byte *)(this + 0x15) | 8;
            return 1;
        }
        break;
    case 0x11: // actionId == 27
        if ((*(byte *)(this + 0x15) & 8) != 0) {
            FUN_007f4490(0, 0, DAT_00d5ef90);
            *(byte *)(this + 0x15) = *(byte *)(this + 0x15) & 0xf7;
            return 1;
        }
        break;
    case 0x12: // actionId == 28
        if ((((this[0x19] != 0) && (this[0x19] != 0x48)) && (this[0x19] != 0)) &&
           (iVar6 = this[0x19] + -0x48, iVar6 != 0)) {
            FUN_007537f0(iVar6, this[0xc], 3);
            FUN_0046fd90(iVar6, 0);
            return 1;
        }
        break;
    case 0x13: // actionId == 29
        iVar6 = FUN_00800a90();
        if (((iVar6 != 0) && (cVar3 = FUN_00701010(), cVar3 != '\0')) &&
           (FUN_00427180(), extraout_ST0_01 < (float10)DAT_00d5ef88)) {
            *(byte *)(this + 0x15) = *(byte *)(this + 0x15) | 0x10;
            FUN_00701290(4);
            return 1;
        }
        break;
    case 0x14: // actionId == 30
        if ((((*(byte *)(this + 0x15) & 0x10) != 0) &&
            ((*(uint *)(this[0x14] + 0x1b94) >> 0x1a & 1) != 0)) &&
           (iVar6 = FUN_00800a90(), iVar6 != 0)) {
            fVar2 = (float)param_2;
            if (param_2 < 0) {
                fVar2 = fVar2 + DAT_00e44578;
            }
            fVar2 = fVar2 * DAT_00d5efb8;
            FUN_00701020();
            if ((extraout_ST0_02 * (float10)_DAT_00d5ca1c + (float10)(float)this[0x28] < (float10)fVar2
                ) && (cVar3 = FUN_00701280(), cVar3 != '\0')) {
                this[0x28] = (int)fVar2;
                *(uint *)(this[0x14] + 0x1f58) = *(uint *)(this[0x14] + 0x1f58) & 0xffbfffff;
                FUN_00806de0();
                return 1;
            }
        }
        break;
    case 0x15: // actionId == 31
        iVar6 = FUN_0072dc00(this[0x14]);
        if ((iVar6 != 0) && ((*(uint *)(iVar6 + 0x4c) >> 1 & 1) != 0)) {
            FUN_00733740();
            return 1;
        }
        break;
    case 0x16: // actionId == 32
        FUN_007ffa80();
        return 1;
    case 0x17: // actionId == 33
        FUN_0076eb80();
        return 1;
    case 0x18: // actionId == 34
        FUN_00770980(1);
        return 1;
    default:
        local_11 = FUN_004ac700(param_2, param_3, param_4, actionId, param_6);
    }
    return (uint)local_11;
}