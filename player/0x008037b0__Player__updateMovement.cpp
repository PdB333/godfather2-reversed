// FUNC_NAME: Player::updateMovement

void __thiscall Player::updateMovement(int *this, float *velocity)
{
    float fVar1;
    undefined8 uVar2;
    code *pcVar3;
    char cVar4;
    int iVar5;
    int *piVar6;
    int unaff_ESI;
    float10 fVar7;
    float fVar8;
    float fVar9;
    float local_34;
    undefined8 local_30;
    float local_28;
    undefined4 local_24;
    float local_20;
    float local_1c;
    float local_18;
    undefined4 uStack_14;

    fVar8 = *velocity;
    fVar1 = velocity[2];
    // Check if velocity squared magnitude exceeds threshold or a flag is set
    if ((DAT_00e44598 < fVar8 * fVar8 + velocity[1] * velocity[1] + fVar1 * fVar1) ||
        (((uint)this[0x6e5] >> 0xe & 1) != 0)) {
        uVar2 = *(undefined8 *)velocity;
        local_28 = velocity[2];
        fVar9 = (float)this[0x10b] * DAT_012067e8; // position.z * deltaTime
        *velocity = fVar8 - (float)this[0x109] * DAT_012067e8; // velocity.x -= position.x * dt
        velocity[2] = fVar1 - fVar9; // velocity.z -= position.z * dt
        velocity[1] = 0.0;
        this[0x6e5] = this[0x6e5] | 0x4000; // set flag
        local_30 = uVar2;
        // If some threshold > 0 and physics body exists and is not a specific type
        if ((0.0 < (float)this[0x407]) && ((this[0x3ff] != 0 && (this[0x3ff] != 0x48)))) {
            local_30._4_4_ = (float)((ulonglong)uVar2 >> 0x20);
            local_30._0_4_ = (float)uVar2;
            // If magnitude squared exceeds another threshold, normalize and scale
            if (_DAT_00d723a4 <
                local_30._4_4_ * local_30._4_4_ + local_28 * local_28 + (float)local_30 * (float)local_30) {
                FUN_0043a210(&local_30, &local_30); // normalize vector
                local_30._0_4_ = (float)local_30 * _DAT_00d5cf70; // scale
                local_30._4_4_ = local_30._4_4_ * _DAT_00d5cf70;
                local_28 = local_28 * _DAT_00d5cf70;
            }
            local_24 = 0;
            fVar7 = (float10)FUN_0056afa0(&local_30, &local_30); // magnitude squared
            local_34 = (float)fVar7 * (float)fVar7; // magnitude^4?
            iVar5 = FUN_00471610(); // get camera or player transform
            local_20 = (float)local_30 * local_34 + *(float *)(iVar5 + 0x30); // add camera offset
            local_1c = local_30._4_4_ * local_34 + *(float *)(iVar5 + 0x34);
            local_18 = local_28 * local_34 + *(float *)(iVar5 + 0x38);
            // Get physics body pointer (subtract 0x48 from the pointer)
            if (this[0x3ff] == 0) {
                piVar6 = (int *)0x0;
            } else {
                piVar6 = (int *)(this[0x3ff] + -0x48);
            }
            // Call virtual function on physics body (likely applyForce or setPosition)
            (**(code **)(*piVar6 + 0x1c))(&local_20);
        }
    }
    fVar8 = velocity[1];
    fVar1 = *velocity;
    fVar9 = velocity[2];
    // Clamp velocity magnitude to maximum
    if (_DAT_00d723a4 < fVar1 * fVar1 + fVar8 * fVar8 + fVar9 * fVar9) {
        uStack_14 = 0;
        local_20 = fVar1;
        local_1c = fVar8;
        local_18 = fVar9;
        FUN_0056afa0(&local_20, &local_20); // compute magnitude
        fVar8 = _DAT_00d5cf70;
        *velocity = local_20 * _DAT_00d5cf70; // scale to max
        velocity[1] = local_1c * fVar8;
        velocity[2] = local_18 * fVar8;
    }
    // Clamp velocity.x to [centerX - rangeX, centerX + rangeX]
    fVar8 = (float)this[0x7a9] + (float)this[0x7ab];
    if (*velocity <= fVar8) {
        fVar8 = (float)this[0x7a9] - (float)this[0x7ab];
        if (*velocity < fVar8) {
            *velocity = fVar8;
        }
    } else {
        *velocity = fVar8;
    }
    this[0x7a9] = (int)*velocity; // store clamped x as int
    // Clamp velocity.z to [centerZ - rangeZ, centerZ + rangeZ]
    fVar8 = (float)this[0x7aa] + (float)this[0x7ab];
    if (velocity[2] <= fVar8) {
        fVar8 = (float)this[0x7aa] - (float)this[0x7ab];
        if (velocity[2] < fVar8) {
            velocity[2] = fVar8;
        }
    } else {
        velocity[2] = fVar8;
    }
    fVar8 = _DAT_00d5780c;
    this[0x7aa] = (int)velocity[2]; // store clamped z as int
    // Compute time step from global frame time
    fVar8 = fVar8 / *(float *)(DAT_01223480 + 0x60);
    pcVar3 = *(code **)(*this + 0x10); // virtual function (handleMessage?)
    local_28 = fVar8 * velocity[2] + (float)this[0x10b]; // integrate position.z
    local_30 = CONCAT44(velocity[1] * fVar8 + (float)this[0x10a], // integrate position.y
                        *velocity * fVar8 + (float)this[0x109]); // integrate position.x
    *(undefined8 *)(this + 0x109) = local_30; // store new position.x and y
    this[0x10b] = (int)local_28; // store new position.z
    local_34 = 0.0;
    cVar4 = (*pcVar3)(0x383225a1, &local_34); // send message with ID
    // If message handled, unaff_ESI is valid, and conditions met, set flag on unaff_ESI
    if ((((cVar4 != '\0') && (unaff_ESI != 0)) && ((char)this[0x40a] != '\0')) &&
       (((this[0x3ff] != 0 && (this[0x3ff] != 0x48)) && (cVar4 = FUN_00481620(), cVar4 != '\0')))) {
        *(uint *)(unaff_ESI + 0x24a0) = *(uint *)(unaff_ESI + 0x24a0) | 2;
    }
    return;
}