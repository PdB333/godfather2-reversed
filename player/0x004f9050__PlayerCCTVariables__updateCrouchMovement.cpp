// FUNC_NAME: PlayerCCTVariables::updateCrouchMovement
int* __thiscall PlayerCCTVariables::updateCrouchMovement(int this, float dt)
{
    float *pfVar1;
    int iVar2;
    int iVar3;
    uint *puVar4;
    int *piVar5;
    undefined4 uVar6;
    int *piVar7;
    int *extraout_ECX;
    uint uVar8;
    undefined **ppuVar9;
    int unaff_FS_OFFSET;
    undefined4 uVar10;
    float fVar11;
    undefined **local_38;
    int local_34;
    float local_30;
    float fStack_2c;
    float fStack_28;
    float fStack_24;
    float local_20;
    float local_1c;
    float local_18;
    undefined4 local_14;

    piVar5 = *(int **)(unaff_FS_OFFSET + 0x2c);
    iVar2 = *piVar5;
    // Check if the entity is not already flagged for update (bit 0 of flags at +0x10)
    if ((*(byte *)(*(int *)(this + 0x10) + *(int *)(iVar2 + 8)) & 1) == 0) {
        iVar3 = *(int *)(this + 0x24); // Get some object pointer from this+0x24
        fVar11 = *(float *)(this + 0x28) * *(float *)(this + 0x28); // Square of current speed
        if (*(float *)(iVar3 + 0x20) == 0.0) {
            // If acceleration is zero, set acceleration value to 0
            *(undefined4 *)(this + 0x30) = 0;
        }
        else {
            // Calculate and apply acceleration
            *(float *)(this + 0x30) = fVar11;
            fVar11 = dt * *(float *)(iVar3 + 0x20) + *(float *)(this + 0x28);
            *(float *)(this + 0x28) = fVar11;
            fVar11 = fVar11 * fVar11;
        }
        *(float *)(this + 0x34) = fVar11; // Store squared speed at this+0x34
        fVar11 = *(float *)(iVar3 + 0x1c); // Max speed from the object
        if (fVar11 <= *(float *)(this + 0x28)) {
            // Clamp speed to max
            *(float *)(this + 0x28) = fVar11;
            *(float *)(this + 0x34) = fVar11 * fVar11;
            if ((*(float *)(this + 0x2c) <= 0.0) && (*(float *)(iVar3 + 0x20) != 0.0)) {
                // If time to decelerate (brake timer) has expired and acceleration is not zero, set the flag
                puVar4 = (uint *)(*(int *)(iVar2 + 8) + *(int *)(this + 0x10));
                *puVar4 = *puVar4 | 1;
            }
        }
        ppuVar9 = DAT_012234c4; // Some global pointer
        pfVar1 = (float *)(*(int *)(this + 0x10) + 0x80 + *(int *)(iVar2 + 8));
        local_30 = *pfVar1;           // Position X from transform matrix
        fStack_2c = pfVar1[1];        // Position Y
        fStack_28 = pfVar1[2];        // Position Z
        fStack_24 = pfVar1[3];        // W component (homogeneous)
        piVar5 = (int *)**(undefined4 **)(this + 0x24); // Second level pointer dereference
        local_38 = DAT_012234c4;
        if (((uint)piVar5 & 0x20) == 0) {
            // Bit 0x20 not set - likely not a specific player or vehicle type
            if (((uint)piVar5 & 0x10) == 0) {
                // Bit 0x10 not set - likely a normal NPC not in vehicle
                local_38 = &PTR_LAB_00e37a10; // Some static data pointer
                local_34 = this;
                if (DAT_012234c4[5] != (undefined *)0x0) {
                    piVar5 = (int *)(**(code **)(*(int *)DAT_012234c4[5] + 8))
                                        (&local_30, *(undefined4 *)(this + 0x28), DAT_012234c4[4],
                                         &local_38, 0, 0, 1);
                }
            }
            else {
                // Bit 0x10 set - likely a player or vehicle type
                iVar3 = DAT_012233a0[3]; // Count from some global array
                uVar8 = 0;
                piVar5 = DAT_012233a0;
                if (0 < iVar3) {
                    do {
                        piVar5 = DAT_012233a0;
                        if ((-1 < (int)uVar8) && (uVar8 < (uint)DAT_012233a0[3])) {
                            piVar7 = (int *)((int *)DAT_012233a0[1])[uVar8];
                            piVar5 = (int *)DAT_012233a0[1];
                            if ((piVar7 != (int *)0x0) &&
                               (piVar7 = (int *)(**(code **)(*piVar7 + 0xc))(), piVar5 = piVar7,
                               piVar7 != (int *)0x0)) {
                                // Extract position from the object at +0x100, +0x104, +0x108
                                local_18 = (float)piVar7[0x42]; // Z
                                local_1c = (float)piVar7[0x41]; // Y
                                local_20 = (float)piVar7[0x40]; // X
                                local_14 = DAT_00e2b1a4; // Some constant
                                fVar11 = *(float *)(this + 0x34); // Squared movement radius
                                // Check if object is within movement radius
                                if (((local_18 - fStack_28) * (local_18 - fStack_28) +
                                     (local_1c - fStack_2c) * (local_1c - fStack_2c) +
                                     (local_20 - local_30) * (local_20 - local_30) < fVar11) &&
                                   (piVar5 = (int *)FUN_004f8a20(&local_20), DAT_00e2e210 < fVar11)) {
                                    piVar5 = (int *)FUN_004f8aa0(piVar7, &local_20, fVar11, 0, 0xffffffff);
                                }
                            }
                        }
                        uVar8 = uVar8 + 1;
                        ppuVar9 = local_38;
                    } while ((int)uVar8 < iVar3);
                }
            }
        }
        else {
            // Bit 0x20 set - likely a vehicle or special entity
            piVar7 = *(int **)(*(int *)(this + 4) + 0xc4); // Get some pointer from this+4
            piVar5 = piVar7;
            if ((piVar7 != (int *)0x0) && (piVar5 = piVar7 + -0x12, piVar5 != (int *)0x0)) {
                // Extract position from the object at -0x48 offset
                local_20 = (float)piVar7[0x2e]; // X
                local_1c = (float)piVar7[0x2f]; // Y
                local_18 = (float)piVar7[0x30]; // Z
                local_14 = DAT_00e2b1a4;
                piVar5 = (int *)FUN_004f8aa0(piVar5, &local_20, 0x3f800000, 0,
                                             *(undefined4 *)(*(int *)(this + 4) + 0xb8));
            }
        }
        if ((0.0 < *(float *)(this + 0x2c)) &&
           (dt = *(float *)(this + 0x2c) - dt, *(float *)(this + 0x2c) = dt,
           dt <= 0.0)) {
            // Decrement brake timer and check if expired
            iVar3 = *(int *)(this + 0x10);
            iVar2 = *(int *)(iVar2 + 8);
            puVar4 = (uint *)(iVar3 + iVar2);
            *puVar4 = *puVar4 | 1;
            piVar5 = (int *)(iVar3 + iVar2);
        }
        piVar7 = (int *)ppuVar9[8]; // Some callback or object pointer
        if (piVar7 != (int *)0x0) {
            piVar5 = (int *)(**(code **)(*piVar7 + 4))
                                (&local_30, *(undefined4 *)(*(int *)(this + 0x24) + 0x2c),
                                 *(undefined4 *)(this + 0x28),
                                 *(undefined4 *)(*(int *)(this + 0x24) + 0x28));
            piVar7 = extraout_ECX;
        }
        if (DAT_012233c4 != 0) {
            iVar2 = *(int *)(*(int *)(this + 0x24) + 0x28);
            if (iVar2 == 4) {
                uVar6 = 2;
            }
            else {
                if ((iVar2 != 5) && ((int *)(iVar2 + -8) != (int *)0x0)) {
                    return (int *)(iVar2 + -8);
                }
                uVar6 = 1;
            }
            uVar10 = *(undefined4 *)(this + 0x28);
            fStack_24 = (float)uVar10;
            FUN_004f8980(piVar7, uVar6);
            piVar5 = (int *)FUN_00416340(&local_30, uVar10, uVar6);
        }
    }
    return piVar5;
}