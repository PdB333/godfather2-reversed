// FUNC_NAME: PlayerSM::updateMovementDirection

void __fastcall PlayerSM::updateMovementDirection(int *this)
{
    int iVar1;
    undefined4 uVar2;
    char cVar3;
    int iVar4;
    float10 fVar5;
    double dVar6;
    float fVar7;
    float fVar8;
    float fVar9;
    float fVar10;
    float local_50;
    float fStack_4c;
    float fStack_48;
    float fStack_44;
    float fStack_40;
    float fStack_3c;
    float fStack_38;
    float fStack_30;
    float fStack_2c;
    float fStack_28;
    float fStack_24;
    float fStack_20;
    float fStack_1c;
    float fStack_18;
    float fStack_14;
    
    uVar2 = DAT_01206800;
    iVar1 = this[1]; // +0x04 - pointer to player data
    if ((char)this[0x10] != '\0') { // +0x40 - some flag
        fVar5 = (float10)(**(code **)(*this + 8))(); // virtual function call
        FUN_007992a0((float)fVar5, _DAT_00e5303c, uVar2, &fStack_44, 0);
    }
    cVar3 = FUN_00481620(); // check if player is in vehicle
    if (cVar3 == '\0') {
        // On foot movement
        local_50 = 0.0;
        fStack_4c = 0.0;
        fStack_48 = 0.0;
        cVar3 = FUN_00472510(&fStack_30); // get camera forward vector
        if (cVar3 != '\0') {
            // Normalize camera forward
            fVar7 = fStack_28 * fStack_28 + fStack_2c * fStack_2c + fStack_30 * fStack_30;
            fStack_38 = 0.0;
            if (fVar7 != 0.0) {
                fStack_38 = _DAT_00d5780c / SQRT(fVar7); // 1.0f / length
            }
            fStack_40 = fStack_38 * fStack_30;
            fStack_3c = fStack_38 * fStack_2c;
            fStack_14 = fStack_38 * fStack_24;
            fStack_38 = fStack_38 * fStack_28;
            fStack_20 = fStack_40;
            fStack_1c = fStack_3c;
            fStack_18 = fStack_38;
            
            iVar4 = FUN_00471610(); // get player transform
            fStack_2c = *(float *)(iVar4 + 0x24); // +0x24 - forward.z
            fStack_28 = *(float *)(iVar4 + 0x28); // +0x28 - forward.x
            fStack_30 = *(float *)(iVar4 + 0x20); // +0x20 - forward.y
            
            // Normalize player forward
            fVar7 = fStack_28 * fStack_28 + fStack_2c * fStack_2c + fStack_30 * fStack_30;
            if (fVar7 == 0.0) {
                fStack_24 = 0.0;
            }
            else {
                fStack_24 = _DAT_00d5780c / SQRT(fVar7);
            }
            fStack_28 = fStack_28 * fStack_24;
            fStack_2c = fStack_2c * fStack_24;
            fStack_30 = fStack_24 * fStack_30;
            
            // Dot product of camera forward and player forward
            fVar8 = fStack_28 * fStack_38 + fStack_2c * fStack_3c + fStack_30 * fStack_40;
            fVar7 = _DAT_00d5780c;
            if ((fVar8 <= _DAT_00d5780c) && (fVar7 = fVar8, fVar8 < DAT_00d5ccf8)) {
                fVar7 = DAT_00d5ccf8;
            }
            
            // Cross product for turn direction
            fVar8 = fStack_20 * fStack_2c;
            fVar9 = fStack_20 * fStack_28;
            fVar10 = fStack_1c * fStack_30;
            fStack_20 = fStack_18 * fStack_2c - fStack_1c * fStack_28;
            fStack_1c = fVar9 - fStack_18 * fStack_30;
            fStack_18 = fVar10 - fVar8;
            fStack_14 = fStack_14 * fStack_24 - fStack_14 * fStack_24;
            
            dVar6 = (double)fVar7;
            if (0.0 <= fStack_1c) {
                FUN_00b9b988(); // acos
                local_50 = DAT_00e44564 - (float)dVar6; // PI - angle
            }
            else {
                FUN_00b9b988(); // acos
                local_50 = (float)dVar6;
            }
            fStack_44 = local_50 + DAT_00d68264; // angle + some offset
            dVar6 = (double)fStack_44;
            FUN_00b99e20(); // sin
            fStack_4c = (float)dVar6;
            dVar6 = (double)fStack_44;
            FUN_00b99fcb(); // cos
            fStack_48 = (float)dVar6;
        }
    }
    else {
        // In vehicle movement
        FUN_0079eab0(0, &fStack_4c, &fStack_48, 1, 0, DAT_00d5ccf8, DAT_00d5ccf8, DAT_00d5ccf8);
        fVar5 = (float10)FUN_0079eb90(0, 0);
        local_50 = (float)fVar5;
    }
    
    iVar4 = this[10]; // +0x28 - current movement direction
    if (((*(uint *)(iVar1 + 0x24a0) >> 1 & 1) != 0) || // +0x24a0 - some flag
       (((float)((uint)fStack_48 & DAT_00e44680) < DAT_00d6ee44 &&
        ((float)((uint)fStack_4c & DAT_00e44680) < DAT_00d6ee44)))) {
        // No input or dead zone
        this[10] = 0; // IDLE
        cVar3 = FUN_00481660(); // check if player is moving
        if ((cVar3 != '\0') && (iVar4 == this[10])) {
            FUN_00472130(0); // stop movement
        }
    }
    else if (0.0 <= fStack_48) {
        if (fStack_4c <= 0.0) {
            this[10] = 3; // BACKWARD_LEFT
        }
        else {
            this[10] = 4; // BACKWARD_RIGHT
        }
    }
    else if (fStack_4c <= 0.0) {
        this[10] = 1; // FORWARD_LEFT
    }
    else {
        this[10] = 2; // FORWARD_RIGHT
    }
    
    cVar3 = FUN_00481640(); // check if player is in combat
    if (cVar3 != '\0') {
        iVar1 = this[10];
        if (iVar4 == iVar1) {
            // Same direction, reset timers
            this[0xb] = 0; // +0x2c - timer[0]
            this[0xc] = 0; // +0x30 - timer[1]
            this[0xd] = 0; // +0x34 - timer[2]
            this[0xe] = 0; // +0x38 - timer[3]
            this[0xf] = 0; // +0x3c - timer[4]
        }
        else if (iVar4 != 0) {
            if ((uint)this[iVar1 + 0xb] < 3) { // check timer for new direction
                this[iVar1 + 0xb] = this[iVar1 + 0xb] + 1; // increment timer
                this[10] = iVar4; // keep old direction
            }
            else {
                // Timer expired, reset
                this[0xb] = 0;
                this[0xc] = 0;
                this[0xd] = 0;
                this[0xe] = 0;
                this[0xf] = 0;
            }
        }
    }
    
    if (this[10] != 0) {
        dVar6 = (double)local_50;
        FUN_00b99fcb(); // cos
        fStack_40 = (float)dVar6;
        dVar6 = (double)local_50;
        FUN_00b99e20(); // sin
        FUN_007ac590((uint)(DAT_00e53040 * fStack_40 + DAT_00e53044 * _DAT_00d577a0 +
                           DAT_00e53048 * (float)dVar6) & DAT_00e44680);
        cVar3 = FUN_00481660(); // check if player is moving
        if (cVar3 != '\0') {
            FUN_00472130(1); // start movement
        }
    }
    return;
}