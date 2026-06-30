// FUNC_NAME: EARS::Transform::applyWeightedBoneTransform
void EARS::Transform::applyWeightedBoneTransform(float *param_1, undefined4 param_2, float *param_3, float *param_4, byte param_5)
{
    float fVar1;
    float fVar2;
    undefined4 uVar3;
    undefined4 uVar4;
    undefined4 uVar5;
    int in_EAX;
    float *pfVar6;
    int extraout_ECX;
    undefined4 *extraout_ECX_00;
    int iVar7;
    int extraout_EDX;
    int unaff_EDI;
    float fVar8;
    double dVar9;
    float fVar10;
    float fVar11;
    float fVar12;
    float fVar13;
    float local_b0;
    float fStack_ac;
    float fStack_a8;
    undefined4 uStack_a4;
    float local_a0;
    float fStack_9c;
    float fStack_98;
    float fStack_94;
    float local_90;
    float fStack_8c;
    float fStack_88;
    float fStack_84;
    float local_80;
    float fStack_7c;
    float fStack_78;
    float fStack_74;
    float local_70;
    float fStack_6c;
    float fStack_68;
    float fStack_64;
    float local_60;
    float fStack_5c;
    float fStack_58;
    float fStack_54;
    float local_50;
    float fStack_4c;
    float fStack_48;
    float fStack_44;
    float local_40;
    float fStack_3c;
    float fStack_38;
    float fStack_34;
    float local_30;
    float fStack_2c;
    float fStack_28;
    float fStack_24;
    float local_20;
    float fStack_1c;
    float fStack_18;
    float fStack_14;

    if (*param_4 == DAT_00e2b1a4) {
        if ((param_5 & 0xc) == 0xc) {
            FUN_0056cef0(param_3);
            uVar3 = *(undefined4 *)(extraout_ECX + 0x14);
            uVar4 = *(undefined4 *)(extraout_ECX + 0x18);
            uVar5 = *(undefined4 *)(extraout_ECX + 0x1c);
            *(undefined4 *)(unaff_EDI + 0x30) = *(undefined4 *)(extraout_ECX + 0x10);
            *(undefined4 *)(unaff_EDI + 0x34) = uVar3;
            *(undefined4 *)(unaff_EDI + 0x38) = uVar4;
            *(undefined4 *)(unaff_EDI + 0x3c) = uVar5;
            *(float *)(unaff_EDI + 0x3c) = DAT_00e2b1a4;
        }
        else {
            FUN_0056cef0(param_2);
            uVar3 = *(undefined4 *)(extraout_EDX + 0x14);
            uVar4 = *(undefined4 *)(extraout_EDX + 0x18);
            uVar5 = *(undefined4 *)(extraout_EDX + 0x1c);
            *(undefined4 *)(unaff_EDI + 0x30) = *(undefined4 *)(extraout_EDX + 0x10);
            *(undefined4 *)(unaff_EDI + 0x34) = uVar3;
            *(undefined4 *)(unaff_EDI + 0x38) = uVar4;
            *(undefined4 *)(unaff_EDI + 0x3c) = uVar5;
            *(float *)(unaff_EDI + 0x3c) = DAT_00e2b1a4;
            if ((param_5 & 4) == 0) {
                if ((param_5 & 8) != 0) {
                    FUN_00414aa0();
                }
            }
            else {
                FUN_0056cef0(param_3);
                extraout_ECX_00[2] = 0;
                extraout_ECX_00[1] = 0;
                *extraout_ECX_00 = 0;
                extraout_ECX_00[3] = DAT_00e2b1a4;
            }
        }
        pfVar6 = (float *)(unaff_EDI + 8);
        iVar7 = 3;
        do {
            pfVar6[-2] = pfVar6[-2] * *(float *)(in_EAX + 0x104);
            pfVar6[-1] = *(float *)(in_EAX + 0x104) * pfVar6[-1];
            *pfVar6 = *pfVar6 * *(float *)(in_EAX + 0x104);
            pfVar6 = pfVar6 + 4;
            iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
        return;
    }
    fStack_58 = *(float *)(in_EAX + 0x108);
    local_90 = fStack_58 * *param_1;
    fStack_8c = fStack_58 * param_1[1];
    fStack_88 = fStack_58 * param_1[2];
    fStack_84 = fStack_58 * param_1[3];
    local_80 = param_1[4] * fStack_58;
    fStack_7c = param_1[5] * fStack_58;
    fStack_78 = param_1[6] * fStack_58;
    fStack_74 = param_1[7] * fStack_58;
    local_70 = param_1[8] * fStack_58;
    fStack_6c = param_1[9] * fStack_58;
    fStack_68 = param_1[10] * fStack_58;
    fStack_64 = param_1[0xb] * fStack_58;
    local_60 = param_1[0xc] * fStack_58;
    fStack_5c = param_1[0xd] * fStack_58;
    fStack_58 = param_1[0xe] * fStack_58;
    fStack_54 = DAT_00e2b1a4;
    fVar13 = DAT_00e2b1a4;
    FUN_0056c640(&local_90, &local_50);
    fVar10 = param_3[1];
    fVar11 = param_3[2];
    fVar12 = *param_3;
    fVar8 = fVar11 * fVar11 + fVar10 * fVar10 + fVar12 * fVar12;
    uStack_a4 = 0;
    if (fVar8 <= DAT_00e2cbe0) {
        fVar8 = 0.0;
    }
    else {
        fVar8 = fVar13 / SQRT(fVar8);
    }
    fVar10 = fVar10 * fVar8;
    fVar12 = fVar8 * fVar12;
    fVar11 = fVar11 * fVar8;
    local_b0 = fVar10 * local_40 + fVar12 * local_50 + fVar11 * local_30;
    fStack_ac = fVar10 * fStack_3c + fVar12 * fStack_4c + fVar11 * fStack_2c;
    fStack_a8 = fVar10 * fStack_38 + fVar12 * fStack_48 + fVar11 * fStack_28;
    fStack_94 = fVar10 * fStack_34 + fVar12 * fStack_44 + fVar11 * fStack_24;
    if ((_DAT_01226f50 & 1) == 0) {
        _DAT_01226f50 = _DAT_01226f50 | 1;
        _DAT_01226f38 = 0;
        _DAT_01226f34 = 0;
        _DAT_01226f30 = 0;
        _DAT_01226f48 = 0.0;
        _DAT_01226f44 = 0.0;
        _DAT_01226f40 = 0.0;
        _DAT_01226f3c = fVar13;
        DAT_01226f4c = fVar13;
    }
    if ((param_5 & 8) != 0) {
        fVar13 = param_3[4];
        fVar8 = param_3[5];
        fVar1 = param_3[6];
        fVar2 = param_3[7];
        DAT_01226f4c = fVar8 * fStack_34 + fVar13 * fStack_44 + fVar1 * fStack_24 + fVar2 * fStack_14;
        _DAT_01226f48 = *(float *)(in_EAX + 0x108);
        _DAT_01226f40 =
             _DAT_01226f48 *
             (fVar8 * local_40 + fVar13 * local_50 + fVar1 * local_30 + fVar2 * local_20);
        _DAT_01226f44 =
             _DAT_01226f48 *
             (fVar8 * fStack_3c + fVar13 * fStack_4c + fVar1 * fStack_2c + fVar2 * fStack_1c);
        _DAT_01226f48 =
             _DAT_01226f48 *
             (fVar8 * fStack_38 + fVar13 * fStack_48 + fVar1 * fStack_28 + fVar2 * fStack_18);
    }
    local_a0 = local_b0;
    fStack_9c = fStack_ac;
    fStack_98 = fStack_a8;
    if ((param_5 & 4) != 0) {
        uStack_a4 = 0;
        dVar9 = (double)param_3[3];
        FUN_00b9b988();
        fVar10 = (float)dVar9 * DAT_00e2b04c;
        local_b0 = fVar10 * local_b0;
        fStack_ac = fVar10 * fStack_ac;
        fStack_a8 = fVar10 * fStack_a8;
        uStack_a4 = 0;
        FUN_0056d1f0(&local_b0, &DAT_01226f30);
        fVar12 = local_b0;
        fVar10 = fStack_ac;
        fVar11 = fStack_a8;
    }
    fStack_a8 = fVar11;
    fStack_ac = fVar10;
    local_b0 = fVar12;
    FUN_00574760();
    return;
}