// FUNC_NAME: BaseVehicle::updateSpringDynamics

void __thiscall BaseVehicle::updateSpringDynamics(int this, float deltaTime)
{
    int *pStatePtr;
    float *pf;
    double dVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    float fVar8;
    float fVar9;
    float fVar10;
    float fVar11;
    float fVar12;
    float fVar13;
    float fVar14;
    float fVar15;
    float fVar16;
    float fVar17;
    float fVar18;
    float fVar19;
    float fVar20;
    float fVar21;
    float fVar22;
    float fVar23;
    float fVar24;
    float fVar25;
    float fVar26;
    float fVar27;
    float fVar28;
    float fVar29;
    int iVar1;
    char cVar2;
    byte bVar3;
    uint uVar4;
    int *piVar5;
    float10 fVar10_10;
    float10 fVar10_11;
    // Undefined locals
    float local_54;
    float local_50;
    float fStack_5c;
    float fStack_58;
    float fStack_4c;
    float fStack_48;
    float fStack_44;
    float fStack_40;
    undefined8 uStack_3c;
    float fStack_34;
    undefined4 uStack_30;
    undefined4 uStack_2c;
    undefined4 uStack_28;
    float fStack_24;
    float fStack_20;
    float fStack_1c;
    char uStack_5d;
    int *statePtr;

    // Get state pointer from this+0xc0
    iVar1 = *(int *)(this + 0xc0);
    statePtr = (int *)(this + 0xc0);
    if (iVar1 == 0) {
        local_54 = 0.0;
        statePtr = (int *)0x0;
    } else {
        local_54 = (float)(iVar1 + -0x48);
        statePtr = (int *)(iVar1 + -0x48);
    }
    local_50 = 0.0;
    // Call a function via vtable (index 4) to check something
    cVar2 = (*(code **)(*statePtr + 0x10))(0x55859efa, &local_50);
    uVar4 = -(uint)(cVar2 != '\0') & *(uint *)&fStack_58; // fStack_58 is from local_50? Actually local_50 is a float, but used as uint? Might be reinterpretation.
    *(uint *)(this + 0x2d0) = uVar4;

    if (((*(int *)(this + 200) != 0) && (*(int *)(this + 200) != 0x48)) &&
       ((uVar4 == 0 || (cVar2 = FUN_007fd720(), cVar2 == '\0')))) {
        // Update spring dynamics
        FUN_006c85e0(deltaTime);
        local_54 = *(float *)(this + 0x2b4);
        fVar10_10 = (float10)FUN_006dd660(fStack_5c); // fStack_5c is likely deltaTime
        fVar2 = _DAT_00d5780c; // some constant like 1.0 ?
        local_50 = (float)fVar10_10;
        fStack_58 = (local_50 - local_54) * _DAT_00e51204 + local_54; // interpolate towards target
        *(float *)(this + 0x2b4) = fStack_58;
        if (0.0 < fStack_58) {
            if (fVar2 <= fStack_58) {
                fStack_58 = fVar2;
            }
        } else {
            fStack_58 = 0.0;
        }
        *(float *)(this + 0x2b4) = fStack_58;
        FUN_006dd900(this + 0x26c, statePtr, fStack_58);
        FUN_006dd760(deltaTime);
        FUN_006dc670(&fStack_24, this + 0x26c, fStack_5c);
        pf = (float *)(this + 0x278);
        FUN_006dc730(pf, this + 0x26c, this + 0x23c, statePtr, *(undefined4 *)(this + 0x2b4));
        uVar3 = *(undefined8 *)(this + 0x23c);
        fStack_34 = *(float *)(this + 0x244);
        uStack_3c._4_4_ = (float)((ulonglong)uVar3 >> 0x20);
        fStack_44 = *(float *)(this + 0x27c) - uStack_3c._4_4_;
        uStack_3c._0_4_ = (float)uVar3;
        fStack_48 = *pf - (float)uStack_3c;
        fStack_40 = *(float *)(this + 0x280) - fStack_34;
        dVar1 = (double)fStack_48;
        uStack_3c = uVar3;
        FUN_00b9a9fa();
        local_54 = (float)dVar1;
        dVar1 = (double)fStack_44;
        FUN_00b9a9fa();
        fStack_58 = DAT_00e44564 - (float)dVar1; // DAT_00e44564 is 3.1415927? PI/2?
        fVar12 = *(float *)(this + 0xdc) * DAT_00e445c8; // DAT_00e445c8 is RAD_TO_DEG? no, likely a speed scale
        fVar14 = DAT_00e44564 - fVar12;
        if ((fStack_58 <= fVar14) || (fVar14 = fVar12, fVar12 <= fStack_58)) {
            fStack_58 = fVar14;
        }
        fVar14 = *(float *)(this + 0xd8);
        if ((*(byte *)(*(int *)(this + 0x2d0) + 0x8e3) & 1) != 0) {
            fVar14 = *(float *)(this + 0x218);
        }
        local_50 = fVar14 * DAT_00e445c8 + fStack_58;
        dVar1 = (double)local_54;
        FUN_00b99fcb(); // cos?
        fStack_48 = (float)dVar1;
        dVar1 = (double)local_54;
        FUN_00b99e20(); // sin?
        fStack_48 = DAT_00e44564 - fStack_48;
        fStack_40 = DAT_00e44564 - (float)dVar1;
        fStack_44 = 0.0;
        fVar10_10 = (float10)FUN_006c93c0(fStack_5c);
        local_54 = (float)CONCAT31(local_54._1_3_, 1);
        if (fVar10_10 <= (float10)0) {
            local_54 = (float)((uint)local_54._1_3_ << 8);
        }
        FUN_006ca4b0(fStack_5c, local_54, 0, deltaTime);
        FUN_004a0370(&fStack_48, &fStack_48, &fStack_24, DAT_00e44564 - local_50);
        iVar1 = *(int *)(this + 0x2d0);
        fVar14 = *(float *)(this + 0x80);
        bVar3 = *(byte *)(iVar1 + 0x8e3) & 1;
        fVar12 = (DAT_00e445ac - *(float *)(this + 0x138)) * fVar14 + *(float *)(this + 0x138);
        if (bVar3 != 0) {
            fVar12 = *(float *)(this + 0x208);
        }
        local_50 = *(float *)(this + 0x2b4);
        fVar13 = *(float *)(this + 0x118);
        if (bVar3 != 0) {
            fVar13 = *(float *)(this + 0x208);
        }
        fVar12 = (fVar13 - fVar12) * local_50 + fVar12;
        fVar13 = (*(float *)(this + 0x114) - *(float *)(this + 0x134)) * local_50 +
                 *(float *)(this + 0x134);
        if (bVar3 != 0) {
            fVar13 = *(float *)(this + 0x20c);
        }
        if (*(char *)(this + 0x288) != '\0') {
            fVar13 = fVar13 * _DAT_00d5ccf8;
        }
        fVar13 = fVar13 * (_DAT_00d5780c -
                          (float)((uint)(fStack_58 * _DAT_00d5f704) & DAT_00e44680) * DAT_00e44748 *
                          _DAT_00d5f700);
        uStack_3c._0_4_ = fStack_24 * fVar13 + fVar12 * fStack_48 + (float)uStack_3c;
        uStack_3c._4_4_ = fStack_20 * fVar13 + fVar12 * fStack_44 + uStack_3c._4_4_;
        fStack_48 = (float)uStack_3c - *pf;
        fStack_34 = fStack_1c * fVar13 + fVar12 * fStack_40 + fStack_34;
        fStack_44 = uStack_3c._4_4_ - *(float *)(this + 0x27c);
        fStack_40 = fStack_34 - *(float *)(this + 0x280);
        uStack_5d = DAT_0112a900;
        fVar12 = (DAT_00d5efa0 - *(float *)(this + 0x144)) * fVar14 + *(float *)(this + 0x144);
        if ((*(byte *)(iVar1 + 0x8e3) & 1) != 0) {
            fVar12 = (DAT_00d5efa0 - *(float *)(this + 0x21c)) * fVar14 + *(float *)(this + 0x21c);
        }
        pf = (float *)(this + 0x260);
        *pf = (*(float *)(this + 0x124) - fVar12) * local_50 + fVar12;
        if ((*(byte *)(iVar1 + 0x8e3) & 1) != 0) {
            *pf = (*(float *)(this + 0x21c) - fVar12) * local_50 + fVar12;
        }
        fVar14 = 0.0;
        if (((*statePtr != 0) && (*statePtr != 0x48)) && (*(char *)(iVar1 + 0x1028) != '\0')) {
            fVar14 = _DAT_00d5780c;
        }
        *(float *)(this + 0x2cc) =
             (fVar14 - *(float *)(this + 0x2cc)) * _DAT_00e51208 + *(float *)(this + 0x2cc);
        FUN_006de000(&uStack_3c, &fStack_48, this + 0x278, (undefined8 *)(this + 0x254), pf,
                     this + 700, statePtr, local_50, *(char *)(this + 0x288), &uStack_5d, this + 0x2b8,
                     deltaTime);
        local_54 = SQRT(fStack_48 * fStack_48 + fStack_40 * fStack_40);
        local_50 = fStack_44;
        fStack_4c = DAT_00e44564 - fStack_40;
        DAT_0112a900 = uStack_5d;
        fStack_5c = DAT_00e44564 - fStack_48;
        fVar14 = ((*(float *)(this + 0x128) - *(float *)(this + 0x148)) *
                  *(float *)(this + 0x2b4) + *(float *)(this + 0x148)) *
                 *(float *)(this + 0x60);
        *(float *)(this + 0x230) =
             ((float)uStack_3c - *(float *)(this + 0x230)) * fVar14 + *(float *)(this + 0x230);
        *(float *)(this + 0x234) =
             (uStack_3c._4_4_ - *(float *)(this + 0x234)) * fVar14 + *(float *)(this + 0x234);
        *(float *)(this + 0x238) =
             (fStack_34 - *(float *)(this + 0x238)) * fVar14 + *(float *)(this + 0x238);
        fVar10_10 = (float10)FUN_006c89b0(*(undefined4 *)(this + 0x14c), *(undefined4 *)(this + 300),
                                          *(undefined4 *)(this + 0x2b4));
        fStack_58 = (float)fVar10_10;
        dVar1 = (double)local_50;
        fVar14 = (float)fVar10_10;
        FUN_00b9a9fa();
        fVar10_10 = (float10)FUN_006c89d0(*(float *)(this + 0x224) * DAT_00e445c8, (float)dVar1, fVar14);
        dVar1 = (double)fStack_5c;
        *(float *)(this + 0x224) = (float)(fVar10_10 * (float10)DAT_00e44748);
        fVar14 = fStack_58;
        FUN_00b9a9fa(fStack_58);
        fVar10_11 = (float10)FUN_006c89d0(*(float *)(this + 0x228) * DAT_00e445c8, (float)dVar1, fVar14);
        fVar10_10 = (float10)DAT_00e44748;
        *(undefined4 *)(this + 0x22c) = 0;
        *(float *)(this + 0x228) = (float)(fVar10_11 * fVar10_10);
        *(undefined8 *)(this + 0x254) = *(undefined8 *)(this + 0x230);
        *(undefined8 *)(this + 0x248) = *(undefined8 *)(this + 0x224);
        *(undefined4 *)(this + 0x250) = *(undefined4 *)(this + 0x22c);
        *(undefined4 *)(this + 0x25c) = *(undefined4 *)(this + 0x238);
        FUN_006dda40(&uStack_30);
        FUN_006ca5e0((undefined4 *)(this + 0x23c), &uStack_30, &uStack_30);
        fVar12 = DAT_00d5f6fc;
        *(undefined4 *)(this + 0x20) = uStack_30;
        *(undefined4 *)(this + 0x24) = uStack_2c;
        *(undefined4 *)(this + 0x28) = uStack_28;
        fVar14 = _DAT_00d5780c;
        *(float *)(this + 0x2c) = _DAT_00d5780c;
        *(undefined4 *)(this + 0x30) = *(undefined4 *)(this + 0x23c);
        *(undefined4 *)(this + 0x34) = *(undefined4 *)(this + 0x240);
        *(float *)(this + 0x3c) = fVar14;
        *(undefined4 *)(this + 0x38) = *(undefined4 *)(this + 0x244);
        fVar13 = DAT_00e445c8;
        fVar14 = *(float *)(this + 0x268) + *(float *)(this + 0x248);
        if ((fVar14 <= fVar12) || (fVar12 = DAT_00d5f6f8, DAT_00d5f6f8 <= fVar14)) {
            fVar14 = fVar12;
        }
        *(float *)(this + 0x40) = fVar14 * DAT_00e445c8;
        *(float *)(this + 0x44) = *(float *)(this + 0x24c) * fVar13;
        *(float *)(this + 0x48) = *(float *)(this + 0x250) * fVar13;
        fVar13 = (*(float *)(this + 0x264) + *(float *)(this + 0x260)) * fVar13;
        *(float *)(this + 0x50) = fVar13;
        fVar14 = 0.0;
        if ((fVar13 <= 0.0) || (fVar14 = DAT_00d5eff8, DAT_00d5eff8 <= fVar13)) {
            fVar13 = fVar14;
        }
        *(float *)(this + 0x50) = fVar13;
    }
    return;
}