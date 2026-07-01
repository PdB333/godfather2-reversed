// FUNC_NAME: SteerController::computeSteering
int SteerController::computeSteering(SteerInput* pDesired, SteerInput* pCurrent)
{
    float* fVar1;
    char cVar2;
    byte bVar3;
    int iVar4;
    int iVar5;
    undefined8* puVar6;
    int iVar7;
    undefined4 uVar8;
    float10 fVar9;
    float fVar10;
    double dVar11;
    undefined8* local_40;
    float* local_3c;
    undefined4 local_38;
    float local_34;
    float local_30;
    int local_2c;
    int local_28;
    undefined4 local_24;
    undefined4 local_20;
    undefined8 local_1c;
    undefined4 local_14;

    // Check current steering mode (0x4c)
    if ((m_steeringMode == 0) || (m_steeringMode == 0x48)) {
        iVar4 = updateSteeringDefault(this, pDesired, pCurrent);
    } else {
        iVar4 = updateSteeringAlternate(this);
    }

    // Validate input pointers and target entity
    if (((((-1 < iVar4) && (iVar7 = m_pTarget != 0)) && 
          (local_28 = pDesired->id != 0)) &&
         ((fVar1 = pDesired->pHeading != nullptr && (local_2c = pCurrent->id != 0)))) && 
        (local_3c = pCurrent->pHeading != nullptr)) {

        iVar5 = isPlayerControlled(local_28); // FUN_0085ec60
        local_24 = 0;
        local_20 = 0;

        if (iVar5 == 0) {
            // AI-controlled?
            iVar5 = getVehicleFromHeading(fVar1, pCurrent); // FUN_005f5f20
            if (iVar5 != 0) {
                cVar2 = checkHash(*(uint16*)(iVar5 + 8), 0xc2e43267, &local_24); // e.g., isPlayer
                if (((cVar2 != '\0') && (cVar2 = isGameStateValid(&local_40)) != '\0') &&
                    ((local_40 != NULL && ((m_pTarget->flags & 0x802) == 0)))) {
                    return -0x7f; // Invalid state
                }

                cVar2 = checkHash(*(uint16*)(iVar5 + 8), 0xf7276be5, &local_24); // e.g., isInVehicle
                if (((cVar2 != '\0') && (cVar2 = isGameStateValid(&local_40)) != '\0') &&
                    (local_40 != NULL && ((m_pTarget->flags >> 0xb & 1) != 0))) {
                    // Check global player pointer
                    if (**(int**)(DAT_012233a0 + 4) == 0) {
                        iVar4 = 0;
                    } else {
                        iVar4 = **(int**)(DAT_012233a0 + 4) + -0x1f30;
                    }
                    if ((m_pTarget->someMask >> 4 & 1) == 0) {
                        return -0x7f;
                    }
                    if (iVar4 == 0) {
                        return -0x7f;
                    }
                    if ((~*(byte*)(DAT_0112af68 + 0x170) & 1) == 0) {
                        return -0x7f;
                    }
                    iVar4 = 0;
                }
            }
        } else {
            // Player-controlled?
            cVar2 = checkHash(*(uint16*)(iVar5 + 8), 0xc2e43267, &local_24);
            if (((cVar2 != '\0') && (cVar2 = isGameStateValid(&local_40)) != '\0') &&
                ((local_40 != NULL && ((m_pTarget->flags & 0x802) == 0)))) {
                return -0x7f;
            }

            cVar2 = checkHash(*(uint16*)(iVar5 + 8), 0xf7276be5, &local_24);
            if (((cVar2 != '\0') && (cVar2 = isGameStateValid(&local_40)) != '\0') &&
                ((local_40 != NULL && ((m_pTarget->flags >> 0xb & 1) != 0)))) {
                if (**(int**)(DAT_012233a0 + 4) == 0) {
                    iVar4 = 0;
                } else {
                    iVar4 = **(int**)(DAT_012233a0 + 4) + -0x1f30;
                }
                if ((m_pTarget->someMask >> 4 & 1) == 0) {
                    return -0x7f;
                }
                if (iVar4 == 0) {
                    return -0x7f;
                }
                if ((~*(byte*)(DAT_0112af68 + 0x170) & 1) == 0) {
                    return -0x7f;
                }
                iVar4 = 0;
            }
        }

        // Compute heading difference
        dVar11 = (double)(*local_3c - *fVar1);
        addNoise(); // FUN_00b9a9fa
        local_38 = 0;
        local_40 = NULL;
        local_30 = (float)dVar11;
        local_34 = 1.4013e-45f;
        normalizeAngle(&local_34, &local_38, &local_40); // FUN_005fd860

        // Get current heading reference
        if (local_40 == NULL) {
            iVar5 = getGameManager(); // FUN_00471610
            local_14 = *(undefined4*)(iVar5 + 0x38);
            puVar6 = (undefined8*)(iVar5 + 0x30);
        } else {
            local_14 = *(undefined4*)(local_40 + 1);
            puVar6 = local_40;
        }
        local_1c = *puVar6; // reference heading

        dVar11 = (double)(*fVar1 - (float)local_1c);
        addNoise(); // FUN_00b9a9fa
        fVar10 = (float)dVar11 - local_30;
        if (fVar10 <= DAT_00d5eeec) {
            if (fVar10 < DAT_00e44588) {
                fVar10 = fVar10 + DAT_00d5d70c; // wrap around
            }
        } else {
            fVar10 = fVar10 - DAT_00d5d70c;
        }

        // Angle difference too large to correct?
        if (_DAT_00d757e4 <= (float)((uint)fVar10 & DAT_00e44680)) {
            return -0x7f;
        }

        // Check steering mode (0xbc)
        if ((m_steeringMode2 == 0) ||
            ((m_steeringMode2 == 2 && (m_steeringMode == 0 || m_steeringMode == 0x48)))) {

            if (1 < (m_pTarget->vehicleState & 0x7fffffff)) {
                iVar4 = computeSteeringAlternative(this, pDesired, pCurrent); // FUN_00864100
                return iVar4;
            }

            if (fVar10 < DAT_00d69acc) {
                return 0; // No steering needed
            }

            if (DAT_00e447a4 < fVar10) {
                iVar4 = iVar4 >> 2; // Reduce correction
            }

            applySteeringFilter(); // FUN_00863c20
            fVar10 = fVar10 * _DAT_00d75cb8;

            // Apply speed-dependent multiplier if player is in vehicle
            if ((**(int**)(DAT_012233a0 + 4) != 0) && (**(int**)(DAT_012233a0 + 4) != 0x1f30)) {
                iVar7 = getGameManager(); // FUN_00471610
                fVar9 = (float10)getPlayerSpeed(iVar7 + 0x30); // FUN_00470250
                local_30 = (float)fVar9;
                fVar10 = local_30;
                if (fVar9 < (float10)DAT_00d5d7b8) {
                    fVar10 = DAT_00d5d7b8; // Minimum speed factor
                }
                fVar10 = fVar10 * local_34 * DAT_00d5ef84;
            }

            uVar8 = getFrameTime(); // FUN_00860800
            bVar3 = applySteeringSmoothing(local_28, fVar1, local_2c, local_3c, uVar8); // FUN_00867760
            iVar4 = iVar4 + (int)fVar10 >> (bVar3 & 0x1f);

            // Clamp final steering value
            if (iVar4 < 1) {
                return 1;
            }
            if (0x7f < iVar4) {
                iVar4 = 0x7f;
            }
        }
    }
    return iVar4;
}