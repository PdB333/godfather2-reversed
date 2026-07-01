// FUNC_NAME: DestructibleObject::applyRandomDebrisForce

void __fastcall DestructibleObject::applyRandomDebrisForce(int *this)
{
    float fVar1;
    float fVar2;
    undefined4 uVar3;
    int iVar4;
    char cVar5;
    int iVar6;
    float *pfVar7;
    int iVar8;
    int iVar9;
    float10 fVar10;
    float fVar11;
    float fVar12;
    float fVar13;
    float fStack_50;
    float fStack_4c;
    float fStack_48;
    float fStack_44;
    float fStack_40;
    float fStack_3c;
    float fStack_38;
    float fStack_34;
    undefined4 local_30;
    float local_2c;
    undefined4 local_28;
    undefined4 local_24;
    float fStack_20;
    float fStack_1c;
    float fStack_18;

    // Check if force already applied (bit 4 of flags at +0xC88)
    if (((uint)this[0x322] >> 4 & 1) == 0) {
        // Get some singleton object (maybe Player or Camera)
        iVar6 = getPlayer();  // FUN_005466a0()
        // Get current time for random seed?
        fVar10 = (float10)getCurrentTime();  // FUN_009efd10()
        setRandomSeed((float)(fVar10 * (float10)GAME_TIME_SCALE));  // FUN_009f3d60()
        // Read euler angles from player's transform (offset +0x160 = rotation)
        local_30 = *(undefined4 *)(iVar6 + 0x160);
        local_28 = *(undefined4 *)(iVar6 + 0x168);
        local_2c = *(float *)(iVar6 + 0x164) + HALF;  // +0.5
        local_24 = *(undefined4 *)(iVar6 + 0x16c);
        // Convert euler to quaternion
        quaternionFromEuler(&local_30);  // FUN_009f4400()
        // Get game manager from global
        iVar4 = *(int *)(GODFATHER_GAME_MANAGER + 0x24);
        // Check if object is alive (vtable+0x19c)
        cVar5 = (**(code **)(*this + 0x19c))();
        if (cVar5 != '\0') {
            // Activate something (vtable+0x23c)
            (**(code **)(*this + 0x23c))();
        }
        randFloat();  // FUN_009f2000()
        // Get vehicle's physics transform (first call: position)
        pfVar7 = (float *)getPhysicsTransform();  // FUN_00471610()
        fVar13 = *pfVar7;
        fVar1 = pfVar7[1];
        fVar2 = pfVar7[2];
        // Second call: basis vectors? (offsets 0x20-0x28)
        iVar8 = getPhysicsTransform();
        fStack_20 = *(float *)(iVar8 + 0x20);
        fStack_1c = *(float *)(iVar8 + 0x24);
        fStack_18 = *(float *)(iVar8 + 0x28);
        // Third call: velocity? (offsets 0x30-0x38)
        iVar8 = getPhysicsTransform();
        fStack_4c = *(float *)(iVar8 + 0x34);
        fStack_48 = *(float *)(iVar8 + 0x38);
        fStack_50 = *(float *)(iVar8 + 0x30);
        fStack_44 = ZERO_EPS;  // _DAT_00d5780c likely 0.0

        // Generate random perturbation for debris scatter
        iVar8 = _rand();
        fVar11 = (float)iVar8 * INV_RAND_MAX - HALF;  // [-0.5, 0.5]
        if (fVar11 < 0.0) {
            fVar11 = fVar11 + HALF;
        } else {
            fVar11 = fVar11 - HALF;
        }
        fVar11 = fVar11 * SCATTER_SCALE_X;  // DAT_00d5ef6c

        iVar8 = _rand();
        fVar12 = (float)iVar8 * INV_RAND_MAX - HALF;
        if (fVar12 < 0.0) {
            fVar12 = fVar12 + HALF;
        } else {
            fVar12 = fVar12 - HALF;
        }
        fVar12 = fVar12 * SCATTER_SCALE_Y;  // DAT_00d5ef6c (same)

        // Apply perturbation to velocity
        fStack_50 = fStack_50 + fVar11 * fVar13 + fVar12 * fStack_20;
        fStack_4c = fStack_4c + fVar1 * fVar11 + fStack_1c * fVar12;
        fStack_48 = fStack_48 + fVar2 * fVar11 + fStack_18 * fVar12;
        fStack_44 = fStack_44 + fVar11 + fVar12;

        // Second random component (angular? wave?)
        iVar8 = _rand();
        iVar9 = _rand();
        fStack_38 = ((float)iVar8 * INV_RAND_MAX - HALF) * ANGULAR_SCALE;  // DAT_00d5f520
        fStack_40 = ((float)iVar9 * INV_RAND_MAX - HALF) * OTHER_ANGULAR_SCALE;  // DAT_00d5f378

        // Normalize (fStack_38, fStack_40, 0)
        fVar13 = fStack_38 * fStack_38 + fStack_40 * fStack_40 + ZERO_EPS;
        if (fVar13 == 0.0) {
            fStack_3c = 0.0;
        } else {
            fStack_3c = ZERO_EPS / sqrt(fVar13);
        }
        fStack_38 = fStack_38 * fStack_3c;
        fStack_40 = fStack_3c * fStack_40;
        fStack_34 = fStack_3c * 0.0;

        // Time delta for force intensity
        fVar10 = (float10)getCurrentTime();  // FUN_009efd10()
        iVar8 = _rand();
        fVar13 = ((float)iVar8 * INV_RAND_MAX * HALF + HALF) * (float)fVar10 * FORCE_MULTIPLIER;  // _DAT_00d76488
        fStack_40 = fVar13 * fStack_40;
        fStack_3c = fStack_3c * fVar13;
        fStack_38 = fStack_38 * fVar13;
        fStack_34 = fStack_34 * fVar13;

        // Get physics component pointer (global +0x24 -> +0x6c -> +0x58)
        uVar3 = *(undefined4 *)(*(int *)(iVar4 + 0x6c) + 0x58);
        randFloat();  // FUN_009f2000()
        // Apply force to physics object (vtable+0x54)
        (**(code **)(*(int *)(iVar6 + 0xd0) + 0x54))(uVar3, &fStack_40, &fStack_50);

        // Set flag to prevent re-application
        if ((this[0x322] | 0x10U) != this[0x322]) {
            (**(code **)(this[0x16] + 0x28))(0x10);
            this[0x322] = this[0x322] | 0x10;
        }
    }
    return;
}