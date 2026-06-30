// FUNC_NAME: Vehicle::updatePhysics

void __thiscall Vehicle::updatePhysics(int thisPtr, float deltaTime)
{
    int *physicsBodyPtr = *(int **)(thisPtr + 0xc0);
    int *vtableBase;
    float contactDist;
    int contactResult;
    float suspensionForce;
    float tempFloat;
    float fVar9;
    float fVar10;
    double dVar11;
    float fVar12;
    float fVar13;
    float fVar14;
    float local_54;
    float local_50;
    float fStack_58;
    float fStack_5c;
    float fStack_4c;
    float fStack_48;
    float fStack_44;
    float fStack_40;
    float fStack_34;
    float fStack_24;
    float fStack_20;
    float fStack_1c;
    undefined8 uStack_3c;
    undefined4 uStack_30;
    undefined4 uStack_2c;
    undefined4 uStack_28;
    float fStack_24_2;
    float fStack_20_2;
    float fStack_1c_2;
    char uStack_5d;

    if (physicsBodyPtr == 0) {
        local_54 = 0.0f;
        vtableBase = 0;
    } else {
        local_54 = (float)((int)physicsBodyPtr - 0x48);
        vtableBase = (int *)((int)physicsBodyPtr - 0x48);
    }

    local_50 = 0.0f;
    // Query ground contact: function at vtable+0x10 takes a large float threshold and returns bool + distance
    contactResult = (**(code **)(*vtableBase + 0x10))(0x55859efa, &local_50);
    // contactDist is the float returned via the second argument? Actually fStack_58 is used but not set; assume it's the distance from the call
    fStack_58 = local_50; // workaround: assume the call sets local_50 and that's the distance
    *(int *)(thisPtr + 0x2d0) = (contactResult != 0) ? (int)fStack_58 : 0;

    if ((*(int *)(thisPtr + 200) != 0) && (*(int *)(thisPtr + 200) != 0x48) &&
        ((*(int *)(thisPtr + 0x2d0) == 0 || (FUN_007fd720() == 0)))) {
        FUN_006c85e0(deltaTime);
        local_54 = *(float *)(thisPtr + 0x2b4);
        fVar9 = (float)FUN_006dd660(fStack_5c);
        fVar14 = _DAT_00d5780c;
        local_50 = fVar9;
        fStack_58 = (local_50 - local_54) * _DAT_00e51204 + local_54;
        *(float *)(thisPtr + 0x2b4) = fStack_58;
        if (0.0f < fStack_58) {
            if (fVar14 <= fStack_58) {
                fStack_58 = fVar14;
            }
        } else {
            fStack_58 = 0.0f;
        }
        *(float *)(thisPtr + 0x2b4) = fStack_58;
        FUN_006dd900(thisPtr + 0x26c, physicsBodyPtr, fStack_58);
        FUN_006dd760(deltaTime);
        FUN_006dc670(&fStack_24, thisPtr + 0x26c, fStack_5c);
        float *pfVar2 = (float *)(thisPtr + 0x278);
        FUN_006dc730(pfVar2, thisPtr + 0x26c, thisPtr + 0x23c, physicsBodyPtr, *(int *)(thisPtr + 0x2b4));
        uStack_3c = *(undefined8 *)(thisPtr + 0x23c);
        fStack_34 = *(float *)(thisPtr + 0x244);
        uStack_3c._4_4_ = (float)((ulonglong)uStack_3c >> 0x20);
        fStack_44 = *(float *)(thisPtr + 0x27c) - uStack_3c._4_4_;
        uStack_3c._0_4_ = (float)uStack_3c;
        fStack_48 = *pfVar2 - (float)uStack_3c;
        fStack_40 = *(float *)(thisPtr + 0x280) - fStack_34;
        dVar11 = (double)fStack_48;
        uStack_3c = *(undefined8 *)(thisPtr + 0x23c);
        FUN_00b9a9fa();
        local_54 = (float)dVar11;
        dVar11 = (double)fStack_44;
        FUN_00b9a9fa();
        fStack_58 = _DAT_00e44564 - (float)dVar11;
        fVar12 = *(float *)(thisPtr + 0xdc) * _DAT_00e445c8;
        fVar14 = _DAT_00e44564 - fVar12;
        if ((fStack_58 <= fVar14) || (fVar14 = fVar12, fVar12 <= fStack_58)) {
            fStack_58 = fVar14;
        }
        fVar14 = *(float *)(thisPtr + 0xd8);
        if ((*(byte *)(*(int *)(thisPtr + 0x2d0) + 0x8e3) & 1) != 0) {
            fVar14 = *(float *)(thisPtr + 0x218);
        }
        local_50 = fVar14 * _DAT_00e445c8 + fStack_58;
        dVar11 = (double)local_54;
        FUN_00b99fcb();
        fStack_48 = (float)dVar11;
        dVar11 = (double)local_54;
        FUN_00b99e20();
        fStack_48 = _DAT_00e44564 - fStack_48;
        fStack_40 = _DAT_00e44564 - (float)dVar11;
        fStack_44 = 0.0f;
        fVar9 = (float)FUN_006c93c0(fStack_5c);
        local_54 = (float)CONCAT31(local_54._1_3_, 1);
        if (fVar9 <= 0.0f) {
            local_54 = (float)((uint)local_54._1_3_ << 8);
        }
        FUN_006ca4b0(fStack_5c, local_54, 0, deltaTime);
        FUN_004a0370(&fStack_48, &fStack_48, &fStack_24, _DAT_00e44564 - local_50);
        int iVar4 = *(int *)(thisPtr + 0x2d0);
        fVar14 = *(float *)(thisPtr + 0x80);
        byte bVar6 = *(byte *)(iVar4 + 0x8e3) & 1;
        fVar12 = (_DAT_00e445ac - *(float *)(thisPtr + 0x138)) * fVar14 + *(float *)(thisPtr + 0x138);
        if (bVar6 != 0) {
            fVar12 = *(float *)(thisPtr + 0x208);
        }
        local_50 = *(float *)(thisPtr + 0x2b4);
        fVar13 = *(float *)(thisPtr + 0x118);
        if (bVar6 != 0) {
            fVar13 = *(float *)(thisPtr + 0x208);
        }
        fVar12 = (fVar13 - fVar12) * local_50 + fVar12;
        fVar13 = (*(float *)(thisPtr + 0x114) - *(float *)(thisPtr + 0x134)) * local_50 + *(float *)(thisPtr + 0x134);
        if (bVar6 != 0) {
            fVar13 = *(float *)(thisPtr + 0x20c);
        }
        if (*(char *)(thisPtr + 0x288) != 0) {
            fVar13 = fVar13 * _DAT_00d5ccf8;
        }
        fVar13 = fVar13 * (_DAT_00d5780c - (float)((uint)(fStack_58 * _DAT_00d5f704) & _DAT_00e44680) * _DAT_00e44748 * _DAT_00d5f700);
        uStack_3c._0_4_ = fStack_24 * fVar13 + fVar12 * fStack_48 + (float)uStack_3c;
        uStack_3c._4_4_ = fStack_20 * fVar13 + fVar12 * fStack_44 + uStack_3c._4_4_;
        fStack_48 = (float)uStack_3c - *pfVar2;
        fStack_34 = fStack_1c * fVar13 + fVar12 * fStack_40 + fStack_34;
        fStack_44 = uStack_3c._4_4_ - *(float *)(thisPtr + 0x27c);
        fStack_40 = fStack_34 - *(float *)(thisPtr + 0x280);
        uStack_5d = _DAT_0112a900;
        fVar12 = (_DAT_00d5efa0 - *(float *)(thisPtr + 0x144)) * fVar14 + *(float *)(thisPtr + 0x144);
        if ((*(byte *)(iVar4 + 0x8e3) & 1) != 0) {
            fVar12 = (_DAT_00d5efa0 - *(float *)(thisPtr + 0x21c)) * fVar14 + *(float *)(thisPtr + 0x21c);
        }
        pfVar2 = (float *)(thisPtr + 0x260);
        *pfVar2 = (*(float *)(thisPtr + 0x124) - fVar12) * local_50 + fVar12;
        if ((*(byte *)(iVar4 + 0x8e3) & 1) != 0) {
            *pfVar2 = (*(float *)(thisPtr + 0x21c) - fVar12) * local_50 + fVar12;
        }
        fVar14 = 0.0f;
        if ((*physicsBodyPtr != 0) && (*physicsBodyPtr != 0x48) && (*(char *)(iVar4 + 0x1028) != 0)) {
            fVar14 = _DAT_00d5780c;
        }
        *(float *)(thisPtr + 0x2cc) = (fVar14 - *(float *)(thisPtr + 0x2cc)) * _DAT_00e51208 + *(float *)(thisPtr + 0x2cc);
        FUN_006de000(&uStack_3c, &fStack_48, thisPtr + 0x278, (undefined8 *)(thisPtr + 0x254), pfVar2,
                     thisPtr + 700, physicsBodyPtr, local_50, *(char *)(thisPtr + 0x288), &uStack_5d, thisPtr + 0x2b8,
                     deltaTime);
        local_54 = SQRT(fStack_48 * fStack_48 + fStack_40 * fStack_40);
        local_50 = fStack_44;
        fStack_4c = _DAT_00e44564 - fStack_40;
        _DAT_0112a900 = uStack_5d;
        fStack_5c = _DAT_00e44564 - fStack_48;
        fVar14 = ((*(float *)(thisPtr + 0x128) - *(float *)(thisPtr + 0x148)) * *(float *)(thisPtr + 0x2b4) + *(float *)(thisPtr + 0x148)) * *(float *)(thisPtr + 0x60);
        *(float *)(thisPtr + 0x230) = ((float)uStack_3c - *(float *)(thisPtr + 0x230)) * fVar14 + *(float *)(thisPtr + 0x230);
        *(float *)(thisPtr + 0x234) = (uStack_3c._4_4_ - *(float *)(thisPtr + 0x234)) * fVar14 + *(float *)(thisPtr + 0x234);
        *(float *)(thisPtr + 0x238) = (fStack_34 - *(float *)(thisPtr + 0x238)) * fVar14 + *(float *)(thisPtr + 0x238);
        fVar9 = (float)FUN_006c89b0(*(int *)(thisPtr + 0x14c), *(int *)(thisPtr + 300), *(float *)(thisPtr + 0x2b4));
        fStack_58 = fVar9;
        dVar11 = (double)local_50;
        fVar14 = fVar9;
        FUN_00b9a9fa(fVar14);
        fVar9 = (float)FUN_006c89d0(*(float *)(thisPtr + 0x224) * _DAT_00e445c8, (float)dVar11, fVar14);
        dVar11 = (double)fStack_5c;
        *(float *)(thisPtr + 0x224) = (float)(fVar9 * (float)_DAT_00e44748);
        fVar14 = fStack_58;
        FUN_00b9a9fa(fStack_58);
        fVar10 = (float)FUN_006c89d0(*(float *)(thisPtr + 0x228) * _DAT_00e445c8, (float)dVar11, fVar14);
        fVar9 = (float)_DAT_00e44748;
        *(int *)(thisPtr + 0x22c) = 0;
        *(float *)(thisPtr + 0x228) = (float)(fVar10 * fVar9);
        *(undefined8 *)(thisPtr + 0x254) = *(undefined8 *)(thisPtr + 0x230);
        *(undefined8 *)(thisPtr + 0x248) = *(undefined8 *)(thisPtr + 0x224);
        *(int *)(thisPtr + 0x250) = *(int *)(thisPtr + 0x22c);
        *(int *)(thisPtr + 0x25c) = *(int *)(thisPtr + 0x238);
        FUN_006dda40(&uStack_30);
        FUN_006ca5e0((int *)(thisPtr + 0x23c), &uStack_30, &uStack_30);
        fVar12 = _DAT_00d5f6fc;
        *(int *)(thisPtr + 0x20) = uStack_30;
        *(int *)(thisPtr + 0x24) = uStack_2c;
        *(int *)(thisPtr + 0x28) = uStack_28;
        fVar14 = _DAT_00d5780c;
        *(float *)(thisPtr + 0x2c) = _DAT_00d5780c;
        *(int *)(thisPtr + 0x30) = *(int *)(thisPtr + 0x23c);
        *(int *)(thisPtr + 0x34) = *(int *)(thisPtr + 0x240);
        *(float *)(thisPtr + 0x3c) = fVar14;
        *(int *)(thisPtr + 0x38) = *(int *)(thisPtr + 0x244);
        fVar13 = _DAT_00e445c8;
        fVar14 = *(float *)(thisPtr + 0x268) + *(float *)(thisPtr + 0x248);
        if ((fVar14 <= fVar12) || (fVar12 = _DAT_00d5f6f8, _DAT_00d5f6f8 <= fVar14)) {
            fVar14 = fVar12;
        }
        *(float *)(thisPtr + 0x40) = fVar14 * _DAT_00e445c8;
        *(float *)(thisPtr + 0x44) = *(float *)(thisPtr + 0x24c) * fVar13;
        *(float *)(thisPtr + 0x48) = *(float *)(thisPtr + 0x250) * fVar13;
        fVar13 = (*(float *)(thisPtr + 0x264) + *(float *)(thisPtr + 0x260)) * fVar13;
        *(float *)(thisPtr + 0x50) = fVar13;
        fVar14 = 0.0f;
        if ((fVar13 <= 0.0f) || (fVar14 = _DAT_00d5eff8, _DAT_00d5eff8 <= fVar13)) {
            fVar13 = fVar14;
        }
        *(float *)(thisPtr + 0x50) = fVar13;
    }
    return;
}