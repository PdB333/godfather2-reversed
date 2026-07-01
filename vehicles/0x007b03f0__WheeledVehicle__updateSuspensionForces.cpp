// FUNC_NAME: WheeledVehicle::updateSuspensionForces

void __thiscall WheeledVehicle::updateSuspensionForces(void* thisPtr, uint param2, float deltaTime, uint param4, uint param5, uint param6)
{
    bool bVar1;
    float fVar2;
    char cVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    float fVar8;
    float local_8;
    float local_4;

    cVar3 = FUN_00410eb0(); // Check if vehicle is active/valid
    if (cVar3 == '\0') {
        // Reset all suspension state
        *(undefined4 *)(thisPtr + 0x1e4) = 0; // +0x1e4: suspensionTimer
        *(undefined4 *)(thisPtr + 0x1e8) = 0; // +0x1e8: suspensionCooldown
        goto LAB_007b0667;
    } else {
        fVar8 = DAT_00d5ef84; // Default suspension force constant
        if (-1 < *(short *)(thisPtr + 0x184)) { // +0x184: wheelIndex (short)
            fVar8 = *(float *)(thisPtr + 0x1e4) - deltaTime; // Decrease timer
        }
        *(float *)(thisPtr + 0x1e4) = fVar8; // Update suspensionTimer

        if ((*(uint *)(*(int *)(thisPtr + 0x58) + 0x8e4) >> 0x1a & 1) == 0) { // Check bit 26 of some flag
            *(float *)(thisPtr + 0x1e8) = *(float *)(thisPtr + 0x1e8) - deltaTime; // Decrease cooldown
        } else {
            *(float *)(thisPtr + 0x1e8) = DAT_00d5c454; // Reset cooldown to max
        }
        if (0.0 < *(float *)(thisPtr + 0x1e8)) goto LAB_007b0667; // If cooldown still active, skip

        // Get random force components
        FUN_0079eab0(1, &local_8, &local_4, 0, 0, DAT_00d5ccf8, DAT_00d5ccf8, DAT_00d5ccf8);
        fVar2 = DAT_00d5f374; // Max suspension travel time
        fVar8 = *(float *)(thisPtr + 0x1d4) + deltaTime; // +0x1d4: suspensionTravelTime
        bVar1 = fVar8 < DAT_00d5f374;
        local_8 = *(float *)(thisPtr + 0x1cc) + local_8; // +0x1cc: suspensionForceX
        local_4 = *(float *)(thisPtr + 0x1d0) + local_4; // +0x1d0: suspensionForceY
        *(float *)(thisPtr + 0x1d4) = fVar8; // Update travel time
        *(float *)(thisPtr + 0x1cc) = local_8; // Update force X
        *(float *)(thisPtr + 0x1d0) = local_4; // Update force Y
        fVar4 = DAT_00d5ccf8; // Zero constant
        if (bVar1) goto LAB_007b06a7; // If travel time not exceeded, skip damping

        // Apply damping and clamp forces
        local_8 = local_8 * DAT_00d5842c; // Damping factor
        local_4 = local_4 * DAT_00d5842c;
        fVar5 = local_8 + *(float *)(thisPtr + 0x1c4); // +0x1c4: accumulatedForceX
        *(undefined4 *)(thisPtr + 0x1cc) = 0; // Reset force X
        *(undefined4 *)(thisPtr + 0x1d0) = 0; // Reset force Y
        fVar6 = fVar4;
        if ((fVar4 <= fVar5) && (fVar6 = fVar5, _DAT_00d5780c < fVar5)) {
            fVar6 = _DAT_00d5780c; // Clamp to max
        }
        fVar7 = *(float *)(thisPtr + 0x1c8) + local_4; // +0x1c8: accumulatedForceY
        *(float *)(thisPtr + 0x1c4) = fVar6; // Update accumulated X
        fVar5 = DAT_00d6bfd8; // Threshold for force magnitude squared
        if ((fVar4 <= fVar7) && (fVar4 = _DAT_00d5780c, fVar7 <= _DAT_00d5780c)) {
            fVar4 = fVar7; // Clamp to max
        }
        local_8 = (fVar2 / fVar8) * local_8; // Scale by travel time ratio
        local_4 = (fVar2 / fVar8) * local_4;
        local_4 = local_4 * local_4; // Square Y component
        *(float *)(thisPtr + 0x1c8) = fVar4; // Update accumulated Y

        if ((fVar5 <= local_4) || (DAT_00d5f378 <= fVar4)) { // Check if force magnitude too high or accumulated Y too high
            *(undefined4 *)(thisPtr + 0x1d8) = 0; // +0x1d8: suspensionBounceTimer
        } else {
            *(float *)(thisPtr + 0x1d8) = *(float *)(thisPtr + 0x1d8) + fVar8; // Increase bounce timer
        }
        fVar2 = DAT_00e44828; // Another threshold
        if ((local_4 <= fVar5) || (DAT_00e44828 < fVar4)) {
            fVar4 = *(float *)(thisPtr + 0x1e0) - fVar8; // +0x1e0: suspensionCompression
            if (fVar4 < 0.0) {
                fVar4 = 0.0;
            }
        } else {
            fVar4 = fVar8 + *(float *)(thisPtr + 0x1e0); // Increase compression
        }
        *(float *)(thisPtr + 0x1e0) = fVar4; // Update compression

        if ((local_8 * local_8 <= fVar5) || ((fVar2 < fVar6 && (fVar6 < DAT_00d5c454)))) {
            fVar8 = *(float *)(thisPtr + 0x1dc) - fVar8; // +0x1dc: suspensionRebound
            if (fVar8 < 0.0) {
                fVar8 = 0.0;
            }
            *(undefined4 *)(thisPtr + 0x1d4) = 0; // Reset travel time
        } else {
            fVar8 = *(float *)(thisPtr + 0x1dc) + fVar8; // Increase rebound
            *(undefined4 *)(thisPtr + 0x1d4) = 0; // Reset travel time
        }
    }
    *(float *)(thisPtr + 0x1dc) = fVar8; // Update rebound

LAB_007b06a7:
    FUN_004aba80(param2, deltaTime, param4, param5, param6); // Call base class update
    return;
}