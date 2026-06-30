// FUNC_NAME: PhysicsComponent::simulateForces
// Function address: 0x004ece90
// This function applies forces and integrates physics for an object.
// It uses a constraint solver (FUN_0048a3b0) and may trigger haptic feedback.

void __fastcall PhysicsComponent::simulateForces(int component)
{
    float fVar1;
    byte bVar2;
    short uVar4;
    int iVar5;
    int iVar8;
    float *pfVar10;
    uint uVar11;
    float fVar12, fVar13, fVar14, fVar15, fVar16, fVar17, fVar18;
    float local_70;
    int local_6c; // direction/type flags
    int local_64;
    float *local_58;
    uint local_54;
    float local_44, local_40, local_3c;
    float savedPos[4]; // for restoring position

    iVar8 = *(_DAT_012234a0); // global engine pointer
    if (*(int *)(component + 0x20) == 0) {
        *(int *)(component + 0x20) = 0;
        return;
    }
    // Call into sub-system with data from component+0x24
    FUN_00488a10(*(int *)(*(int *)(component + 0x24) + 4));
    float timeDelta = *(float *)0x00e2b1a4; // frame time
    *(_DAT_01205504) = component; // store current component globally

    // Check and initialize vtable for owner (base object)
    int owner = *(_ECX); // ECX register (this for the owning class)
    if (*(int *)(owner + 0x54) != (int)&LAB_004ee6c0) {
        *(int *)(owner + 0x54) = (int)&LAB_004ee6c0;
        *(float *)(owner + 0x28) = *(float *)0x00e2e24c;
        *(float *)(owner + 0x2c) = *(float *)0x00e2e250;
    }

    iVar5 = *(int *)(component + 0x24); // sub-object pointer
    uVar4 = *(short *)(iVar5 + 0x2c); // flags
    if ((uVar4 & 0x200) != 0) {
        timeDelta = *(float *)0x00e44764; // alternate time factor
    }

    float speedFactor = *(float *)(iVar5 + 0x10) / timeDelta;
    float forceFactor = 0.0f;
    if (*(int *)(owner + 0x1c) != 0) {
        forceFactor = (float)*(int *)(*(int *)(owner + 0x1c) + 0x18) * *(float *)(owner + 0x2c);
    }
    float externalForce = *(float *)(component + 0x30);
    forceFactor = (externalForce / forceFactor) * speedFactor;

    // Determine direction/type flags
    local_6c = 0;
    if ((uVar4 & 1) == 0) {
        if ((uVar4 & 2) != 0) local_6c = 2;
    } else {
        local_6c = 1;
    }
    local_64 = 0;
    if ((uVar4 & 8) == 0) {
        if ((uVar4 & 0x10) != 0) local_64 = 2;
    } else {
        local_64 = 1;
    }

    local_44 = speedFactor * *(float *)0x00e2ee80; // some base force
    // Conditionally point to local_44 if bit 7 of flags is set
    pfVar10 = (float *)(-(uint)((uVar4 & 0x80) != 0) & (uint)&local_44);
    local_54 = CONCAT31(local_54._1_3_, (byte)uVar4 >> 6) & 0xffffff01;
    local_40 = local_44; // copy

    FUN_004ecd50(iVar5, externalForce); // initial step

    local_58 = 0;
    // Main physics block
    if (*(float *)(iVar5 + 0x4c) != 0.0f && 0.0f < *(float *)(iVar5 + 0x40) && 0.0f < local_70) {
        float accel = local_70;
        FUN_00488210(iVar8 + 0x1c);
        iVar5 = *(int *)(component + 0x24);
        accel = accel * forceFactor;
        float curForce = *(float *)(iVar5 + 0x50) * (local_70 / *(float *)(iVar5 + 0x40));
        bVar2 = *(byte *)(iVar5 + 0x2f);
        bool bVar7 = false;
        if (curForce < accel && (bVar2 & 1) != 0) bVar7 = true;
        if (bVar7 || curForce < accel || ((~(bVar2 >> 1) & 1) != 0)) {
            float posDelta = accel;
            FUN_00488210(iVar8 + 0x1c);
            iVar5 = *(int *)(component + 0x24);
            float mass = (float)*(int *)(iVar5 + 0x54);
            if (*(int *)(iVar5 + 0x54) < 0) {
                mass += *(float *)0x00e44578; // smoothing constant
            }
            float relForce = *(float *)(iVar5 + 0x50) / *(float *)(iVar5 + 0x40);
            float velocity = *(float *)(component + 0x34) + *(float *)(component + 0x38);
            float newPos = mass * posDelta * forceFactor + posDelta;
            local_58 = &local_3c;
            *(float *)(component + 0x38) = velocity; // update velocity component
            float damping = 0.0f;
            if (!bVar7) {
                damping = (*(float *)(iVar5 + 0x4c) / *(float *)(iVar5 + 0x40)) * velocity;
            }
            float fVar13 = *(float *)(iVar5 + 0x4c);
            float ratio = newPos / local_70;
            if (fVar13 < 0.0f) {
                damping = ratio + damping;
            }
            if (fVar13 <= 0.0f || damping * local_70 <= newPos) {
                local_3c = damping;
                if (fVar13 < 0.0f && damping * local_70 < 0.0f) {
                    local_3c = damping * local_70 + ratio;
                    *(float *)(component + 0x38) = 
                        *(float *)0x00e44564 - (damping / fVar13) * local_70 * *(float *)(iVar5 + 0x40);
                }
            } else {
                *(float *)(component + 0x38) = ((damping - ratio) / fVar13) * *(float *)(iVar5 + 0x40);
                local_3c = damping - ratio;
            }
        } else {
            if ((bVar2 & 4) != 0) local_6c = 1;
            local_70 = curForce;
        }
    }

    // Haptic feedback and second processing
    if (pfVar10 != 0 && (*pfVar10 != 0.0f || pfVar10[1] != 0.0f)) {
        if ((*(int *)0x01227870 & 1) == 0) {
            *(int *)0x01227870 |= 1;
            FUN_004d9500("{66EB9CC0-9CC0-66EB-C09C-EB66C09CEB66}"); // haptic guid
        }
        if (*(int *)(component + 4) != 0 && 
            FUN_00420950(&DAT_01227860) != 0) {
            float scaledTime = speedFactor * *(float *)0x00e2b334;
            // Save position and apply offset
            savedPos[0] = 0;
            savedPos[1] = 0;
            savedPos[2] = 0;
            savedPos[3] = *(float *)0x00e44584;
            savedPos[0] = *(float *)(*_DAT_01205504 + 0x10);
            savedPos[1] = *(float *)(*_DAT_01205504 + 0x14);
            savedPos[2] = *(float *)(*_DAT_01205504 + 0x18);
            savedPos[3] = *(float *)(*_DAT_01205504 + 0x1c);
            *(float *)(*_DAT_01205504 + 0x10) = 0;
            *(float *)(*_DAT_01205504 + 0x14) = 0;
            *(float *)(*_DAT_01205504 + 0x18) = 0;
            *(float *)(*_DAT_01205504 + 0x1c) = *(float *)0x00e44584;
            *pfVar10 = scaledTime;
            pfVar10[1] = scaledTime;
            pfVar10 = 0;
            FUN_0048a3b0(scaledTime, timeDelta - scaledTime, local_70, externalForce, forceFactor,
                         *(int *)(component + 0x20), local_6c, local_64, 0, local_54, 0, 0, 0,
                         local_58, *(int *)(component + 0x2c), *(byte *)(component + 0x3c));
            // Restore saved position
            int tmp = *_DAT_01205504;
            *(float *)(tmp + 0x10) = savedPos[0];
            *(float *)(tmp + 0x14) = savedPos[1];
            *(float *)(tmp + 0x18) = savedPos[2];
            *(float *)(tmp + 0x1c) = savedPos[3];
        }
    }

    // Final integration/constraint call
    FUN_0048a3b0(0, 1.0f, local_70, externalForce, forceFactor,
                 *(int *)(component + 0x20), local_6c, local_64, pfVar10, local_54, 0, 0, 0,
                 local_58, *(int *)(component + 0x2c), *(byte *)(component + 0x3c));

    // Reset time step
    float fVar14 = *(float *)0x00e2b1a4;
    if (*(int *)(iVar8 + 0x54) != 0) {
        uVar11 = *(int *)0x01205898;
        *(int *)(iVar8 + 0x54) = 0;
        *(float *)(iVar8 + 0x28) = fVar14 / (float)*(int *)0x0120588c;
        *(float *)(iVar8 + 0x2c) = fVar14 / (float)uVar11;
    }
    *(int *)(component + 0x20) = 0;
}