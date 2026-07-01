// FUNC_NAME: MinimapManager::updateMinimap
void __thiscall MinimapManager::updateMinimap(int this, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, int *param_6)
{
    undefined4 uVar1;
    undefined4 *puVar2;
    float fVar3;
    char cVar4;
    int *piVar5;
    int iVar6;
    int *piVar7;
    uint uVar8;
    float *pfVar9;
    float *pfVar10;
    float10 fVar11;
    float fVar12;
    float fVar13;
    float fVar14;
    undefined4 local_29c;
    float local_290;
    float local_28c;
    float local_288;
    float local_284;
    float local_27c;
    float fStack_278;
    float local_274;
    int *local_270;
    undefined4 local_26c;
    int local_268;
    undefined1 local_264;
    float afStack_260 [16];
    float afStack_220 [18];
    float local_1d8;
    float local_1d4;
    float local_1d0;
    float local_1cc;
    float local_1c8;
    float local_1c4;
    float fStack_1c0;
    float fStack_1bc;
    float fStack_1b8;
    float fStack_1b4;
    undefined4 uStack_1ac;
    undefined4 uStack_1a8;
    undefined4 uStack_1a4;
    float fStack_1a0;
    float fStack_19c;
    float fStack_198;
    undefined4 uStack_194;
    undefined1 auStack_190 [32];
    float fStack_170;
    float fStack_16c;
    float fStack_168;
    float fStack_164;
    undefined1 auStack_150 [64];
    char acStack_110 [268];

    if (*param_6 == 0) {
        FUN_005c5080();
        local_27c = *(float *)(this + 0xf0); // +0xF0: some float field
        *param_6 = 1;
        uVar8 = 0;
        do {
            FUN_005c7680(param_2, *(undefined4 *)((int)&PTR_DAT_00e56800 + uVar8), (int)&DAT_00e568d0 + uVar8);
            uVar8 = uVar8 + 4;
        } while (uVar8 < 0x30);
        uVar8 = 0;
        do {
            FUN_005c7680(param_2, *(undefined4 *)((int)&PTR_DAT_00e56830 + uVar8), (int)&DAT_00e5689c + uVar8);
            uVar8 = uVar8 + 4;
        } while (uVar8 < 0x30);
        uVar8 = 0;
        do {
            FUN_005c7680(param_2, *(undefined4 *)((int)&PTR_DAT_00e56860 + uVar8), (int)&DAT_00e56904 + uVar8);
            uVar8 = uVar8 + 4;
        } while (uVar8 < 0x30);
        uVar8 = 0;
        do {
            FUN_005c7680(param_2, *(undefined4 *)((int)&PTR_s_SpeedMin__00e56890 + uVar8), (int)&DAT_01130600 + uVar8);
            uVar8 = uVar8 + 4;
        } while (uVar8 < 0xc);
        uVar1 = *(undefined4 *)((int)local_27c + 4);
        piVar5 = (int *)(DAT_01206880 + 0x14);
        **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_00e56a14;
        *piVar5 = *piVar5 + 4;
        *(int *)*piVar5 = this + -0x10;
        *piVar5 = *piVar5 + 4;
        *(undefined4 *)*piVar5 = local_29c;
        *piVar5 = *piVar5 + 4;
        *(undefined4 *)*piVar5 = uVar1;
        *piVar5 = *piVar5 + 4;
        local_26c = DAT_01130388;
        local_268 = 0;
        local_264 = 0;
        FUN_00408a00();
    }
    FUN_005c50c0(param_4, &local_1d8, &local_1d4, &local_1d0, &local_1c8);
    local_1c4 = local_1d8 * DAT_00d5eee4 - _DAT_00d5780c;
    local_274 = local_1d0 * DAT_00d5eee4 - _DAT_00d5780c;
    local_1cc = _DAT_00d5780c - local_1d4 * DAT_00d5eee4;
    fVar14 = _DAT_00d5780c - local_1c8 * DAT_00d5eee4;
    if (**(int **)(DAT_012233a0 + 4) == 0) {
        piVar5 = (int *)0x0;
    }
    else {
        piVar5 = (int *)(**(int **)(DAT_012233a0 + 4) + -0x1f30);
    }
    local_270 = piVar5;
    iVar6 = FUN_00471610();
    local_290 = *(float *)(iVar6 + 0x30); // +0x30: camera position X
    local_28c = *(float *)(iVar6 + 0x34); // +0x34: camera position Y
    local_288 = *(float *)(iVar6 + 0x38); // +0x38: camera position Z
    local_284 = _DAT_00d5780c;
    if (((int *)**(int **)(DAT_012233a0 + 4) != (int *)0x0) &&
       (piVar7 = (int *)(**(code **)(*(int *)**(int **)(DAT_012233a0 + 4) + 0xc))(),
       piVar7 != (int *)0x0)) {
        (**(code **)(*piVar7 + 0x10))();
    }
    local_27c = 2.8026e-45;
    FUN_00425060();
    FUN_0056b8a0(uStack_1a8, uStack_1ac, uStack_1a4, auStack_190);
    fVar12 = fStack_168 * fStack_168 + fStack_170 * fStack_170 + fStack_164 * fStack_164;
    if (fVar12 <= DAT_00d5f2b4) {
        fVar12 = 0.0;
    }
    else {
        fVar12 = _DAT_00d5780c / SQRT(fVar12);
    }
    fStack_170 = fVar12 * fStack_170;
    fStack_16c = fVar12 * 0.0;
    fStack_168 = fVar12 * fStack_168;
    fStack_164 = fStack_164 * fVar12;
    if ((_DAT_01130630 & 1) == 0) {
        _DAT_01130630 = _DAT_01130630 | 1;
        _DAT_01130620 = local_290;
        _DAT_01130624 = local_28c;
        _DAT_01130628 = local_288;
        DAT_0113062c = _DAT_00d5780c;
    }
    cVar4 = FUN_0040edb0();
    if (cVar4 == '\0') {
        fVar11 = (float10)(**(code **)(*piVar5 + 0x1c0))();
        fVar12 = DAT_01130604;
        if (fVar11 * (float10)DAT_00d5f374 < (float10)DAT_01130604) {
            fVar12 = (float)(fVar11 * (float10)DAT_00d5f374);
        }
        fVar12 = fVar12 * DAT_00d5ef90;
        *(float *)(this + 0xa0) = *(float *)(this + 0xa0) - *(float *)(this + 0x4c + *(int *)(this + 0x9c) * 4);
        *(float *)(this + 0x4c + *(int *)(this + 0x9c) * 4) = fVar12;
        iVar6 = *(int *)(this + 0x9c) + 1;
        *(float *)(this + 0xa0) = *(float *)(this + 0x4c + *(int *)(this + 0x9c) * 4) + *(float *)(this + 0xa0);
        *(int *)(this + 0x9c) = iVar6;
        if (0x13 < iVar6) {
            *(undefined4 *)(this + 0x9c) = 0;
        }
    }
    fVar3 = _DAT_00d5780c;
    fVar12 = *(float *)(this + 0xa0);
    fStack_278 = DAT_01130604 - DAT_01130600;
    if (0.0 < (fVar12 - DAT_01130600) / fStack_278) {
        if ((fVar12 - DAT_01130600) / fStack_278 < _DAT_00d5780c) {
            fStack_278 = (fVar12 - DAT_01130600) / fStack_278;
        }
        else {
            fStack_278 = _DAT_00d5780c;
        }
    }
    else {
        fStack_278 = 0.0;
    }
    if ((DAT_01130610 == 0) || (fVar12 = _DAT_00d5780c, (DAT_01130610 & 1) == 0)) {
        fVar12 = 0.0;
    }
    *(float *)(this + 0xf4) = fVar12;
    if ((*(float *)(this + 0xf8) < fVar12) &&
       (fVar13 = fVar3 / _DAT_01130608 + *(float *)(this + 0xf8),
       *(float *)(this + 0xf8) = fVar13, fVar12 < fVar13)) {
        *(float *)(this + 0xf8) = fVar12;
    }
    if ((fVar12 < *(float *)(this + 0xf8)) &&
       (fVar13 = *(float *)(this + 0xf8) - fVar3 / _DAT_01130608,
       *(float *)(this + 0xf8) = fVar13, fVar13 < fVar12)) {
        *(float *)(this + 0xf8) = fVar12;
    }
    local_29c = 1;
    if (*(float *)(this + 0xf8) <= _DAT_00d5c458) {
        local_29c = 2;
    }
    afStack_260[6] = DAT_00d8b2a0;
    afStack_220[6] = DAT_00d8b2a0;
    afStack_220[7] = DAT_00d8b29c;
    afStack_220[8] = (float)DAT_00d8b298;
    afStack_260[8] = (float)DAT_00d8b298;
    afStack_220[10] = (float)DAT_00d8b2a8;
    afStack_260[10] = (float)DAT_00d8b2a8;
    afStack_260[0] = DAT_00d8b2ac;
    afStack_260[1] = DAT_00d8b2ac;
    afStack_260[2] = (float)DAT_00d8b2a4;
    afStack_260[3] = DAT_00d5f378;
    afStack_260[4] = DAT_00e446f4;
    afStack_260[5] = 0.0;
    afStack_260[9] = fVar3;
    afStack_260[0xb] = (float)DAT_00d75ca0;
    afStack_220[0] = DAT_00d8b2ac;
    afStack_220[1] = DAT_00d8b2ac;
    afStack_220[2] = (float)DAT_00d8b2a4;
    afStack_220[3] = DAT_00d5f378;
    afStack_220[4] = DAT_00e446f4;
    afStack_220[5] = 0.0;
    afStack_220[9] = fVar3;
    afStack_220[0xb] = (float)DAT_00d75ca0;
    afStack_220[0xc] = fVar3;
    if (0.0 < fStack_278) {
        if (fStack_278 < fVar3) {
            uVar8 = 0;
            do {
                *(float *)((int)afStack_220 + uVar8) =
                     (*(float *)((int)&DAT_00e56904 + uVar8) - *(float *)((int)&DAT_00e5689c + uVar8)) *
                     fStack_278 + *(float *)((int)&DAT_00e5689c + uVar8);
                uVar8 = uVar8 + 4;
            } while (uVar8 < 0x34);
        }
        else {
            pfVar9 = (float *)&DAT_00e56904;
            pfVar10 = afStack_220;
            for (iVar6 = 0xd; iVar6 != 0; iVar6 = iVar6 + -1) {
                *pfVar10 = *pfVar9;
                pfVar9 = pfVar9 + 1;
                pfVar10 = pfVar10 + 1;
            }
        }
    }
    else {
        pfVar9 = (float *)&DAT_00e5689c;
        pfVar10 = afStack_220;
        for (iVar6 = 0xd; iVar6 != 0; iVar6 = iVar6 + -1) {
            *pfVar10 = *pfVar9;
            pfVar9 = pfVar9 + 1;
            pfVar10 = pfVar10 + 1;
        }
    }
    fVar12 = *(float *)(this + 0xf8);
    if (0.0 < fVar12) {
        if (fVar12 < fVar3) {
            uVar8 = 0;
            do {
                *(float *)((int)afStack_260 + uVar8) =
                     (*(float *)((int)&DAT_00e568d0 + uVar8) - *(float *)((int)afStack_220 + uVar8)) *
                     fVar12 + *(float *)((int)afStack_220 + uVar8);
                uVar8 = uVar8 + 4;
            } while (uVar8 < 0x34);
            if (DAT_00d5f378 <= fVar12) {
                afStack_260[0xc] = (fVar12 - DAT_00d5f378) * _DAT_00d8b2b4;
                afStack_260[7] = DAT_00e568ec * afStack_260[0xc];
            }
            else {
                afStack_260[7] = (DAT_00e44564 - afStack_220[7]) * fVar12 * _DAT_00d5ca64 + afStack_220[7];
                afStack_260[0xc] = fVar3 - fVar12 * _DAT_00d5ca64;
            }
        }
        else {
            pfVar9 = (float *)&DAT_00e568d0;
            pfVar10 = afStack_260;
            for (iVar6 = 0xd; iVar6 != 0; iVar6 = iVar6 + -1) {
                *pfVar10 = *pfVar9;
                pfVar9 = pfVar9 + 1;
                pfVar10 = pfVar10 + 1;
            }
        }
    }
    else {
        afStack_260[0] = afStack_220[0];
        afStack_260[1] = afStack_220[1];
        afStack_260[2] = afStack_220[2];
        afStack_260[3] = afStack_220[3];
        afStack_260[4] = afStack_220[4];
        afStack_260[5] = afStack_220[5];
        afStack_260[6] = afStack_220[6];
        afStack_260[7] = afStack_220[7];
        afStack_260[8] = afStack_220[8];
        afStack_260[9] = afStack_220[9];
        afStack_260[10] = afStack_220[10];
        afStack_260[0xb] = afStack_220[0xb];
        afStack_260[0xc] = afStack_220[0xc];
    }
    fStack_1a0 = local_290 - fStack_170 * afStack_260[4];
    fStack_19c = afStack_260[6] + local_28c;
    fStack_198 = local_288 - fStack_168 * afStack_260[4];
    uStack_194 = 0;
    local_290 = afStack_260[5] * fStack_170 + local_290;
    local_288 = afStack_260[5] * fStack_168 + local_288;
    FUN_006138b0(&fStack_1a0, &local_290, &DAT_00e56a30, auStack_150);
    iVar6 = FUN_00471610();
    _DAT_01130620 = *(float *)(iVar6 + 0x30);
    _DAT_01130624 = *(float *)(iVar6 + 0x34);
    _DAT_01130628 = *(float *)(iVar6 + 0x38);
    local_284 = _DAT_00d5780c;
    fStack_1c0 = local_1c4;
    fStack_1bc = local_1cc;
    fStack_1b8 = local_274;
    local_290 = _DAT_01130620;
    local_28c = _DAT_01130624;
    local_288 = _DAT_01130628;
    fStack_1b4 = fVar14;
    fVar11 = (float10)FUN_005c7630();
    fVar14 = (float)fVar11;
    FUN_005c4e30();
    puVar2 = *(undefined4 **)(this + 0xf0);
    iVar6 = puVar2[1];
    FUN_00422bc0();
    FUN_00422e80();
    FUN_00422fb0();
    local_274 = (float)(this + -0x10);
    piVar5 = (int *)(DAT_01206880 + 0x14);
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_FUN_00e569c4;
    *piVar5 = *piVar5 + 4;
    afStack_220[0] = afStack_260[0];
    afStack_220[1] = afStack_260[1];
    afStack_220[2] = afStack_260[2];
    afStack_220[3] = afStack_260[3];
    afStack_220[4] = afStack_260[4];
    afStack_220[5] = afStack_260[5];
    afStack_220[6] = afStack_260[6];
    afStack_220[7] = afStack_260[7];
    afStack_220[0xc] = afStack_260[0xc];
    afStack_220[8] = afStack_260[8];
    afStack_220[9] = afStack_260[9];
    afStack_220[10] = afStack_260[10];
    afStack_220[0xb] = afStack_260[0xb];
    *(float *)*piVar5 = local_274;
    *piVar5 = *piVar5 + 4;
    FUN_0049c430(&fStack_1c0, 0x10, 0x10);
    FUN_0049c430(&local_290, 0x10, 0x10);
    FUN_0049c430(auStack_150, 0x40, 0x10);
    pfVar9 = (float *)*piVar5;
    *pfVar9 = fVar14;
    pfVar9 = pfVar9 + 1;
    *piVar5 = (int)pfVar9;
    *pfVar9 = local_27c;
    *piVar5 = *piVar5 + 4;
    FUN_0049c430(afStack_220, 0x34, 4);
    if (iVar6 != 0) {
        iVar6 = FUN_00422930();
        FUN_00422900();
        (**(code **)(*(int *)*puVar2 + 0xc))();
        FUN_004e03d0();
        if (iVar6 != 0) {
            FUN_00422900();
        }
    }
    fVar3 = local_274;
    fVar12 = local_27c;
    local_268 = DAT_01130614[1];
    if (local_268 == 0) {
        local_26c = 0;
    }
    else {
        local_26c = *DAT_01130614;
    }
    piVar5 = (int *)DAT_01130614[3];
    if (piVar5 == (int *)0x0) {
        piVar5 = &DAT_01218a14;
    }
    do {
        if (*piVar5 == 2) {
            iVar6 = piVar5[1];
            goto LAB_009464e5;
        }
        piVar5 = (int *)piVar5[2];
    } while (piVar5 != (int *)0x0);
    iVar6 = 0x10;
LAB_009464e5:
    piVar5 = (int *)(DAT_01206880 + 0x14);
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_FUN_00e569d8;
    *piVar5 = *piVar5 + 4;
    FUN_00944350(local_274, &fStack_1c0, &local_290, auStack_150, fVar14, local_27c, local_29c,
                 CONCAT44(local_268, local_26c), iVar6);
    piVar5 = (int *)(DAT_01206880 + 0x14);
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_00e569ec;
    *piVar5 = *piVar5 + 4;
    *(float *)*piVar5 = fVar3;
    *piVar5 = *piVar5 + 4;
    FUN_0049c430(&fStack_1c0, 0x10, 0x10);
    pfVar9 = (float *)*piVar5;
    *pfVar9 = fVar14;
    *piVar5 = (int)(pfVar9 + 1);
    FUN_004e0420();
    FUN_005c4f80();
    if ((DAT_0112aa1c != 0) && (*(int *)(DAT_0112aa1c + 0x2c88) != 0)) {
        fVar11 = (float10)FUN_00784790();
        if (_DAT_00d577a0 <= (float)fVar11) {
            if ((*(byte *)((int)fVar3 + 0xfe) & 1) == 0) {
                FUN_00945690();
                *(ushort *)((int)fVar3 + 0xfe) = *(ushort *)((int)fVar3 + 0xfe) | 1;
            }
            else {
                FUN_00944d60(_DAT_00d5780c - (float)fVar11);
            }
            goto LAB_0094665d;
        }
    }
    if ((*(byte *)((int)fVar3 + 0xfe) & 1) != 0) {
        if ((*(byte *)((int)fVar3 + 0xfc) & 1) != 0) {
            __snprintf(acStack_110, 0x100, "mmap/minimap_timer.%s", "_visible");
            FUN_0059ee00(acStack_110, 0);
            *(ushort *)((int)fVar3 + 0xfc) = *(ushort *)((int)fVar3 + 0xfc) & 0xfffe;
        }
        *(ushort *)((int)fVar3 + 0xfe) = *(ushort *)((int)fVar3 + 0xfe) & 0xfffe;
    }
LAB_0094665d:
    FUN_009427a0(auStack_150, &local_290, afStack_260, (uint)fVar12 & 0xffffff01,
                 _DAT_00d5780c - fStack_278);
    return;
}