// FUNC_NAME: Vehicle::updateWheelForces
void Vehicle::updateWheelForces(int param_1) // param_1 likely deltaTime or some time step
{
    int *piVar1;
    undefined4 *puVar2;
    int iVar3;
    int iVar4;
    int unaff_ESI; // this pointer
    int iVar5;
    float10 fVar6;
    float fVar7;
    float fVar8;
    float fVar9;
    float fVar10;
    float fVar11;
    float local_30; // wheelForce or acceleration
    int local_2c;
    int local_28;
    float local_20; // x component of some direction
    float local_1c; // y component
    float local_18; // z component
    // +0xbc: some time-related float (e.g., lastUpdateTime)
    fVar7 = DAT_00e44564 - *(float *)(unaff_ESI + 0xbc);
    // +0x110: flags bitfield, bit 1 checked (0x2)
    if ((*(uint *)(unaff_ESI + 0x110) >> 1 & 1) != 0) {
        // +0x4c: number of wheels
        iVar3 = *(int *)(unaff_ESI + 0x4c);
        iVar4 = 0;
        if (0 < iVar3) {
            // +0x48: pointer to wheel array, each wheel entry is 0x30 bytes, +0x24 is some flag
            piVar1 = (int *)(*(int *)(unaff_ESI + 0x48) + 0x24);
            do {
                if (*piVar1 != 0) {
                    iVar4 = iVar4 + 1;
                }
                piVar1 = piVar1 + 0x30;
                iVar3 = iVar3 + -1;
            } while (iVar3 != 0);
            if (iVar4 != 0) goto LAB_0055fb75;
        }
        // +0x18: pointer to rigid body (physics object)
        iVar3 = *(int *)(unaff_ESI + 0x18);
        // Compute velocity magnitude squared
        fVar6 = (float10)FUN_00414a80(*(float *)(iVar3 + 0x1a0) * *(float *)(iVar3 + 0x1a0) +
                                      *(float *)(iVar3 + 0x1a4) * *(float *)(iVar3 + 0x1a4) +
                                      *(float *)(iVar3 + 0x1a8) * *(float *)(iVar3 + 0x1a8));
        local_30 = (float)fVar6;
        // +0xec: some force component (e.g., engineForce)
        fVar10 = *(float *)(unaff_ESI + 0xec) * DAT_00e2b118 + DAT_0113982c;
        // Compute direction vector from constants and vehicle orientation/forces
        local_20 = DAT_01126060 * DAT_00e448d0 +
                   *(float *)(unaff_ESI + 0xe0) * DAT_00e2b118 + DAT_01139820;
        local_1c = DAT_01126064 * DAT_00e448d0 +
                   *(float *)(unaff_ESI + 0xe4) * DAT_00e2b118 + DAT_01139824;
        local_18 = DAT_01126068 * DAT_00e448d0 +
                   *(float *)(unaff_ESI + 0xe8) * DAT_00e2b118 + DAT_01139828;
        fVar11 = DAT_0112606c * DAT_00e448d0;
        fVar9 = local_18 * local_18 + local_1c * local_1c + local_20 * local_20;
        if (fVar9 == 0.0) {
            fVar9 = 0.0;
        }
        else {
            fVar6 = (float10)FUN_00414a80(fVar9);
            fVar9 = (float)((float10)1 / fVar6);
        }
        // Normalize the direction vector
        *(float *)(unaff_ESI + 0xe4) = fVar9 * local_1c;
        *(float *)(unaff_ESI + 0xe0) = fVar9 * local_20;
        *(float *)(unaff_ESI + 0xe8) = fVar9 * local_18;
        *(float *)(unaff_ESI + 0xec) = fVar9 * (fVar11 + fVar10);
        goto LAB_0055fcd0;
    }
LAB_0055fb75:
    // +0x9c: pointer to some component (e.g., wheelComponent)
    iVar3 = *(int *)(unaff_ESI + 0x9c);
    // +0x14: some force value (e.g., brakeForce)
    fVar9 = *(float *)(iVar3 + 0x14);
    // +0x10: boolean flag (e.g., isBraking)
    if (*(char *)(iVar3 + 0x10) != '\0') {
        fVar9 = 0.0;
    }
    iVar4 = *(int *)(unaff_ESI + 0x18);
    // Compute dot product of velocity with some direction (e.g., forward vector)
    fVar10 = *(float *)(iVar4 + 0x1a8) * *(float *)(iVar4 + 0x108) +
             *(float *)(iVar4 + 0x1a4) * *(float *)(iVar4 + 0x104) +
             *(float *)(iVar4 + 0x1a0) * *(float *)(iVar4 + 0x100);
    // Some threshold check (bitwise AND with constant)
    if ((float)((uint)fVar10 & DAT_00e44680) < DAT_00e2e210) {
        fVar10 = 0.0;
    }
    // +0x11: another boolean (e.g., isReversing)
    if (*(char *)(iVar3 + 0x11) != '\0') {
        fVar9 = DAT_00e44564 - fVar9;
    }
    fVar11 = fVar10;
    if (fVar10 <= 0.0) {
        if (fVar10 < 0.0) {
            // +0x18: some force adjustment (e.g., rollingResistance)
            fVar9 = *(float *)(iVar3 + 0x18) + fVar9;
            goto LAB_0055fc12;
        }
    }
    else {
        fVar9 = fVar9 - *(float *)(iVar3 + 0x18);
LAB_0055fc12:
        if (fVar10 < 0.0) {
            fVar11 = 0.0;
        }
    }
    // param_1 + 8: some time step or factor
    fVar8 = *(float *)(param_1 + 8);
    // +0xf8: maxForce, +0xfc: forceScale
    local_30 = ((*(float *)(unaff_ESI + 0xf8) - fVar11) / *(float *)(unaff_ESI + 0xf8)) *
               *(float *)(unaff_ESI + 0xfc) * fVar9 * fVar8 + fVar10;
    // Clamp to zero if sign changes
    if (((local_30 < 0.0) && (0.0 < fVar10)) || ((0.0 < local_30 && (fVar10 < 0.0)))) {
        local_30 = 0.0;
    }
    // If braking, apply anti-lock braking logic
    if (*(char *)(iVar3 + 0x10) != '\0') {
        fVar6 = (float10)FUN_0040f220(local_30); // fabs
        if ((float10)DAT_00e3ac58 <= fVar6) {
            fVar8 = fVar8 * DAT_00e2b04c;
            if (DAT_00e2b1a4 < fVar8) {
                fVar8 = DAT_00e2b1a4;
            }
            local_30 = (DAT_00e2b1a4 - fVar8) * local_30;
        }
        else {
            local_30 = 0.0;
        }
    }
LAB_0055fcd0:
    // +0x1c: pointer to some component (e.g., suspensionComponent)
    iVar3 = *(int *)(unaff_ESI + 0x1c);
    iVar4 = 0;
    // +0x20: number of wheels
    if ('\0' < *(char *)(iVar3 + 0x20)) {
        local_28 = 0;
        local_2c = 0;
        do {
            iVar5 = *(int *)(unaff_ESI + 0x48) + local_2c;
            // +0xa0: pointer to some array of flags per wheel
            if (*(char *)(iVar4 + *(int *)(unaff_ESI + 0xa0)) == '\0') {
                // Copy orientation from rigid body to suspension
                FUN_00aa2cd0(*(int *)(unaff_ESI + 0x18) + 0xe0, iVar3 + 0x40);
                iVar3 = *(int *)(unaff_ESI + 0x18);
                // Compute wheel force based on velocity and suspension
                fVar9 = (*(float *)(iVar3 + 0x1a4) * local_1c + *(float *)(iVar3 + 0x1a8) * local_18 +
                         *(float *)(iVar3 + 0x1a0) * local_20 + *(float *)(iVar5 + 0xb0)) /
                        *(float *)(*(int *)(*(int *)(unaff_ESI + 0x1c) + 0x8c) + local_28);
                // +0xa0: wheelForce, +0xa4: wheelForceAccumulator
                *(float *)(iVar5 + 0xa0) = fVar9;
                *(float *)(iVar5 + 0xa4) = *(float *)(param_1 + 8) * fVar9 + *(float *)(iVar5 + 0xa4);
            }
            else {
                *(undefined4 *)(iVar5 + 0xa0) = 0;
            }
            iVar3 = *(int *)(unaff_ESI + 0x1c);
            local_2c = local_2c + 0xc0; // each wheel entry size
            local_28 = local_28 + 0x28; // some other array stride
            iVar4 = iVar4 + 1;
        } while (iVar4 < *(char *)(iVar3 + 0x20));
    }
    // +0xf4: minForce, +0xf0: maxForce
    fVar9 = DAT_00e44564 - *(float *)(unaff_ESI + 0xf4);
    if ((local_30 < fVar9) || (fVar9 = *(float *)(unaff_ESI + 0xf0), fVar9 < local_30)) {
        local_30 = fVar9;
    }
    // Call another function to apply forces
    FUN_0055fe80(unaff_ESI, param_1, local_30, fVar7);
    // Clear some arrays (likely wheel contact data)
    iVar3 = 0;
    if (0 < *(int *)(*(int *)(unaff_ESI + 0x1c) + 0x9c)) {
        puVar2 = (undefined4 *)(unaff_ESI + 0x5c);
        do {
            puVar2[-2] = 0;
            puVar2[-1] = 0;
            *puVar2 = 0;
            puVar2[1] = 0;
            puVar2[2] = 0;
            puVar2[3] = 0;
            puVar2[4] = 0;
            puVar2[5] = 0;
            puVar2[6] = 0;
            iVar3 = iVar3 + 1;
            puVar2 = puVar2 + 9;
        } while (iVar3 < *(int *)(*(int *)(unaff_ESI + 0x1c) + 0x9c));
    }
    return;
}