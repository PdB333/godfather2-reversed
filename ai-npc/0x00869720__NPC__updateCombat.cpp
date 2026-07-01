// FUNC_NAME: NPC::updateCombat

void __thiscall NPC::updateCombat(NPC* this, float dt)
{
    bool bVar1;
    char cVar2;
    char* pcVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    float* pfVar7;
    int* piVar8;
    float10 fVar9;
    float fVar10;
    float fVar11;
    float fVar12;
    double dVar13;
    double dVar14;
    float fVar15;

    // locals
    float fStack_24;
    float local_1c, local_18, local_14;
    float local_4c, local_48, local_54, local_38;
    float local_2c, local_28, local_20;
    int local_50;
    char local_56, local_55;
    undefined8 local_34; // actually a 2-float vector (x,y)
    int iStack_44, iStack_40, iStack_3c;

    local_54 = _DAT_00d5780c; // some global constant
    local_50 = 0;

    // If combat range <= 0
    if (this->ownerDistanceThreshold <= 0.0f) { // +0x3d8
        // If move away distance > 0
        if (0.0f < this->ownerMoveAwayDistance) { // +0x3dc
            iVar6 = getPlayerTransform(); // returns pointer to player's transform struct
            cVar2 = getDirectionToTarget(iVar6 + 0x30, &local_1c, &local_4c, &local_38);
            if ((cVar2 != '\0') && (0.0f <= local_4c)) {
                local_4c = (float)this->ownerThreatListIndex; // +0x3f1
                local_48 = (float)this->ownerSpeed; // +0x452
                fStack_24 = local_18;
                if (local_4c == 0.0f) {
                    // no threat, keep current velocity
                    local_28 = local_1c;
                    local_20 = local_14;
                } else {
                    // adjust velocity based on threat index and speed
                    dVar14 = (double)local_48;
                    FUN_00b99e20();
                    dVar13 = (double)local_48;
                    local_28 = local_1c - (float)dVar14 * local_4c;
                    FUN_00b99fcb();
                    local_20 = (float)dVar13 * local_4c + local_14;
                }
                fVar9 = (float10)FUN_00470250(&local_28);
                if ((float10)1.0f < fVar9) {
                    // compute desired movement vector
                    iVar6 = getPlayerTransform();
                    local_34.x = local_28 - *(float*)(iVar6 + 0x30);
                    local_34.y = fStack_24 - *(float*)(iVar6 + 0x34);
                    local_2c = local_20 - *(float*)(iVar6 + 0x38);
                    FUN_0043a210(&local_34, &local_34);
                    iVar6 = getPlayerTransform();
                    iVar4 = getPlayerTransform();
                    iVar5 = getPlayerTransform();
                    if (*(float*)(iVar4 + 0x24) * local_34.y + *(float*)(iVar6 + 0x20) * local_34.x + *(float*)(iVar5 + 0x28) * local_2c < DAT_00d62364) {
                        // heading away from threat
                        pfVar7 = (float*)getPlayerTransform();
                        iVar6 = getPlayerTransform();
                        iVar4 = getPlayerTransform();
                        if (_DAT_00d577a0 < *(float*)(iVar6 + 4) * local_34.y + *pfVar7 * local_34.x + *(float*)(iVar4 + 8) * local_2c) {
                            goto LAB_0086995b;
                        }
                        goto LAB_00869969;
                    }
                }
            }
        }
        // if not in some state (bit 0xb of flags and bit 0xe of other flags)
        if ((((uint)this->ownerStateFlags >> 0xb & 1) == 0) && (((uint)this->ownerOtherFlags >> 0xe & 1) == 0)) {
            FUN_00867570(); // maybe reset combat state?
        }
        // get current velocity
        local_1c = (float)this->ownerVelocity.x; // +0x414
        local_48 = (float)this->ownerSpeed; // +0x452
        local_18 = (float)this->ownerVelocity.y; // +0x415
        local_14 = (float)this->ownerVelocity.z; // +0x416
        FUN_008750c0(&local_28); // transform velocity to world space?
        local_4c = local_28;
        local_54 = local_20;
        iVar6 = getPlayerTransform();
        dVar14 = (double)local_4c;
        uVar22 = 1;
        uVar20 = 0;
        uVar21 = 0;
        piVar8 = &local_50;
        pfVar7 = &this->ownerCombatRange; // +0x3e6? Actually offset 0x3e6 (float)
        pfVar17 = &local_1c;
        fVar10 = local_48;
        pfVar19 = pfVar7;
        FUN_00b9a9fa(pfVar17, local_48, pfVar7, piVar8, 0, 0, 1);
        local_55 = FUN_00862970(iVar6 + 0x30, (float)dVar14, pfVar17, fVar10, pfVar19, piVar8, uVar21, uVar20, uVar22);

        if ((((local_55 == '\0') || (((float)this->ownerScale + (float)this->ownerCombatRange) * DAT_00d75738 < *pfVar7)) || (local_50 == 0)) || (((uint)this->ownerStateFlags >> 0xb & 1) == 0)) {
            // no line of sight or too close or no target or state forbids
            if (DAT_00d75778 < DAT_01205228 - (float)this->ownerAttackTimer) {
                if (local_55 == '\0') goto LAB_0086a2c9;
                if ((((float)this->ownerCombatRange <= DAT_00d5d934 && DAT_00d5d934 != (float)this->ownerCombatRange) && (((uint)this->ownerStateFlags >> 0xb & 1) == 0)) && ((cVar2 = FUN_008603b0(), cVar2 == '\0' && (cVar2 = FUN_00862490(5), cVar2 == '\0')))) {
                    local_48 = -NAN;
                    piVar8 = (int*)FUN_006c12a0(local_50, 0x10e5319e);
                    if (piVar8 != (int*)0x0) {
                        local_56 = '\x01';
                        cVar2 = FUN_00860440();
                        if ((cVar2 != '\0') || (cVar2 = FUN_00862490(5), cVar2 != '\0')) {
                            local_56 = '\0';
                        }
                        if (**(int**)(DAT_012233a0 + 4) == 0) {
                            iVar6 = 0;
                        } else {
                            iVar6 = **(int**)(DAT_012233a0 + 4) + -0x1f30;
                        }
                        iVar4 = (**(code**)(*piVar8 + 0x1e4))(); // get some ID
                        fVar10 = local_48;
                        if (iVar4 != iVar6) {
                            fVar10 = (float)piVar8[0x3f4]; // threat index?
                        }
                        if (local_56 != '\0') {
                            fVar11 = (float)(this->ownerCurrentThreat + -1); // +0x3f4
                            local_54 = 0.0f;
                            // Evaluate threat index change
                            if (((((-1 < (int)fVar11) && ((int)fVar11 < (int)(this->ownerThreatCount & 0x7fffffffU))) && (fVar11 != fVar10)) && (((cVar2 = FUN_00865780(fVar11, &local_54), cVar2 == '\0' || ((float)this->ownerCombatRange <= local_54)) && ((cVar2 = FUN_00860880(fVar11, &local_54), cVar2 == '\0' || (_DAT_00d75ce0 <= local_54)))))) || (((fVar11 = (float)(this->ownerCurrentThreat + 1), -1 < (int)fVar11 && ((int)fVar11 < (int)(this->ownerThreatCount & 0x7fffffffU))) && ((fVar11 != fVar10 && (((cVar2 = FUN_00865780(fVar11, &local_54), cVar2 == '\0' || ((float)this->ownerCombatRange <= local_54)) && ((cVar2 = FUN_00860880(fVar11, &local_54), cVar2 == '\0' || (_DAT_00d75ce0 <= local_54)))))))))) {
                                this->ownerCurrentThreat = (int)fVar11;
                                fVar10 = DAT_00d75764;
                                local_4c = DAT_00d5eee4;
                                if ((uint)ABS((float)this->ownerThreatCount) <= (uint)fVar11) {
                                    fVar11 = ABS((float)this->ownerThreatCount);
                                    local_4c = DAT_00e44564;
                                }
                                fVar15 = (float)(int)fVar11;
                                if ((int)fVar11 < 0) {
                                    fVar15 = fVar15 + DAT_00e44578;
                                }
                                fVar12 = (_DAT_00d5780c - (DAT_00d75cdc - (float)this->ownerCombatRange) * DAT_00d5f374) * DAT_00d75764;
                                this->ownerTargetIndex = (int)(fVar15 * DAT_00d75750 + local_4c);
                                fVar12 = fVar12 + (float)this->ownerAttackCooldown;
                                this->ownerAttackCooldown = (int)fVar12;
                                if (fVar12 < fVar10) {
                                    this->ownerAttackCooldown = (int)fVar10;
                                }
                                this->ownerAttackTimer = (int)DAT_01205228;
                                local_38 = fVar11;
                                FUN_00875190(&this->ownerThreatCooldown, 0);
                                goto LAB_0086a2c9;
                            }
                        }
                    }
                }
            }
        } else {
            // line of sight and target exists
            iVar6 = FUN_006c12d0(local_50, 0xa5975eb2);
            if ((iVar6 == 0) || ((*(uint*)(iVar6 + 0xc88) >> 0xb & 1) == 0)) {
                iVar6 = getPlayerTransform();
                fVar9 = (float10)FUN_00875220(this, iVar6 + 0x30);
                local_48 = (float)fVar9;
                local_54 = 0.0f;
                if ((float)this->ownerThreatListIndex <= _DAT_00d5c458) {
                    fVar10 = DAT_00d75ce4;
                    if ((local_48 < 0.0f) || (DAT_00d5f00c < local_48)) {
                        if ((local_48 < DAT_00d68264) && ((0.0f < local_48 || (local_48 < DAT_00e446a0)))) {
                            goto LAB_00869f28;
                        }
                    } else if (((uint)this->ownerOtherFlags >> 0x17 & 1) == 0) {
                        fVar10 = DAT_00d75ce8;
                    }
                    local_54 = fVar10;
                }
LAB_00869f28:
                pfVar7 = (float*)getPlayerTransform();
                local_48 = DAT_00e44564 - local_54;
                iVar6 = getPlayerTransform();
                local_1c = local_48 * *pfVar7 + *(float*)(iVar6 + 0x30);
                local_18 = pfVar7[1] * local_48 + *(float*)(iVar6 + 0x34);
                local_14 = pfVar7[2] * local_48 + *(float*)(iVar6 + 0x38);
                cVar2 = FUN_00864d70(&local_1c);
                if (cVar2 != '\0') {
                    iVar6 = getPlayerTransform();
                    fVar10 = (float)this->ownerCombatRange - ((float)this->ownerScale + (float)this->ownerCombatRange);
                    this->ownerDestination.x = (int)(*(float*)(iVar6 + 0x20) * fVar10 + local_1c);
                    this->ownerDestination.y = (int)(*(float*)(iVar6 + 0x24) * fVar10 + local_18);
                    this->ownerDestination.z = (int)(*(float*)(iVar6 + 0x28) * fVar10 + local_14);
                    this->ownerTargetIndex = (int)local_54;
                    this->ownerMoveAwayDistance = (int)DAT_00d5d934;
                    this->ownerSomeFlag = 0;
                    goto LAB_00869c45;
                }
            }
        }
LAB_00869c4d:
        if (local_55 == '\0') goto LAB_0086a2c9;
        if ((float)this->ownerSomeTimer <= 0.0f && (float)this->ownerSomeTimer != 0.0f) {
            this->ownerSomeTimer = 0;
        }
        fVar9 = (float10)(**(code**)(*this + 0x1b0))();
        if ((float10)DAT_00d75700 <= fVar9) goto LAB_0086a4ef;
        fVar10 = (float)this->ownerComboTimer;
        fVar11 = fVar10 + dt;
        if (((int)(fVar10 + _DAT_00d5c458) % 3 == 0) && ((int)(fVar11 + _DAT_00d5c458) % 3 != 0)) {
            this->ownerComboCount = 0;
        }
        if ((fVar10 < DAT_00d75cec) && (DAT_00d75cec <= fVar11)) {
            this->ownerHitCounter = this->ownerHitCounter + 1;
        }
        if ((fVar10 < DAT_00d5d934) && (DAT_00d5d934 <= fVar11)) {
            this->ownerHitCounter = this->ownerHitCounter + 99;
        }
        if (3 < this->ownerHitCounter) {
            cVar2 = FUN_008671a0();
            if (cVar2 != '\0') {
                this->ownerSomeFlag = 0;
            }
            fVar11 = DAT_00d5ccf8;
            this->ownerHitCounter = 0;
        }
        this->ownerComboTimer = (int)fVar11;
        fVar11 = DAT_00d75cc8;
        fVar10 = (float)this->ownerPatienceTimer;
        if ((fVar10 < _DAT_00d577a0) || (dt < fVar10)) {
            bVar1 = false;
        } else {
            bVar1 = true;
        }
        if (DAT_00d75cc8 < fVar10) {
            this->ownerPatienceTimer = (int)(fVar10 - dt);
        }
        if ((float)this->ownerComboTimer < DAT_00d5eee4) goto LAB_0086a4ef;
        if ((float)this->ownerPatienceTimer <= fVar11) goto LAB_0086a43a;
        if (!bVar1) goto LAB_0086a4ef;
    } else {
        pcVar3 = (char*)FUN_00549a40(&local_55);
        if (*pcVar3 != '\0') {
LAB_0086995b:
            local_54 = DAT_00d5ccf8;
        }
LAB_00869969:
        iVar6 = getPlayerTransform();
        local_2c = *(float*)(iVar6 + 0x28);
        local_34 = *(undefined8*)(iVar6 + 0x20);
        pcVar3 = (char*)FUN_00549a40(&local_55);
        if (*pcVar3 != '\0') {
            local_34.x = local_34.x * DAT_00d5ccf8;
            local_34.y = local_34.y * DAT_00d5ccf8;
            local_2c = local_2c * DAT_00d5ccf8;
        }
        pfVar7 = (float*)getPlayerTransform();
        local_1c = *pfVar7 * local_54;
        local_18 = pfVar7[1] * local_54;
        local_14 = pfVar7[2] * local_54;
        iVar6 = getPlayerTransform();
        local_28 = *(float*)(iVar6 + 0x30);
        fStack_24 = *(float*)(iVar6 + 0x34);
        local_20 = local_14 * DAT_00d5eee4 + local_2c * DAT_00d75744 + *(float*)(iVar6 + 0x38);
        local_28 = local_1c * DAT_00d5eee4 + local_34.x * DAT_00d75744 + local_28;
        fStack_24 = local_18 * DAT_00d5eee4 + local_34.y * DAT_00d75744 + fStack_24;
        local_4c = 0.0f;
        local_54 = 0.0f;
        iVar6 = getPlayerTransform();
        dVar14 = (double)local_1c;
        uVar21 = 1;
        pfVar17 = &local_54;
        pfVar19 = &local_4c;
        piVar8 = &local_50;
        pfVar7 = &this->ownerCombatRange;
        pfVar18 = pfVar7;
        FUN_00b9a9fa(pfVar7, piVar8, pfVar19, pfVar17, 1);
        fVar10 = (float)dVar14;
        dVar14 = (double)local_34.x;
        pfVar16 = &local_28;
        FUN_00b9a9fa(pfVar16, fVar10);
        local_55 = FUN_00862970(iVar6 + 0x30, (float)dVar14, pfVar16, fVar10, pfVar18, piVar8, pfVar19, pfVar17, uVar21);
        if ((local_55 != '\0') && (((fVar9 = (float10)(**(code**)(*this + 0x1b0))(), (float10)_DAT_00d75cf0 <= fVar9 || (local_54 <= DAT_00d58cbc)) || (fVar9 = (float10)(**(code**)(*this + 0x1b0))(), (float10)*pfVar7 <= fVar9 * (float10)local_54 * (float10)_DAT_00d7576c)))) {
            pcVar3 = (char*)FUN_00549a40(&local_56);
            if (*pcVar3 == '\0') {
                local_54 = (float)this->ownerWeaponRange1; // +0x467
            } else {
                local_54 = (float)this->ownerWeaponRange2; // +0x468
            }
            iVar6 = getPlayerTransform();
            cVar2 = FUN_00865000(iVar6 + 0x30, &local_1c, &local_48, &local_38);
            fVar10 = DAT_00d5ccf8;
            if (cVar2 != '\0') {
                fVar10 = local_48;
            }
            if (fVar10 - local_4c <= local_54 * DAT_00e445a4) {
                if ((this->ownerAttackAttempt != 0) || ((float)this->ownerDistanceThreshold <= _DAT_00d577a0)) goto LAB_00869c4d;
                cVar2 = FUN_0085e970();
                FUN_0085ea10(cVar2 == '\0');
                this->ownerAttackAttempt = this->ownerAttackAttempt + 1;
LAB_00869c45:
                this->ownerComboTimer = 0;
                goto LAB_00869c4d;
            }
        }
LAB_0086a2c9:
        fVar10 = (float)this->ownerComboTimer;
        fVar11 = DAT_00e44564;
        if ((_DAT_00d577a0 <= fVar10) || (fVar11 = fVar10, DAT_00e44750 <= fVar10)) {
            this->ownerComboTimer = (int)(fVar11 - dt);
        }
        if ((DAT_0112dfd4 == 0) || (DAT_0112dfd4 == 0x48)) goto LAB_0086a4ef;
        fVar9 = (float10)(**(code**)(*this + 0x1a8))();
        local_4c = (float)fVar9;
        if (DAT_0112dfd4 == 0) {
            piVar8 = (int*)0x0;
        } else {
            piVar8 = (int*)(DAT_0112dfd4 + -0x48);
        }
        fVar9 = (float10)(**(code**)(*piVar8 + 0x1a8))();
        local_54 = (float)fVar9;
        if (((fVar9 <= (float10)_DAT_00d75ce0) || (local_4c <= DAT_00d5d7b8)) || (local_54 <= local_4c * DAT_00d5eee4)) goto LAB_0086a4ef;
        iVar6 = getPlayerTransform();
        fVar9 = (float10)FUN_004702b0(iVar6 + 0x30);
        fVar10 = DAT_00d75cc8;
        if ((float10)DAT_00d5e288 <= fVar9) goto LAB_0086a4ef;
        fVar11 = (float)this->ownerPatienceTimer;
        if ((fVar11 < _DAT_00d577a0) || (dt < fVar11)) {
            bVar1 = false;
        } else {
            bVar1 = true;
        }
        if (DAT_00d75cc8 < fVar11) {
            this->ownerPatienceTimer = (int)(fVar11 - dt);
        }
        if ((float)this->ownerPatienceTimer <= fVar10) {
LAB_0086a43a:
            iVar6 = _rand();
            this->ownerPatienceTimer = (int)((float)iVar6 * DAT_00e44590);
            goto LAB_0086a4ef;
        }
        if (!bVar1) goto LAB_0086a4ef;
        if (DAT_0112dfd4 == 0) {
            piVar8 = (int*)0x0;
        } else {
            piVar8 = (int*)(DAT_0112dfd4 + -0x48);
        }
        (**(code**)(*piVar8 + 0x4c))(&local_28);
        (**(code**)(*this + 0x4c))(&local_20);
        if (((0.0f <= local_18 * fStack_24 + local_1c * local_28 + local_14 * local_20) && (local_54 <= local_4c * DAT_00d75750)) || (fVar9 = (float10)FUN_00427180(), (float10)DAT_00d5c454 <= fVar9)) goto LAB_0086a4ef;
    }
    FUN_0087bde0();
LAB_0086a4ef:
    cVar2 = FUN_00868210(dt);
    if (cVar2 != '\0') {
        local_38 = (float)this->ownerWeaponRange; // +0x436
        if (local_38 == 0.0f) {
            local_54 = 0.0f;
        } else {
            local_54 = (float)this->ownerWeaponRange2; // +0x438
        }
        if ((((this->ownerTargetEntity != 0) && (this->ownerTargetEntity != 0x48)) && (DAT_00d5d7b8 <= (float)this->ownerHealthMax - (float)this->ownerHealth)) && (((float)this->ownerHealthMax - (float)this->ownerHealth) - (float)this->ownerDamageReduction * dt <= DAT_00d5d7b8)) {
            FUN_008652d0();
        }
        fVar10 = (float)this->ownerTargetIndex - (float)this->ownerThreatListIndex;
        if (_DAT_00d577a0 < (float)((uint)fVar10 & DAT_00e44680)) {
            fVar15 = DAT_012067e8 * (float)this->ownerAttackCooldown;
            fVar11 = DAT_00e44564 - fVar15;
            if ((fVar11 < fVar10) && (fVar11 = fVar10, fVar15 <= fVar10)) {
                fVar11 = fVar15;
            }
            fVar10 = (float)this->ownerThreatListIndex;
            this->ownerThreatListIndex = (int)(fVar11 + fVar10);
            if (fVar11 + fVar10 == (float)this->ownerTargetIndex) {
                this->ownerAttackCooldown = (int)DAT_00d75764;
            }
        }
        iVar6 = FUN_00600210(dt, 0, 0, 0);
        this->ownerActionState = iVar6;
        if (iVar6 == 0) {
            this->ownerOtherFlags = 0;
            FUN_00868d70(0, 0, 0);
        } else if (iVar6 == 1) {
            local_48 = 2.802597e-45f; // very small, maybe 0
            FUN_005fd860(&local_48, &iStack_3c, &local_4c);
            if (local_4c != local_54) {
                if (((uint)this->ownerFlags >> 10 & 1) != 0) {
                    local_48 = 2.802597e-45f;
                    FUN_005fd860(&local_48, &iStack_40, &iStack_44);
                    if ((iStack_44 != 0) && (iStack_40 != 0)) {
                        cVar2 = FUN_00420950(&this->ownerSomeCounter);
                        if (cVar2 == '\0') {
                            FUN_0083f210(iStack_40 + 0x10);
                        }
                    }
                }
                this->ownerOtherFlags &= 0xffbfffff;
                if ((iStack_3c == 0) || (iVar6 = FUN_0085ec60(iStack_3c), iVar6 == 0)) {
                    this->ownerOtherFlags |= 0x800000;
                } else {
                    this->ownerOtherFlags &= 0xff7fffff;
                }
            }
        } else if (iVar6 == 3) {
            cVar2 = FUN_0087cb30();
            if (cVar2 != '\0') {
                return;
            }
            FUN_004088c0(this + 0xf);
            return;
        }
        piVar8 = &this->ownerActiveEntity; // +0x465
        if (local_50 == 0) {
            iVar6 = 0;
        } else {
            iVar6 = local_50 + 0x48;
        }
        if (*piVar8 != iVar6) {
            if (*piVar8 != 0) {
                FUN_004daf90(piVar8);
            }
            *piVar8 = iVar6;
            if (iVar6 != 0) {
                this->ownerActiveEntityPrev = *(int*)(iVar6 + 4);
                *(int**)(iVar6 + 4) = piVar8;
            }
        }
    }
    return;
}