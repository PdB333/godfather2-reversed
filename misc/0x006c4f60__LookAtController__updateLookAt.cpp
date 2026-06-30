// FUNC_NAME: LookAtController::updateLookAt

void __thiscall LookAtController::updateLookAt(LookAtController *this, float deltaTime) {
    float *pfVar1;
    float fVar2;
    int iVar3;
    int *piVar4;
    float10 fVar5;
    float fVar6;
    float fVar7;
    double dVar8;
    float fStack_64;
    float local_5c;
    float fStack_58;
    float local_54;
    float local_50;
    float local_4c;
    float local_48;
    undefined4 local_44;
    float fStack_38;
    float local_34;
    float local_30;
    float local_2c;
    float local_28;
    float fStack_24;
    float fStack_20;
    float local_1c;
    float fStack_18;

    // Determine pointer to owner or vtable from offset 0xe8
    if (*(int *)(this + 0xe8) == 0) {
        piVar4 = (int *)0x0;
    } else {
        piVar4 = (int *)(*(int *)(this + 0xe8) + -0x48);
    }

    // Get target info (player/camera) - likely a global
    iVar3 = FUN_00471610(); // e.g., getPlayerData()
    local_5c = (float)*(undefined8 *)(iVar3 + 0x30); // target X (double read)
    local_54 = *(float *)(iVar3 + 0x38); // target Z (actually Y? but ordering)
    fStack_58 = *(float *)(this + 0x224); // current look-at Y?

    // Compute direction from current target to desired look point
    fVar5 = (float10)FUN_006c9b00(&local_5c, (float *)(this + 0x220), 0, 0); // likely vec3 distance
    fVar2 = (float)fVar5;
    local_50 = *(float *)(this + 0x220) - local_5c; // delta X
    local_4c = *(float *)(this + 0x224) - fStack_58; // delta Y
    local_48 = *(float *)(this + 0x228) - local_54; // delta Z

    local_44 = 0;
    local_34 = local_50;
    local_30 = local_4c;
    local_2c = local_48;
    FUN_0056afa0(&local_50, &local_50); // normalize delta

    // Compute interpolation factor based on distance and fVar2 (maybe speed)
    fVar6 = SQRT(local_2c * local_2c + local_30 * local_30 + local_34 * local_34) * fVar2;
    local_5c = local_50 * fVar6 + local_5c; // interpolate target X
    fStack_58 = local_4c * fVar6 + fStack_58; // interpolate target Y
    local_54 = local_48 * fVar6 + local_54;   // interpolate target Z

    // Write new target position
    *(ulonglong *)(this + 0x24c) = CONCAT44(fStack_58, local_5c); // target X, Y at 0x24c, 0x250
    *(float *)(this + 0x254) = local_54; // target Z

    if (DAT_00d5ef84 < (float)(*(uint *)(this + 0x27c) & DAT_00e44680)) {
        return; // skip if timer not expired
    }

    // Compute look-at rotation from new target to owner
    FUN_006c0dd0(&local_28, &local_5c, piVar4); // compute rotation quaternion/euler
    (**(code **)(*piVar4 + 0x4c))(&local_1c); // call virtual function on owner (get some transform?)

    pfVar1 = (float *)(this + 0x238); // pointer to another rotation/angle
    fVar5 = (float10)FUN_006c9b00(pfVar1, &local_2c, 0, 0); // distance between current and desired rotation
    fVar6 = (float)fVar5;

    if (fVar5 < (float10)1) {
        // Smooth rotation interpolation
        local_28 = local_28 - *(float *)(this + 0x23c);
        fStack_24 = fStack_24 - *(float *)(this + 0x240);
        fVar7 = local_2c - *pfVar1;
        if (_DAT_00d5eff4 < (fStack_24 * fStack_24 + local_28 * local_28 + fVar7 * fVar7) * fVar6) {
            fStack_38 = fVar7 * fVar6 + *pfVar1;
            local_34 = local_28 * fVar6 + *(float *)(this + 0x23c);
            local_30 = fStack_24 * fVar6 + *(float *)(this + 0x240);
            fVar5 = (float10)FUN_006c9b00(&local_2c, &fStack_38, 0, 0);
            if (fVar5 < (float10)1) {
                *(undefined4 *)(this + 0x248) = *(undefined4 *)(this + 0x2a0);
                *(ulonglong *)(this + 0x24c) = CONCAT44(local_34, fStack_38);
                *(float *)(this + 0x254) = local_30;
                *(float *)(this + 0x2b8) = *(float *)(this + 0x2b8) + deltaTime; // accumulate timer
                *(undefined4 *)(this + 0x68) = *(undefined4 *)(this + 0x18c);
                goto LAB_006c51ff;
            }
        }
    }

    // Decay the smoothing factor (deltaTime subtract)
    deltaTime = *(float *)(this + 0x68) - deltaTime;
    if (deltaTime <= 0.0) {
        deltaTime = 0.0;
    }
    *(float *)(this + 0x68) = deltaTime;
    *(undefined4 *)(this + 0x2b8) = 0;
LAB_006c51ff:
    if (*(float *)(this + 0x68) != 0.0) {
        // Apply velocity/acceleration with interpolation
        local_54 = *(float *)(this + 0x214) - fVar2;
        fStack_38 = *(float *)(this + 0x24c) - fVar2;
        local_34 = *(float *)(this + 0x250) - local_5c;
        local_50 = *(float *)(this + 0x218) - local_5c;
        local_30 = *(float *)(this + 0x254) - fStack_58;
        local_4c = *(float *)(this + 0x21c) - fStack_58;
        dVar8 = (double)(DAT_00e44564 - local_54);
        FUN_00b9a9fa(); // some init or get time
        fVar5 = (float10)FUN_004a1580(*(float *)(this + 0x248) - (float)dVar8); // angle wrap
        fVar6 = (SQRT(fStack_18 * fStack_18 + local_1c * local_1c + fStack_20 * fStack_20) -
                 *(float *)(this + 0xf4)) / (*(float *)(this + 0xf8) - *(float *)(this + 0xf4)); // lerp factor
        if (0.0 < fVar6) {
            if (_DAT_00d5780c <= fVar6) {
                fVar6 = _DAT_00d5780c;
            }
        } else {
            fVar6 = 0.0;
        }
        fStack_64 = DAT_00d5ddec;
        if ((float)((uint)(float)fVar5 & DAT_00e44680) <= _DAT_00d5780c) {
            fStack_64 = (float)((uint)(float)fVar5 & DAT_00e44680) * DAT_00e445ac + _DAT_00d5780c;
        }
        fStack_64 = ((*(float *)(this + 0x194) - *(float *)(this + 400)) * fVar6 +
                    *(float *)(this + 400)) * fStack_64;
        fVar5 = (float10)FUN_006c89d0(*(undefined4 *)(this + 100), (float)fVar5, fStack_64);
        *(float *)(this + 100) = (float)fVar5;
        FUN_004a0370(&local_54, &local_54, &DAT_00d5eed4, (float)fVar5);
        FUN_004a0370(&fStack_38, &fStack_38, &DAT_00d5eed4, *(undefined4 *)(this + 100));
        *(float *)(this + 0x214) = fVar2 + local_54;
        *(float *)(this + 0x218) = local_50 + local_5c;
        *(float *)(this + 0x21c) = fStack_58 + local_4c;
        *(float *)(this + 0x250) = local_34 + local_5c;
        *(float *)(this + 0x24c) = fStack_38 + fVar2;
        *(float *)(this + 0x254) = local_30 + fStack_58;
        fVar5 = (float10)FUN_004a1580(*(float *)(this + 0x20c) + *(float *)(this + 100));
        *(float *)(this + 0x20c) = (float)fVar5;
        return;
    }
    // If smoothing factor is zero, snap directly to target
    *(ulonglong *)(this + 0x24c) = CONCAT44(local_5c, fVar2);
    *(float *)(this + 0x254) = fStack_58;
    *(undefined4 *)(this + 100) = 0;
    return;
}