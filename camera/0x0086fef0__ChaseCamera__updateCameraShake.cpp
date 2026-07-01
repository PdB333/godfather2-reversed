// FUNC_NAME: ChaseCamera::updateCameraShake

void __thiscall ChaseCamera::updateCameraShake(ChaseCamera* this, float deltaTime)
{
    // +0x5c: pointer to a component/controller (likely a rumble or shake controller)
    // +0x6c: bitfield flags (6: shake enabled, 7: something, 8: directional shake, 9: complex shake, 10: cooldown)
    // +0x50: parent camera or transform object
    // +0xa4: shake timer (countdown until next shake impulse)
    // +0xa8: stored shake intensity (from previous frame?)
    // +0xb0: next shake interval (in frames?)

    float fVar1, fVar2, fVar3, fVar4, fVar13, fVar14, fVar15, fVar16, fVar17;
    int iVar7, iVar8, iVar10;
    float* pfVar9;
    int* piVar11;
    float local_c, local_8, local_4; // delta position components
    uint uVar5;
    uint uStack_28;
    float fStack_30; // final shake intensity

    // Step 0: Update the rumble/shake system with the given delta time (cleared?)
    FUN_0086f5c0(deltaTime, 0); // likely resets internal state

    // Get two objects (likely player and target, or camera target and player)
    iVar7 = FUN_00471610(); // returns pointer to first object (e.g., player transform)
    iVar8 = FUN_00471610(); // returns pointer to second object (e.g., current camera target)

    // Compute delta position (relative vector from target to player?)
    local_c = *(float*)(iVar7 + 0x30) - *(float*)(iVar8 + 0x30); // +0x30: x position
    local_8 = *(float*)(iVar7 + 0x34) - *(float*)(iVar8 + 0x34); // +0x34: y position
    local_4 = *(float*)(iVar7 + 0x38) - *(float*)(iVar8 + 0x38); // +0x38: z position

    // Get the angle from a virtual function (probably the heading/rotation of the shake controller)
    // Base address from this+0x5c -> vtable at +0x1b0
    fVar3 = (float)(*(double* (__thiscall**)(void*))(*(int*)this->mShakeController + 0x1b0))(this->mShakeController);
    fVar13 = fVar3 - PI; // _DAT_00d75f50 likely PI (3.14159...)
    fVar14 = 0.0f;
    if (fVar13 <= 0.0f) {
        fVar13 = 0.0f;
    } else if (TWO_PI <= fVar13) { // _DAT_00d75fd0 likely TWO_PI (6.28318...)
        fVar13 = TWO_PI;
    }

    // Convert angle to a factor (1.0 - angle * invPI?) // _DAT_00d5780c=1.0, _DAT_00d68258=1/PI
    fVar13 = 1.0f - fVar13 * (1.0f / PI); 

    // Get the facing direction from the first object
    pfVar9 = (float*)FUN_00471610(); // again? returns orientation/direction vector
    fVar14 = (*pfVar9) * local_c + pfVar9[1] * local_8 + pfVar9[2] * local_4; // dot product with line-of-sight

    // Compute base shake intensity
    fStack_30 = (fVar13 + 1.0f) * SHAKE_RANGE; // _DAT_00d5eee0: range scaling factor

    // If looking away (dot product almost negative?), invert the shake side
    if (0.0f <= fVar14) { // _DAT_00d577a0 likely 0.0
        fStack_30 = 1.0f - fStack_30; // _DAT_00e44564 likely 1.0f
    }

    // Get the vehicle/controller responsible for shake tuning
    iVar7 = FUN_008fa210(); // returns pointer to a shake parameters object (e.g., VehicleBrain)
    uVar5 = *(uint*)(this + 0x6c); // current flags

    // Bit 7: decide between simple and complex rumble path
    if (((uVar5 >> 7 & 1) == 0) || (iVar7 == 0)) {
        // Simple path: bit 6 (shake enabled) and bit 10 (cooldown?) 
        if (((uVar5 >> 6 & 1) != 0) && (((uVar5 >> 10 & 1) != 0 && (iVar7 != 0)))) {
            fStack_30 = 1.0f - *(float*)(iVar7 + 0xa0) * fStack_30; // scale by some parameter
        }
        goto LAB_00870450;
    }

    // Complex rumble path: get a random value
    fVar12 = (float)FUN_0086d760(); // random number between 0 and 1 perhaps
    fVar13 = (float)fVar12;
    fVar4 = (float)(fVar12 * *(float*)(iVar7 + 0x10) + *(float*)(iVar7 + 0xc)); // random offset

    iVar8 = FUN_00471610(); // get orientation of second object? (target?)
    fVar15 = 1.0f - (*(float*)(iVar8 + 0x24) * local_8 + *(float*)(iVar8 + 0x20) * local_c +
                    *(float*)(iVar8 + 0x28) * local_4); // reverse dot product
    if (fVar15 < 0.0f) {
        *(uint*)(this + 0x6c) &= 0xFFFFFDFF; // clear bit 9 (maybe disable directional mode)
    }

    uVar5 = *(uint*)(this + 0x6c);
    fVar16 = (float)((uint)fVar14 & INT_MASK); // _DAT_00e44680 likely 0xFFFFFFFF, but used as bitwise with float bits? 

    // Check if both bits 9 and 8 are set (complex mode)
    if (((uVar5 >> 9 & 1) != 0) && ((uVar5 >> 8 & 1) != 0)) {
        // Use many parameters from iVar7 to adjust shake
        fVar14 = *(float*)(iVar7 + 0x78);
        fVar4 = *(float*)(iVar7 + 0x74);
        fVar1 = *(float*)(iVar7 + 0x80);
        fVar2 = *(float*)(iVar7 + 0x7c);
        fStack_30 = *(float*)(iVar7 + 0x70) * fStack_30;
        fVar17 = MIN_SHAKE; // _DAT_00d5ccf8 maybe 0.0 or -1.0?
        if ((fStack_30 <= MIN_SHAKE) || (fVar17 = MAX_SHAKE, MAX_SHAKE <= fStack_30)) { // _DAT_00d5780c=MAX
            fStack_30 = fVar17;
        }
        // Set rumble axes: left motor (0), right motor (0), trigger (0 or 1)
        FUN_0086b7d0(0.0f);
        FUN_0086b7f0(0.0f);
        if (*(float*)(iVar7 + 0x6c) <= fVar3) {
            FUN_0086b7b0(0.0f); // trigger off
        } else {
            FUN_0086b7b0(1.0f); // trigger on
        }
        // Check conditions to clear bit 8 (disable directional shake)
        if ((((fVar13 + fVar3) * fVar1 + fVar2 < fVar15) || (fVar14 * fVar3 + fVar4 <= fVar16)) ||
            (fVar3 < *(float*)(iVar7 + 0x84) || fVar3 == *(float*)(iVar7 + 0x84))) {
            if (fVar15 < *(float*)(iVar7 + 0x88)) {
                *(uint*)(this + 0x6c) &= 0xFFFFFEFF; // clear bit 8
            }
        } else {
            *(uint*)(this + 0x6c) &= 0xFFFFFEFF;
        }
        goto LAB_00870450;
    }

    // Bit 8 set but not bit 9 (directional mode only)
    if (((uVar5 >> 8 & 1) != 0) && (fVar15 <= fVar4)) {
        if (*(float*)(iVar7 + 0x14) <= fVar16) {
            if ((*(float*)(iVar7 + 0x18) <= fVar3 && fVar3 != *(float*)(iVar7 + 0x18)) &&
               (*(float*)(iVar7 + 0x1c) * fVar4 < fVar15)) {
                fStack_30 = *(float*)(iVar7 + 0x20) * fStack_30;
            }
        } else {
            fStack_30 = 0.0f;
        }
        FUN_0086b7d0(0.0f);
        FUN_0086b7f0(0.0f);
        if (*(float*)(iVar7 + 0x24) <= (fVar3 - fVar13)) {
            FUN_0086b7b0(0.0f);
        } else {
            FUN_0086b7b0(1.0f);
        }
        goto LAB_00870450;
    }

    // If neither bit 8 nor bit 9, clear bit 8 and do a more direct calculation
    *(uint*)(this + 0x6c) &= 0xFFFFFEFF;
    iVar10 = FUN_00471610(); // get another transform
    fVar4 = *(float*)(iVar8 + 0x20);
    if (*(float*)(iVar7 + 0x30) <= (float)((uint)(*(float*)(iVar8 + 0x24) * *(float*)(iVar10 + 0x24) +
                                                fVar4 * *(float*)(iVar10 + 0x20) +
                                                *(float*)(iVar10 + 0x28) * *(float*)(iVar8 + 0x28)) & INT_MASK)) {
        fStack_30 = *(float*)(this + 0xa8);
        if (fStack_30 == 0.0f) {
            fStack_30 = MAX_SHAKE; // _DAT_00d5780c
            if (0.0f <= fVar14 - (*(float*)(iVar8 + 0x24) * local_8 + fVar4 * local_c +
                                *(float*)(iVar8 + 0x28) * local_4) *
                                (*(float*)(iVar8 + 0x24) * pfVar9[1] + fVar4 * *pfVar9 +
                                *(float*)(iVar8 + 0x28) * pfVar9[2])) {
                fStack_30 = MIN_SHAKE; // _DAT_00d5ccf8
            }
            goto LAB_0087036a;
        }
    } else {
        fStack_30 = 0.0f;
LAB_0087036a:
        *(float*)(this + 0xa8) = fStack_30; // store for next frame
    }

    // Build an additional flag word for rumble
    uStack_28 = (uint)fVar13 & 0xFFFFFF00; // lower byte masked out
    if (*(float*)(iVar7 + 0x28) <= fVar3 && fVar3 != *(float*)(iVar7 + 0x28)) {
        uStack_28 = CONCAT31((int3)((uint)fVar13 >> 8), 1); // set lowest byte to 1
    } else if (fVar16 < *(float*)(iVar7 + 0x2c)) {
        iVar8 = *(int*)(*(int*)(this + 0x50) + 0x70);
        if (iVar8 == 0) {
            piVar11 = nullptr;
        } else {
            piVar11 = (int*)(iVar8 - 0x48); // pointer math on parent object
        }
        (**(code**)(*piVar11 + 0x4c))(&local_c); // virtual call on some object
        if (local_8 * *(float*)(iVar10 + 0x24) + *(float*)(iVar10 + 0x20) * local_c +
            *(float*)(iVar10 + 0x28) * local_4 < VERTICAL_THRESHOLD) { // _DAT_00d68260
            goto LAB_008703ea;
        }
    }

    // Set rumble motors based on calculated parameters
    FUN_0086b7d0(1.0f); // left motor full
    FUN_0086b7f0((float)uStack_28); // right motor as per the derived flag
    FUN_0086b7b0(0.0f); // trigger off

LAB_008703ea:
    FUN_0086b7d0(1.0f);
    FUN_0086b7f0(uStack_28);
    FUN_0086b7b0(0.0f);

    // After switching rumble, apply final intensity
LAB_00870450:
    FUN_0086b830(fStack_30); // apply shake intensity to motors

    // Update shake timer
    deltaTime = *(float*)(this + 0xa4) - deltaTime;
    *(float*)(this + 0xa4) = deltaTime;

    // If timer expired and vehicle exists and shake enabled (bit 6)
    if (((deltaTime <= 0.0f) && (iVar7 != 0)) && ((*(uint*)(this + 0x6c) >> 6 & 1) != 0)) {
        if ((*(uint*)(this + 0x6c) >> 10 & 1) == 0) {
            iVar8 = rand();
            float randomDuration = (float)iVar8 * RANDOM_SCALE * *(float*)(iVar7 + 0x9c) + *(float*)(iVar7 + 0x98);
            *(float*)(this + 0xa4) = randomDuration;
            if (0.0f < randomDuration) {
                *(uint*)(this + 0x6c) |= 0x400; // set bit 10 (cooldown active)
            }
        }
        *(int*)(this + 0xb0) = *(int*)(iVar7 + 0xa4) + BASE_INTERVAL; // _DAT_01205224
    }
    return;
}