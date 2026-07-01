// FUNC_NAME: AICarBehavior::updateSteering

void __thiscall AICarBehavior::updateSteering(int32_t thisPtr, float param2) {
    int32_t *vtablePtr;
    bool bVar2;
    char cVar3;
    int32_t iVar4;
    float *currentPos;
    float *someTargetPos;
    float *someDirection;
    float fVar8;
    float fVar9;
    float fVar10;
    float fVar11;
    float fVar12;
    float fVar13;
    float fVar14;
    float unaff_retaddr;
    float localD;
    float localC;
    float localB;
    float localA;
    float local9;
    float local8;
    float local7;
    uint64_t uStack_1c;
    float fStack_14;
    float fStack_10;
    float fStack_c;
    float fStack_8;

    iVar4 = *(int32_t *)(*(int32_t *)(thisPtr + 0x50) + 0x70);
    if ((((iVar4 != 0) &&
          (vtablePtr = (int32_t *)(iVar4 + -0x48), vtablePtr != (int32_t *)0x0)) &&
         (*(int32_t *)(thisPtr + 0x50) != 0)) && (iVar4 = FUN_005466a0(), *(int8_t *)(iVar4 + 0xd8) != '\a')) {
        (**(code **)(*vtablePtr + 0x4c))((int32_t)&uStack_1c + 4);
        if (fStack_14 * fStack_14 + uStack_1c._4_4_ * uStack_1c._4_4_ +
            (float)uStack_1c * (float)uStack_1c < _DAT_00d5780c) {
            iVar4 = FUN_00471610();
            uStack_1c = *(undefined8 *)(iVar4 + 0x20);
            fStack_14 = *(float *)(iVar4 + 0x28);
        }
        FUN_0043a210(&uStack_1c, &uStack_1c);
        fStack_38 = 0.0;
        fStack_34 = _DAT_00d5780c;
        currentPos = (float *)FUN_0086d5a0();
        someTargetPos = (float *)FUN_0086d500();
        FUN_0086d860(&fStack_28);
        if ((*(uint8_t *)(thisPtr + 0x6c) & 1) == 0) {
            fStack_10 = fStack_28 - *(float *)(thisPtr + 0x80);
            fStack_c = fStack_24 - *(float *)(thisPtr + 0x84);
            fStack_8 = fStack_20 - *(float *)(thisPtr + 0x88);
            someDirection = (float *)FUN_00471610();
            fVar9 = (*someDirection * fStack_10 + someDirection[1] * fStack_c + someDirection[2] * fStack_8) * _DAT_00d75fcc;
            fStack_28 = *(float *)(thisPtr + 0x80) + *someDirection * fVar9 + fStack_10;
            fStack_24 = *(float *)(thisPtr + 0x84) + someDirection[1] * fVar9 + fStack_c;
            fStack_20 = *(float *)(thisPtr + 0x88) + someDirection[2] * fVar9 + fStack_8;
            *(uint64_t *)(thisPtr + 0x80) = CONCAT44(fStack_24, fStack_28);
            *(float *)(thisPtr + 0x88) = fStack_20;
        } else {
            *(uint64_t *)(thisPtr + 0x80) = CONCAT44(fStack_24, fStack_28);
            *(float *)(thisPtr + 0x88) = fStack_20;
            *(uint32_t *)(thisPtr + 0x6c) = *(uint32_t *)(thisPtr + 0x6c) & 0xfffffffe;
        }
        fStack_8 = fStack_20 - currentPos[2];
        fStack_c = fStack_24 - currentPos[1];
        fStack_10 = fStack_28 - *currentPos;
        fStack_30 = fStack_8 * fStack_8 + fStack_c * fStack_c + fStack_10 * fStack_10;
        cVar3 = FUN_0086eb20(unaff_retaddr);
        if (cVar3 == '\0') {
            FUN_0086dcc0(&fStack_34, &fStack_38, fStack_30, &fStack_28, &uStack_1c, someTargetPos);
            FUN_0043a210(&fStack_10, &fStack_10);
            fVar9 = *someTargetPos;
            fVar13 = fVar9 * fStack_10 + someTargetPos[1] * fStack_c + someTargetPos[2] * fStack_8;
            fStack_2c = fVar9 * (float)uStack_1c + someTargetPos[1] * uStack_1c._4_4_ + someTargetPos[2] * fStack_14;
            if (DAT_00d75f3c <= fStack_30) {
                if ((0.0 <= fVar13) || (fStack_2c <= 0.0)) {
                    fVar8 = (float10)FUN_007f3770(&fStack_10);
                    fVar8 = (float10)FUN_00871bd0((float)fVar8);
                    fVar9 = (float)fVar8;
                } else {
                    fVar9 = someTargetPos[1] * uStack_1c._4_4_ + (DAT_00e44564 - someTargetPos[2]) * (float)uStack_1c +
                            fVar9 * fStack_14;
                    fVar14 = DAT_00d5ccf8;
                    if ((fVar9 < DAT_00d5ccf8) || (fVar14 = _DAT_00d5780c, _DAT_00d5780c < fVar9)) {
                        fVar9 = fVar14;
                    }
                    fStack_38 = *(float *)(*(int32_t *)(thisPtr + 0x50) + 0x84) * DAT_00e445a0;
                    if (DAT_00d58cbc <= fStack_38) {
                        if (_DAT_00d5780c < fStack_38) {
                            fStack_38 = _DAT_00d5780c;
                        }
                        fStack_34 = 0.0;
                    } else {
                        fStack_38 = DAT_00d58cbc;
                        fStack_34 = 0.0;
                    }
                }
            } else {
                fVar9 = 0.0;
            }
            fVar14 = fVar9;
            if (param2._0_1_ != '\0') {
                fVar8 = (float10)(**(code **)(**(int32_t **)(thisPtr + 0x5c) + 0x1b0))();
                fVar8 = (fVar8 - (float10)_DAT_00d75fc8) * (float10)_DAT_00d75fc4;
                param2 = (float)fVar8;
                if ((float10)0 < fVar8) {
                    fVar12 = param2;
                    if (_DAT_00d5780c <= param2) {
                        fVar12 = _DAT_00d5780c;
                    }
                } else {
                    fVar12 = 0.0;
                }
                fVar11 = (fVar12 + _DAT_00d5780c) * DAT_00d5eee4;
                fVar10 = _DAT_00d5780c - fVar12 * DAT_00d5ef6c;
                if ((*(float *)(thisPtr + 0x30) < fVar11) || (fVar10 < _DAT_00d5780c)) {
                    fVar11 = *(float *)(thisPtr + 0x30) / fVar11;
                    if (0.0 < fVar11) {
                        if (_DAT_00d5780c <= fVar11) {
                            fVar11 = _DAT_00d5780c;
                        }
                    } else {
                        fVar11 = 0.0;
                    }
                    fVar12 = DAT_00d5ef88 - fVar12 * _DAT_00d5cf70;
                    if (fVar12 < 0.0) {
                        fVar12 = 0.0;
                    }
                    fVar14 = DAT_00d58cbc;
                    if ((DAT_00d58cbc < fVar10) && (fVar14 = fVar10, _DAT_00d5780c <= fVar10)) {
                        fVar14 = _DAT_00d5780c;
                    }
                    fVar12 = (fVar14 - fVar12) * fVar11 * fVar11 + fVar12;
                    fVar14 = DAT_00e44564 - fVar12;
                    if ((DAT_00e44564 - fVar12 < fVar9) && (fVar14 = fVar9, fVar12 <= fVar9)) {
                        fVar14 = fVar12;
                    }
                }
            }
            if (DAT_00d5efd0 < fVar13) {
                fVar14 = (_DAT_00d5780c - fVar13 * fVar13) * fVar14;
            }
            FUN_0086b830(fVar14);
            FUN_0086b7b0(fStack_34);
            FUN_0086b7d0(fStack_38);
            FUN_0086b7f0(0);
            FUN_0086b810(0);
            if ((fVar13 <= 0.0) || (0.0 <= fStack_2c)) {
                bVar2 = false;
                fVar9 = DAT_00d75f5c;
            } else {
                bVar2 = true;
                fVar9 = *(float *)(DAT_0112af68 + 0x374);
            }
            if ((fStack_30 < fVar9) && ((*(uint32_t *)(thisPtr + 0x6c) >> 5 & 1) != 0)) {
                if ((!bVar2) || (fStack_30 < DAT_00d75f5c)) {
                    FUN_0086cbc0(&param2);
                    if (param2 == 0.0) {
                        *(uint32_t *)(thisPtr + 0x6c) = *(uint32_t *)(thisPtr + 0x6c) | 0x20;
                        *(uint32_t *)(thisPtr + 0x6c) = *(uint32_t *)(thisPtr + 0x6c) & 0xffffff3f;
                    } else {
                        *(uint32_t *)(thisPtr + 0x6c) = *(uint32_t *)(thisPtr + 0x6c) & 0xffffffdf;
                        if (param2 == 1.4013e-45) {
                            *(uint32_t *)(thisPtr + 0x6c) = *(uint32_t *)(thisPtr + 0x6c) | 0x80;
                        } else {
                            *(uint32_t *)(thisPtr + 0x6c) = *(uint32_t *)(thisPtr + 0x6c) | 0x40;
                        }
                    }
                } else {
                    FUN_0086cc70();
                    *(uint32_t *)(thisPtr + 0x6c) = *(uint32_t *)(thisPtr + 0x6c) & 0xffffff9f;
                    *(uint32_t *)(thisPtr + 0x6c) = *(uint32_t *)(thisPtr + 0x6c) | 0x80;
                }
            }
            fVar8 = (float10)(**(code **)(**(int32_t **)(thisPtr + 0x5c) + 0x1b0))();
            param2 = (float)fVar8;
            if (((float10)_DAT_00d75fc0 < fVar8) && (fStack_2c < DAT_00d75cb4)) {
                fVar9 = param2 * _DAT_00d75fbc;
                if (0.0 < fVar9) {
                    if (_DAT_00d5780c <= fVar9) {
                        fVar9 = _DAT_00d5780c;
                    }
                } else {
                    fVar9 = 0.0;
                }
                fVar13 = _DAT_00d5c458;
                if (_DAT_00d5c458 < fStack_2c) {
                    fVar13 = fStack_2c;
                }
                FUN_00470130(&fStack_28, (_DAT_00d5780c - fVar13) * fVar9 * unaff_retaddr * _DAT_00d75fb8, 0);
            }
        }
    }
    return;
}