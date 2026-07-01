// FUNC_NAME: PlayerGroundSM::updateMovement
void __thiscall PlayerGroundSM::updateMovement(int this, float deltaTime)
{
    int iVar1;
    float fVar2;
    undefined4 uVar3;
    undefined4 uVar4;
    undefined4 uVar5;
    bool bVar6;
    char cVar7;
    float *pfVar8;
    int extraout_EDX;
    int extraout_EDX_00;
    int iVar9;
    float10 fVar10;
    float fVar11;
    float fVar12;
    float fVar13;
    float fVar14;
    float fVar15;
    float fVar16;
    float local_74;
    float local_70;
    float local_6c;
    int local_68;
    float local_64;
    float local_60;
    float fStack_5c;
    float fStack_58;
    float fStack_54;
    float local_50 [6];
    undefined4 uStack_38;
    undefined4 uStack_34;
    undefined4 local_30;
    undefined4 uStack_2c;
    float fStack_28;
    undefined4 uStack_24;
    undefined4 local_20;
    undefined4 uStack_1c;
    undefined4 uStack_18;
    float fStack_14;
    
    cVar7 = FUN_00977110(); // likely isPaused or similar
    iVar9 = DAT_012233b4; // global game state pointer
    if ((cVar7 != '\0') || (*(int *)(*(int *)(this + 0x6c) + 0x110) != 0)) goto LAB_009563b3;
    local_6c = (float)CONCAT31(local_6c._1_3_,*(undefined1 *)(DAT_012233b4 + 0x53d));
    local_68 = DAT_012233b4;
    pfVar8 = (float *)FUN_00410540(local_6c); // likely getInputAxis
    local_64 = *(float *)(iVar9 + 0x54c);
    if ((local_64 == _DAT_00d577a0) &&
       (((*(uint *)(iVar9 + 0x550) >> 1 & 1) == 0 && (cVar7 = FUN_00410eb0(), cVar7 != '\0')))) {
      bVar6 = false;
    }
    else {
      bVar6 = true;
    }
    if (pfVar8 == (float *)0x0) goto LAB_009563b3;
    local_6c = DAT_00d5c454; // dead zone threshold
    cVar7 = FUN_00410d80(); // isSprinting?
    iVar9 = DAT_01129938; // player state pointer
    fVar2 = DAT_00d5d70c; // max speed
    fVar12 = DAT_00d5ccf8; // speed multiplier
    fVar14 = 0.0;
    if (cVar7 != '\0') {
      local_6c = 0.0; // no dead zone when sprinting
    }
    local_74 = *pfVar8; // left stick X
    if ((float)((uint)local_74 & DAT_00e44680) <= local_6c) {
      local_74 = 0.0;
    }
    local_70 = pfVar8[1]; // left stick Y
    if ((float)((uint)local_70 & DAT_00e44680) <= local_6c) {
      local_70 = 0.0;
    }
    fVar11 = pfVar8[2]; // right stick X
    if ((float)((uint)fVar11 & DAT_00e44680) <= local_6c) {
      fVar11 = 0.0;
    }
    fVar13 = pfVar8[3]; // right stick Y
    if ((float)((uint)fVar13 & DAT_00e44680) <= local_6c) {
      fVar13 = 0.0;
    }
    fVar15 = local_74;
    fVar16 = local_70;
    local_6c = fVar13;
    if (bVar6) {
        iVar1 = *(int *)(this + 0x6c); // player entity
        fVar11 = *(float *)(iVar1 + 0xa0) * fVar11; // right stick X * some factor
        if ((*(uint *)(DAT_01129938 + 0x14) >> 5 & 1) == 0) {
            fVar11 = fVar11 * DAT_00d5ccf8; // speed multiplier
        }
        fVar11 = fVar11 + *(float *)(iVar1 + 0x94); // add to current yaw
        *(float *)(iVar1 + 0x94) = fVar11;
        if (fVar2 < fVar11) {
            *(float *)(iVar1 + 0x94) = fVar11 - fVar2; // wrap yaw
        }
        if (*(float *)(iVar1 + 0x94) < DAT_00e44780) {
            *(float *)(iVar1 + 0x94) = (float)((double)*(float *)(iVar1 + 0x94) + _DAT_00d8c068);
        }
        if (local_64 != 0.0) {
            fVar13 = DAT_00e44564 - local_64;
        }
        local_6c = fVar13;
        if (fVar13 <= 0.0) {
            if (fVar13 < 0.0) {
                FUN_00955b40(fVar13 * fVar12); // apply negative rotation
                iVar9 = extraout_EDX_00;
            }
        }
        else {
            FUN_00955bf0(fVar13); // apply positive rotation
            iVar9 = extraout_EDX;
        }
    }
    if ((*(uint *)(iVar9 + 0x14) >> 4 & 1) == 0) {
        fVar15 = fVar15 * fVar12;
        fVar16 = fVar16 * fVar12;
        local_74 = fVar15;
        local_70 = fVar16;
    }
    if ((DAT_0110acca & !bVar6 & *(byte *)(DAT_0112af70 + 0x1c1)) == 0) {
LAB_00956286:
        if ((fVar15 != fVar14) || (fVar16 != fVar14)) {
LAB_00956298:
            cVar7 = FUN_00410e40(0,DAT_00e2ed14);
            if ((cVar7 == '\0') || (*(char *)(DAT_01129a74 + 0x3c4) != '\0')) {
                bVar6 = false;
            }
            else {
                bVar6 = true;
            }
            *(bool *)(DAT_0112af70 + 0x1c0) = !bVar6;
            fVar15 = local_74;
        }
    }
    else {
        if (fVar15 != fVar14) goto LAB_00956298;
        if (fVar16 != fVar14) goto LAB_00956286;
        FUN_00955d30(&local_64,&local_6c); // likely getCameraRelativeInput
        fVar12 = local_64 + local_74;
        local_74 = DAT_00d5ccf8;
        if ((DAT_00d5ccf8 < fVar12) && (local_74 = fVar12, _DAT_00d5780c <= fVar12)) {
            local_74 = _DAT_00d5780c;
        }
        local_70 = local_6c + local_70;
        if (DAT_00d5ccf8 < local_70) {
            if (_DAT_00d5780c <= local_70) {
                local_70 = _DAT_00d5780c;
            }
        }
        else {
            local_70 = DAT_00d5ccf8;
        }
        fVar15 = local_74;
        if (*(char *)(DAT_01129a74 + 0x3c4) != '\0') {
            *(undefined1 *)(DAT_0112af70 + 0x1c0) = 1;
        }
    }
    FUN_00955860(*(float *)(*(int *)(this + 0x6c) + 0xbc) * fVar15 * deltaTime * _DAT_00d5f560); // apply forward movement
    FUN_00955910(*(float *)(*(int *)(this + 0x6c) + 0xbc) * local_70 * deltaTime * _DAT_00d5f560); // apply strafe movement
    iVar9 = *(int *)(this + 0x6c);
    if (*(float *)(iVar9 + 0xbc) <= _DAT_00d5780c && _DAT_00d5780c != *(float *)(iVar9 + 0xbc)) {
        *(float *)(iVar9 + 0xbc) = *(float *)(iVar9 + 0xc4) * deltaTime * _DAT_00d5f560 + *(float *)(iVar9 + 0xbc); // accelerate
    }
    if ((local_74 == 0.0) && (local_70 == 0.0)) {
        *(undefined4 *)(*(int *)(this + 0x6c) + 0xbc) = *(undefined4 *)(*(int *)(this + 0x6c) + 0xc0); // reset speed
    }
    cVar7 = FUN_00410eb0(); // isInCover?
    if (cVar7 != '\0') {
        *(float *)(*(int *)(this + 0x6c) + 0xbc) = _DAT_00d5780c; // set speed to max
    }
LAB_009563b3:
    if (*(int *)(*(int *)(this + 0x6c) + 0x110) != 0) {
        FUN_00954e10(); // handle ragdoll
    }
    iVar9 = *(int *)(this + 0x6c);
    fStack_54 = 0.0;
    fStack_58 = 0.0;
    local_60 = 0.0;
    fStack_5c = *(float *)(iVar9 + 0xb4); // vertical offset
    local_50[0] = _DAT_00d5780c; // identity matrix?
    local_50[1] = 0.0;
    local_50[2] = 0.0;
    local_50[3] = 0.0;
    local_50[4] = 0.0;
    local_50[5] = _DAT_00d5780c;
    uStack_38 = 0;
    uStack_34 = 0;
    local_30 = 0;
    uStack_2c = 0;
    fStack_28 = _DAT_00d5780c;
    uStack_24 = 0;
    local_20 = 0;
    uStack_1c = 0;
    uStack_18 = 0;
    fStack_14 = _DAT_00d5780c;
    FUN_0056b8a0(*(undefined4 *)(iVar9 + 0x94),*(float *)(iVar9 + 0x90) - DAT_00d5f00c,
                 *(undefined4 *)(iVar9 + 0x98),local_50); // build rotation matrix
    FUN_0056b420(local_50,&local_60,&local_60); // extract forward vector
    iVar9 = *(int *)(this + 0x6c);
    fVar12 = *(float *)(iVar9 + 0xd4);
    fVar2 = *(float *)(iVar9 + 0xd8);
    fVar14 = *(float *)(iVar9 + 0xdc);
    *(float *)(this + 0x20) = *(float *)(iVar9 + 0xd0) + local_60; // update position X
    *(float *)(this + 0x24) = fVar12 + fStack_5c; // update position Y
    *(float *)(this + 0x28) = fVar2 + fStack_58; // update position Z
    *(float *)(this + 0x2c) = fVar14 + fStack_54; // update position W?
    uVar3 = *(undefined4 *)(iVar9 + 0x94);
    uVar4 = *(undefined4 *)(iVar9 + 0x98);
    uVar5 = *(undefined4 *)(iVar9 + 0x9c);
    *(undefined4 *)(this + 0x40) = *(undefined4 *)(iVar9 + 0x90);
    *(undefined4 *)(this + 0x44) = uVar3;
    *(undefined4 *)(this + 0x48) = uVar4;
    *(undefined4 *)(this + 0x4c) = uVar5;
    FUN_00977550(); // update animation
    fVar10 = (float10)FUN_00425240(*(undefined4 *)(this + 0x50),1,2); // get animation blend weight
    FUN_00977860(this + 0x20,(undefined4 *)(this + 0x40),(float)fVar10); // blend animation
    FUN_009559c0(this + 0x20); // finalize movement
    return;
}