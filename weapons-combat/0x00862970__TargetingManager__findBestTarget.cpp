// FUNC_NAME: TargetingManager::findBestTarget
bool __thiscall TargetingManager::findBestTarget(
    TargetingManager *this,
    Vector3 *sourcePos,
    float sourceRadius,
    Vector3 *targetPos,
    float targetRadius,
    float *outBestDistance,
    Entity **outBestEntity,
    float *outBestAngle,
    float *outBestDist2,
    char unknownFlag
)
{
    char bVar1;
    int *piVar2;
    undefined8 *puVar3;
    char *pcVar4;
    int iVar5;
    int *piVar6;
    int iVar7;
    float *pfVar8;
    bool result;
    float10 fVar10;
    float fVar11;
    float fVar12;
    double dVar13;
    char local_e1;
    float fStack_e0;
    float fStack_dc;
    float fStack_d8;
    float fStack_d4;
    float *pfStack_d0;
    float fStack_cc;
    undefined8 local_c8;
    float local_c0;
    float fStack_bc;
    float *local_b8;
    float local_b4;
    float fStack_b0;
    undefined8 uStack_ac;
    float fStack_a4;
    undefined8 local_a0;
    float local_98;
    float fStack_90;
    float fStack_8c;
    float fStack_88;
    int *piStack_84;
    float fStack_80;
    float fStack_7c;
    float fStack_78;
    float fStack_74;
    int *local_70;
    float fStack_6c;
    float fStack_68;
    float fStack_64;
    int local_60;
    float fStack_5c;
    float fStack_58;
    float fStack_54;
    float fStack_50;
    float local_4c;
    float local_48;
    float local_44;
    float fStack_40;
    undefined1 auStack_3c [4];
    float fStack_38;
    float fStack_34;
    float fStack_30;
    float fStack_2c;
    undefined1 auStack_28 [12];
    undefined1 auStack_1c [24];

    // Check if targeting is disabled (bit 0xB of field 0x3CA)
    if (((uint)this->fields[0x3ca] >> 0xb & 1) == 0) {
        // If already targeting something, clear the flag
        if (((uint)this->fields[0x3ca] >> 0x16 & 1) != 0) {
            this->fields[0x3ca] = this->fields[0x3ca] & 0xffbfffff;
        }

        // Get target list info - field 0x3E5 points to some target list structure
        local_60 = *(int *)(this->fields[0x3e5] + 0xc4); // +0xC4 = target count
        local_70 = (int *)(this->fields[0x3e5] + 0xc0); // +0xC0 = target array pointer

        // Skip if no targets or if the only target is ourselves
        if ((0 < local_60) &&
           ((local_60 != 1 ||
            (piVar2 = (int *)FUN_004afca0(*(undefined4 *)*local_70), piVar2 != this)))) {

            // Get character's current position and orientation
            FUN_008750c0(&local_4c);
            local_c0 = *(float *)(targetPos + 1);
            local_c8 = *targetPos; // Note: this assignment seems wrong, should be sourcePos?
            // Actually looking at the code, it reads from param_2 (targetPos) but then modifies it
            // This is likely a bug in the decompilation, but we'll preserve it

            // Get character's transform
            puVar3 = (undefined8 *)FUN_00471610();
            local_a0 = *puVar3;
            local_98 = *(float *)(puVar3 + 1);

            // Check some flag - possibly first person mode?
            pcVar4 = (char *)FUN_00549a40(&local_e1);
            if (*pcVar4 == '\0') {
                // Scale by global constant (likely field of view or sensitivity)
                local_a0 = CONCAT44(local_a0._4_4_ * DAT_00d5ccf8, (float)(int *)local_a0 * DAT_00d5ccf8);
                local_98 = local_98 * DAT_00d5ccf8;
                local_b8 = (float *)this->fields[1000]; // +0xFA0 = entity pointer?
            }
            else {
                local_b8 = (float *)this->fields[0x3e9]; // +0xFA4 = alternative entity pointer
            }

            // Calculate position delta
            local_b4 = (float)this->fields[0x3f0]; // +0xFC0 = character radius
            fVar11 = (float)local_b8 - local_b4;
            local_c8 = CONCAT44(local_48 * fVar11 + local_c8._4_4_, local_4c * fVar11 + (float)local_c8);
            local_c0 = local_44 * fVar11 + local_c0;

            // Get max targeting distance
            fVar10 = (float10)(**(code **)(*this + 0x1b0))(); // this->getMaxTargetDist()
            fStack_dc = (float)fVar10;
            if (fVar10 < (float10)DAT_00d75858) {
                fStack_dc = DAT_00d75858; // Minimum distance clamp
            }

            // Get angular speed (aim speed)
            if (((uint)this->fields[0x322] >> 7 & 1) == 0) {
                fStack_d4 = DAT_00d68260; // Default angular speed
            }
            else {
                fVar10 = (float10)(**(code **)(*this + 0x2cc))(); // this->getAngularSpeed()
                fStack_d4 = (float)fVar10;
            }

            // Check if angle difference is very small (already looking at target)
            if ((float)((uint)(sourceRadius - targetRadius) & DAT_00e44680) < _DAT_00d75898) {
                dVar13 = (double)sourceRadius;
                FUN_00b99fcb();
                fStack_58 = (float)dVar13;
                dVar13 = (double)sourceRadius;
                FUN_00b99e20();
            }
            else {
                // Calculate turn rate factor
                fStack_d8 = _DAT_00d5780c;
                if (fStack_dc < fStack_d4) {
                    fStack_d8 = fStack_dc / fStack_d4;
                }

                // Get target position relative to character
                fStack_a4 = *(float *)(targetPos + 1);
                uStack_ac = *targetPos;
                FUN_00601970(targetRadius, &fStack_90);
                uStack_ac = CONCAT44(fStack_8c * fStack_dc + uStack_ac._4_4_,
                                     fStack_90 * fStack_dc + (float)uStack_ac);
                fStack_a4 = fStack_88 * fStack_dc + fStack_a4;

                // Calculate angle between current facing and target direction
                fVar10 = (float10)FUN_004a0cd0(&local_c8, &local_4c, &uStack_ac, &DAT_00d75690);
                pfStack_d0 = (float *)(float)fVar10;
                fStack_bc = sourceRadius - (float)pfStack_d0 * fStack_d8;

                // Normalize angle to [-PI, PI]
                if (fStack_bc <= DAT_00d5eeec) {
                    if (fStack_bc < DAT_00e44588) {
                        fStack_bc = fStack_bc + DAT_00d5d70c;
                    }
                }
                else {
                    fStack_bc = fStack_bc - DAT_00d5d70c;
                }

                dVar13 = (double)fStack_bc;
                FUN_00b99fcb();
                fStack_58 = (float)dVar13;
                dVar13 = (double)fStack_bc;
                FUN_00b99e20();

                // Apply turn rate
                fVar11 = DAT_00e44718;
                if (0.0 < (float)pfStack_d0) {
                    fVar11 = _DAT_00d5c458;
                }
                fVar11 = fStack_d8 * fVar11;
                local_b4 = fStack_d8 * DAT_00d61fe8 + local_b4;
                local_c8 = CONCAT44(local_a0._4_4_ * fVar11 + local_c8._4_4_,
                                    (float)(int *)local_a0 * fVar11 + (float)local_c8);
                local_c0 = local_98 * fVar11 + local_c0;
            }

            // Calculate movement vector
            fStack_58 = fStack_58 * fStack_dc;
            fStack_54 = fStack_dc * 0.0;
            fStack_50 = (float)dVar13 * fStack_dc;
            fStack_dc = 0.0;
            fStack_5c = 0.0;

            // Handle movement-based targeting (if character has moved > 0)
            if ((1 < this->fields[0x3cc]) && // +0xF30 = current target index
               (fStack_dc = (float)this->fields[0x445] - (float)this->fields[0x444], 0.0 < fStack_dc)) {
                FUN_00875190(&fStack_90, 0);
                FUN_0085ecf0(&fStack_6c);
                fStack_dc = SQRT((fStack_88 - fStack_64) * (fStack_88 - fStack_64) +
                                 (fStack_8c - fStack_68) * (fStack_8c - fStack_68) +
                                 (fStack_90 - fStack_6c) * (fStack_90 - fStack_6c)) + fStack_dc;

                fStack_e0 = 2.8026e-45;
                bVar1 = FUN_005fd8a0(&fStack_e0, &pfStack_d0);
                pfVar8 = pfStack_d0;
                if (bVar1 != '\0') {
                    FUN_0085ea30(this->fields[0x453], this->fields[0x3f1]);
                    fStack_e0 = 4.2039e-45;
                    bVar1 = FUN_005fd8a0(&fStack_e0, &pfStack_d0);
                    if (bVar1 != '\0') {
                        fStack_80 = *pfStack_d0 - *pfVar8;
                        fStack_7c = pfStack_d0[1] - pfVar8[1];
                        fStack_78 = pfStack_d0[2] - pfVar8[2];
                        FUN_0043a210(&fStack_80, &fStack_80);
                        fStack_80 = fStack_80 * fStack_d4;
                        fStack_7c = fStack_7c * fStack_d4;
                        fStack_78 = fStack_78 * fStack_d4;
                        fVar10 = (float10)(**(code **)(*this + 0x1b0))(); // this->getMaxTargetDist()
                        fVar10 = (float10)fStack_dc / ((fVar10 + (float10)fStack_d4) * (float10)_DAT_00d5c458);
                        fStack_5c = (float)fVar10;
                        if ((float10)0 < fVar10) goto LAB_00862f47;
                    }
                }
                this->fields[0x3cc] = 0; // Reset target index
            }

LAB_00862f47:
            fStack_e0 = (float)local_b8 * DAT_00d75750;
            fStack_38 = fStack_e0;
            fVar10 = (float10)(**(code **)(*this + 0x1b8))(); // this->getWeaponRange()
            fStack_d4 = (float)((float10)(float)local_b8 * (float10)_DAT_00d75758 +
                               fVar10 * (float10)_DAT_00d63484);

            // Adjust range based on line of sight
            FUN_0085ecf0(auStack_28);
            fVar10 = (float10)FUN_004a0b00(&local_c8, &local_4c, auStack_28, &DAT_00d75690);
            if (fVar10 < (float10)_DAT_00d75894) {
                fStack_d4 = fStack_d4 * _DAT_00d5c458;
            }
            if (fStack_d4 < fStack_e0) {
                fStack_d4 = fStack_e0;
            }

            // Iterate through all targets
            piStack_84 = (int *)0x0;
            fStack_74 = 0.0;
            pfStack_d0 = (float *)0x0;
            fStack_d8 = 0.0;
            fStack_bc = fStack_d4;
            if (0 < local_60) {
                do {
                    iVar5 = *(int *)((int)fStack_d8 * 4 + *local_70); // Get target entity pointer
                    if ((iVar5 != 0) && (*(char *)(iVar5 + 0x10) + iVar5 != 0)) {
                        // Check if this is a valid target
                        FUN_004af8c0(&local_a0, 0x2001);
                        piVar2 = (int *)0x0;
                        if ((int *)local_a0 != (int *)0x0) {
                            piVar2 = (int *)local_a0;
                        }

                        // Validate target: exists, not self, not dead, not immune
                        if (((((piVar2 != (int *)0x0) && (piVar2 != this)) &&
                             (iVar5 = FUN_00541470(*(undefined4 *)(iVar5 + 0x1c)), iVar5 != 1)) &&
                            (-1 < *(char *)((int)piVar2 + 0x15e))) &&
                           (((fStack_d8 == 0.0 ||
                             (piVar6 = (int *)FUN_004afca0(*(undefined4 *)(*local_70 + -4 + (int)fStack_d8 * 4))
                             , piVar2 != piVar6)) && (bVar1 = FUN_00543070(piVar2), bVar1 == '\0')))) {

                            // Check if target is the player (local player check)
                            if (**(int **)(DAT_012233a0 + 4) == 0) {
                                piVar6 = (int *)0x0;
                            }
                            else {
                                piVar6 = (int *)(**(int **)(DAT_012233a0 + 4) + -0x1f30);
                            }

                            if (((piVar2 != piVar6) || (piVar6 == (int *)0x0)) ||
                               (bVar1 = FUN_007f7c60(), bVar1 == '\0')) {
                                // Calculate distance to target
                                fVar10 = (float10)FUN_00470250(sourcePos);
                                fStack_cc = (float)fVar10;

                                // Check range and type validity
                                if (((unknownFlag == '\0') || ((float)this->fields[0x3f0] <= fStack_cc)) &&
                                   ((iVar5 = FUN_006b1c70(piVar2, 0x55859efa), iVar5 != 0 ||
                                    (iVar5 = FUN_006c12d0(piVar2, 0xa5975eb2), iVar5 != 0)))) {

                                    // Calculate angle to target
                                    iVar5 = FUN_00471610();
                                    fVar10 = (float10)FUN_004a0cd0(&local_c8, &local_4c, iVar5 + 0x30, &DAT_00d75690);
                                    fStack_e0 = (float)fVar10;
                                    fVar11 = DAT_00d75890;
                                    if (fStack_38 < fStack_cc) {
                                        fVar11 = DAT_00d75890 - (fStack_cc / fStack_d4) * _DAT_00d7588c;
                                    }

                                    fStack_40 = (float)((uint)fStack_e0 & DAT_00e44680);
                                    if (fStack_40 < fVar11) {
                                        // Check if target has special behavior flag
                                        iVar5 = FUN_006c12a0(piVar2, 0x10e5319e);
                                        if (iVar5 == 0) {
                                            // Get target position via function
                                            local_e1 = FUN_0085ee60(piVar2, *(undefined4 *)(*local_70 + (int)fStack_d8 * 4),
                                                                    &fStack_b0, &fStack_6c, &fStack_90);
                                        }
                                        else {
                                            // Get target position directly
                                            FUN_00860260(&fStack_6c, &fStack_90, &fStack_b0);
                                            fStack_cc = fStack_cc - DAT_00d5ef70;
                                            local_e1 = '\x01';
                                            if (fStack_cc < 0.0) {
                                                fStack_cc = 0.0;
                                            }
                                        }

                                        // Calculate distance from character to target
                                        fVar11 = SQRT((fStack_64 - local_c0) * (fStack_64 - local_c0) +
                                                      (fStack_68 - local_c8._4_4_) * (fStack_68 - local_c8._4_4_) +
                                                      (fStack_6c - (float)local_c8) * (fStack_6c - (float)local_c8));

                                        // If we have two positions, use the closer one
                                        if ((local_e1 != '\0') &&
                                           (fVar12 = SQRT((fStack_88 - local_c0) * (fStack_88 - local_c0) +
                                                          (fStack_8c - local_c8._4_4_) * (fStack_8c - local_c8._4_4_) +
                                                          (fStack_90 - (float)local_c8) * (fStack_90 - (float)local_c8))
                                           , fVar12 < fVar11)) {
                                            fVar11 = fVar12;
                                        }

                                        // Check if target is within range and angle
                                        if ((fStack_b0 + local_b4 + _DAT_00d5780c < fVar11) ||
                                           (DAT_00e447d4 <= fStack_40)) {
                                            // Get target's velocity
                                            (**(code **)(*piVar2 + 0x4c))(&uStack_ac);

                                            // Handle auto-aim adjustment for moving targets
                                            if ((1 < this->fields[0x3cc]) &&
                                               (((((uint)this->fields[0x3ca] >> 0x16 & 1) == 0 && (fStack_dc < DAT_00d5d934))
                                                && (_DAT_00d577a0 < fStack_dc)))) {
                                                iVar7 = FUN_00471610();
                                                fStack_34 = (float)uStack_ac * fStack_5c + *(float *)(iVar7 + 0x30);
                                                fStack_30 = uStack_ac._4_4_ * fStack_5c + *(float *)(iVar7 + 0x34);
                                                fStack_2c = fStack_a4 * fStack_5c + *(float *)(iVar7 + 0x38);
                                                bVar1 = FUN_0084c940(auStack_1c, &fStack_34, &fStack_80, &uStack_ac,
                                                                     local_b4 + DAT_00d58cbc, DAT_00d757b8, &local_b8);
                                                if (bVar1 != '\0') {
                                                    this->fields[0x3ca] = this->fields[0x3ca] | 0x400000; // Set auto-aim flag
                                                }
                                            }

                                            // Check if this target is better (closer) than current best
                                            if ((fStack_cc <= fStack_bc) &&
                                               ((iVar5 == 0 ||
                                                (bVar1 = FUN_00860aa0(iVar5, fStack_cc, &fStack_e0), bVar1 != '\0')))) {
                                                if (local_e1 == '\0') {
                                                    // Check line of sight to target
                                                    iVar5 = FUN_00471610();
                                                    fVar11 = local_b4 + DAT_00d5ef90;
                                                    pfVar8 = (float *)(iVar5 + 0x30);
LAB_0086352e:
                                                    bVar1 = FUN_0084c940(&local_c8, pfVar8, &fStack_58, &uStack_ac, fVar11,
                                                                         fStack_b0, &local_b8);
                                                    if (bVar1 == '\0') goto LAB_008635a9;
                                                }
                                                else {
                                                    fStack_e0 = local_b4 + DAT_00d5ef90;
                                                    bVar1 = FUN_0084c940(&local_c8, &fStack_6c, &fStack_58, &uStack_ac, fStack_e0,
                                                                         fStack_b0, &local_b8);
                                                    if (bVar1 == '\0') {
                                                        pfVar8 = &fStack_90;
                                                        fVar11 = fStack_e0;
                                                        goto LAB_0086352e;
                                                    }
                                                }

                                                // Check if target can be targeted (special abilities check)
                                                bVar1 = (**(code **)(*piVar2 + 0x10))(0x55859efa, auStack_3c);
                                                if ((bVar1 == '\0') ||
                                                   ((bVar1 = FUN_00690150(0x36), bVar1 == '\0' &&
                                                    ((((uint)this->fields[0x3ca] >> 0xe & 1) == 0 ||
                                                     (((uint)this->fields[0x322] >> 0x15 & 1) != 0)))))) {
                                                    // This target is valid and better - store it
                                                    pfStack_d0 = local_b8;
                                                    fStack_bc = fStack_cc;
                                                    piStack_84 = piVar2;
                                                    fStack_74 = fStack_b0;
                                                }
                                            }
                                        }
                                        else {
                                            // Target is valid but not within distance/angle - still store as fallback
                                            pfStack_d0 = (float *)0x0;
                                            fStack_bc = fStack_cc;
                                            piStack_84 = piVar2;
                                            fStack_74 = fStack_b0;
                                        }
                                    }
                                }
                            }
                        }
                    }
LAB_008635a9:
                    fStack_d8 = (float)((int)fStack_d8 + 1);
                } while ((int)fStack_d8 < local_60);
            }

            // Store output values
            result = piStack_84 != (int *)0x0;
            if (result) {
                *outBestDistance = fStack_bc;
            }
            if (outBestEntity != (undefined4 *)0x0) {
                *outBestEntity = piStack_84;
            }
            if (outBestAngle != (float *)0x0) {
                *outBestAngle = fStack_74;
            }
            if (outBestDist2 == (float *)0x0) {
                return result;
            }
            *outBestDist2 = (float)pfStack_d0;
            return result;
        }
    }
    return false;
}