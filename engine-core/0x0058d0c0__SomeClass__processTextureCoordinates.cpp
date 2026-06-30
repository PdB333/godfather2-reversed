// FUNC_NAME: SomeClass::processTextureCoordinates
void __thiscall SomeClass::processTextureCoordinates(int *this, undefined4 param_2, int param_3, int *param_4, float param_5, float param_6, uint param_7, undefined4 param_8)
{
    short sVar1;
    short sVar2;
    int iVar3;
    uint uVar4;
    int iVar5;
    bool bVar6;
    int *piVar7;
    float fVar8;
    int *piVar9;
    float fVar10;
    float fVar11;
    float fVar12;
    int *local_4;

    piVar7 = param_4;
    piVar9 = (int *)0x0;
    iVar3 = *(int *)(param_3 + 4); // +0x04: some pointer
    fVar11 = param_5;
    fVar12 = param_6;
    local_4 = this;
    if (((param_7 >> 1 ^ param_7) & 1) == 0) {
        if ((0.0 <= param_6) || (param_5 < 0.0)) {
            bVar6 = false;
        }
        else {
            bVar6 = true;
        }
        if ((param_6 <= param_5) && (!bVar6)) goto LAB_0058d332;
    }
    else if (param_5 <= param_6) goto LAB_0058d332;
    uVar4 = *(uint *)(iVar3 + 4); // +0x04: index
    if ((uint)param_4[1] <= uVar4) {
        param_4 = (int *)0x0;
        FUN_00591c00(&param_4);
    }
    param_4 = *(int **)(*piVar7 + uVar4 * 4);
    uVar4 = *(uint *)(iVar3 + 4);
    fVar8 = *(float *)(iVar3 + 0xc); // +0x0c: some float
    if (fVar8 < *(float *)(iVar3 + 8) || fVar8 == *(float *)(iVar3 + 8)) { // +0x08: some float
        if ((uint)piVar7[1] <= uVar4) {
            local_4 = (int *)0x0;
            FUN_00591c00(&local_4);
        }
        piVar9 = (int *)0x0;
        *(undefined4 *)(*piVar7 + uVar4 * 4) = *(undefined4 *)(iVar3 + 8);
        fVar11 = param_5;
        fVar12 = param_6;
    }
    else {
        if ((uint)piVar7[1] <= uVar4) {
            local_4 = (int *)0x0;
            FUN_00591c00(&local_4);
        }
        piVar9 = (int *)0x0;
        iVar5 = *piVar7;
        fVar10 = *(float *)(iVar3 + 8);
        fVar11 = param_5;
        fVar12 = param_6;
        FUN_00593700();
        *(float *)(iVar5 + uVar4 * 4) =
             fVar8 * ((*(float *)(iVar3 + 0xc) - fVar10) + DAT_00e2b1a4) + fVar10;
    }
    uVar4 = *(uint *)(iVar3 + 4);
    if ((uint)piVar7[1] <= uVar4) {
        local_4 = piVar9;
        FUN_00591c00(&local_4);
        piVar9 = (int *)0x0;
        fVar11 = param_5;
        fVar12 = param_6;
    }
    if (*(float *)(*piVar7 + uVar4 * 4) != (float)param_4) {
        sVar1 = *(short *)(param_3 + 2); // +0x02: some short
        if ((uint)piVar7[1] <= (uint)(int)sVar1) {
            local_4 = piVar9;
            FUN_00591c00(&local_4);
            piVar9 = (int *)0x0;
            fVar11 = param_5;
            fVar12 = param_6;
        }
        sVar2 = *(short *)(param_3 + 2);
        local_4 = (int *)(*(float *)(*piVar7 + sVar1 * 4) / ((float)param_4 + DAT_00e2b1a4));
        if ((uint)piVar7[1] <= (uint)(int)sVar2) {
            param_4 = piVar9;
            FUN_00591c00(&param_4);
            piVar9 = (int *)0x0;
            fVar11 = param_5;
            fVar12 = param_6;
        }
        sVar1 = *(short *)(param_3 + 2);
        local_4 = (int *)((*(float *)(*piVar7 + sVar2 * 4) + DAT_00e2b1a4) * (float)local_4);
        if ((uint)piVar7[1] <= (uint)(int)sVar1) {
            param_4 = piVar9;
            FUN_00591c00(&param_4);
            piVar9 = (int *)0x0;
            fVar11 = param_5;
            fVar12 = param_6;
        }
        *(int **)(*piVar7 + sVar1 * 4) = local_4;
    }
LAB_0058d332:
    sVar1 = *(short *)(param_3 + 2);
    if ((uint)piVar7[1] <= (uint)(int)sVar1) {
        param_4 = piVar9;
        FUN_00591c00(&param_4);
        piVar9 = (int *)0x0;
        fVar11 = param_5;
        fVar12 = param_6;
    }
    iVar3 = *piVar7;
    sVar2 = *(short *)(param_3 + 2);
    if ((uint)piVar7[1] <= (uint)(int)sVar2) {
        param_4 = piVar9;
        FUN_00591c00(&param_4);
        fVar11 = param_5;
        fVar12 = param_6;
    }
    fVar8 = *(float *)(iVar3 + sVar1 * 4) / (*(float *)(*piVar7 + sVar2 * 4) + DAT_00e2b1a4);
    if (fVar8 == DAT_00e2b1a4) {
        fVar11 = fVar11 - (float)(int)fVar11;
    }
    else {
        fVar10 = fVar8 - DAT_00e2b1a4;
        if (fVar10 < fVar11) {
            fVar11 = fVar11 - (float)(int)(fVar11 / fVar10) * fVar10;
        }
    }
    if (fVar8 == DAT_00e2b1a4) {
        fVar12 = fVar12 - (float)(int)fVar12;
    }
    else {
        fVar8 = fVar8 - DAT_00e2b1a4;
        if (fVar8 < fVar12) {
            fVar12 = fVar12 - (float)(int)(fVar12 / fVar8) * fVar8;
        }
    }
    param_5 = fVar11;
    param_6 = fVar12;
    FUN_0058afb0(param_2, param_3, piVar7, fVar11, fVar12, param_7, param_8);
    return;
}