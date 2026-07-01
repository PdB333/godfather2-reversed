// FUNC_NAME: Entity::updateEngineEffects
void __fastcall Entity::updateEngineEffects(int *this) {
    float engineSpeed;
    float fVar2;
    bool bVar1;
    byte bVar3;
    char cVar4;
    int iVar5;
    uint flags;
    undefined4 uVar7;
    int *piStack_88;
    int iVar9;
    undefined4 *puVar13;
    float4 uStack_94;
    undefined1 auStack_90 [4];
    uint uStack_8c;
    int *piStack_88;
    undefined **ppuStack_84;
    undefined8 uStack_80;
    uint uStack_78;
    undefined4 uStack_74;
    undefined ***ppppuStack_70;
    undefined1 uStack_6c;
    float local_64;
    float fStack_5c;
    float afStack_54 [20];
    
    // Update engine RPM if below threshold (e.g., throttle released)
    if ((float)this[0x54] < g_frametime) {
        // Engine speed (RPM) increases based on some global
        FUN_004706f0(g_frameDelta * g_engineAccel + (float)this[0x54]);
    }
    
    // Update pitch and maybe other engine parameters
    FUN_0087da40();
    FUN_00874a10();
    
    local_64 = (float)this[0x4c]; // Some stored value (e.g., throttle input amplitude)
    
    // Virtual: getEngineSpeed() or getCurrentSpeed()
    float engineSpeedFromVtable = (**(code **)(*this + 0x1b0))();
    piStack_88 = (int *)(float)engineSpeedFromVtable; // Not used further? Possibly a cast
    
    FUN_00424fb0(&fStack_5c, 0); // Reset some vector? 
    iVar5 = FUN_00471610(); // Get player's transform object
    fStack_5c = *(float *)(iVar5 + 0x30) - fStack_5c;
    afStack_54[0] = *(float *)(iVar5 + 0x38) - afStack_54[0];
    fStack_5c_3 = *(float *)(iVar5 + 0x34) - fStack_5c_3; // fStack_58
    float magnitude = SQRT(fStack_5c * fStack_5c + afStack_54[0] * afStack_54[0] + fStack_5c_3 * fStack_5c_3);
    
    // If speed is above a threshold, handle engine idle/revving sounds
    if (g_minEngineSpeedThreshold < magnitude) {
        flags = this[0x322];
        if ((flags >> 0x18 & 1) == 0) { // Bit 24: maybe player-controlled?
            if (((flags & 0x100) != 0) || (g_highSpeedThreshold <= magnitude)) {
                // Check additional condition for revving
                if (((flags & 0x100) != 0) && (g_revThreshold < magnitude && (cVar4 = FUN_00875940(), cVar4 != '\0'))) {
                    FUN_00766440(0x100); // Play rev sound
                    puVar13 = &g_revSoundData1;
                    goto LAB_0087dc55;
                }
            }
            else {
                // Idle behavior: if speed below threshold and idle sound not already playing
                iVar5 = FUN_00875900();
                if (iVar5 != 0) {
                    FUN_00766470(0x100); // Start idle sound
                    puVar13 = &g_idleSoundData1;
LAB_0087dc55:
                    FUN_00408c70(puVar13, this + 0xf, 0); // Set sound at bone offset
                }
            }
        }
        else if (((flags >> 8 & 1) == 0) && (iVar5 = FUN_00875900(), iVar5 != 0)) {
            // Bit 24 set, bit 8 not set: alternate idle/rev handling
            FUN_00766470(0x100);
            puVar13 = &g_idleSoundData1;
            goto LAB_0087dc55;
        }
    }
    
    // Update engine state based on throttle input
    if (this[0x60] == 0) { // throttle off?
        // Use update function for no throttle
        pcVar10 = *(code **)(*this + 0xdc);
        piStack_88 = this + 0x2a9; // Some parameter (maybe rev limit?)
    }
    else {
        pcVar10 = *(code **)(*this + 0xe8); // With throttle
        auStack_90[3] = 1; // Indicate throttle active
        piStack_88 = (int *)(auStack_90 + 3);
    }
    (*pcVar10)(piStack_88); // Call the update function
    
    // Get current speed and angular velocity (rotations?)
    iVar5 = FUN_00471610();
    float speed = (**(code **)(*this + 0xc0))(); // getLinearSpeed?
    float rotation = (**(code **)(*this + 0xc4))(); // getAngularSpeed?
    piStack_88 = (int *)(float)speed;
    auStack_90 = (undefined1  [4])(float)rotation;
    uStack_94 = uStack_94 & 0xffffff; // Clear high byte
    
    // If not in a certain state, set flag and check speed ratio
    if (this[0x2dd] == 0) {
        uStack_94._0_3_ = CONCAT12(1, (undefined2)uStack_94); // Set bit 0
        uStack_94 = (uint)(uint3)uStack_94;
        if ((float)this[0x1ef] * (float)auStack_90 < (float)piStack_88) goto LAB_0087dceb; // Speed > torque*rotation
    }
    uStack_94 = uStack_94 & 0xffff; // Clear high word
    
LAB_0087dceb:
    // Check if character is in a vehicle (some global pointer)
    if (**(int **)(g_playerManager + 4) == 0) {
        iVar9 = 0;
    }
    else {
        iVar9 = **(int **)(g_playerManager + 4) + -0x1f30; // Get player object offset
    }
    bVar1 = true;
    if ((iVar9 != 0) && (FUN_004702b0(iVar5 + 0x30) >= g_combatAngleThreshold)) {
        bVar1 = false; // Not in combat mode
    }
    
    flags = (uint)this[0x322] >> 2;
    bVar3 = (byte)flags & 1;
    
    // Check conditions to trigger engine stall/restart
    if (((((flags & 1) != 0) || (uStack_94._2_1_ == bVar3)) ||
        (g_stallTimerThreshold <= (float)(uStack_8c & g_stallTimerMask))) || (!bVar1)) {
        this[0x385] = 0; // Reset stall timer
        if ((((flags & 1) != 0) || (uStack_94._2_1_ == bVar3)) ||
           ((FUN_004702b0(this + 0x382) > g_stallTimeThreshold || (!bVar1)))) {
            FUN_008764f0(); // Trigger engine stopped event
        }
    }
    else {
        float timer = (float)this[0x385] + g_frameDelta;
        this[0x385] = (int)timer;
        if ((this[0x377] == 0) && (g_frametime < timer)) {
            FUN_00876710(); // Attempt engine restart
        }
    }
    
    // Update flag based on speed comparison
    if ((float)piStack_88 <= (float)this[0x1ef] * (float)auStack_90) {
        uStack_94 = CONCAT13(1, (uint3)uStack_94);
    }
    
    // Check speed ranges to determine gear shift or engine behavior
    if (((float)this[0x2d5] * (float)auStack_90 < (float)piStack_88) || 
        ((float)piStack_88 <= (float)this[0x2d6] * (float)auStack_90)) {
        // First speed range
        if (((float)this[0x2d6] * (float)auStack_90 < (float)piStack_88) || 
            ((float)piStack_88 <= (float)this[0x2d7] * (float)auStack_90)) {
            // Second speed range
            if ((float)piStack_88 <= (float)this[0x2d7] * (float)auStack_90) {
                // Third speed range (high speed)
                if (this[0x2dc] != 0) {
                    FUN_004df590(); // Stop current effect
                }
                if ((this[0x2de] == 0) && (this[0x2dd] == 0)) {
                    cVar4 = FUN_00414d50(); // Check if can spawn effect
                    if (cVar4 == '\0') {
                        // Spawn engine exhaust effect
                        int transform = FUN_00471610();
                        FUN_0044b4e0(afStack_54, transform); // Get position from transform
                        auStack_90 = (undefined1  [4])0x0;
                        (**(code **)(*this + 0x94))(auStack_90, "BP_engine"); // Get engine bone index
                        ppuStack_84 = (undefined **)(unaff_EBX >> 2); // Unused
                        uStack_80 = (ulonglong)uStack_80._4_4_ << 0x20;
                        uStack_8c = 3; // Effect type?
                        piStack_88 = this;
                        int effectHandle = (**(code **)(*this + 0x58))(0, &uStack_8c); // Create effect
                        effectHandle = FUN_004df270(&uStack_94, this + 0x2bd, &fStack_5c, effectHandle); // Set effect parameters
                        FUN_00414db0(effectHandle); // Apply effect
                        if (uStack_94 != 0) {
                            *(undefined4 *)(uStack_94 + 8) = 0; // Clear some effect data
                        }
                        (**(code **)(*this + 0x2b4))(); // Extra update after spawning
                    }
                    // Random chance to play an audio event
                    FUN_00408680(&g_engineAudio);
                    uStack_8c = _rand();
                    FUN_00440590(&g_engineAudio, this + 0xf, 
                                 (float)(int)uStack_8c * g_randomScale + (float)(int)uStack_8c * g_randomScale, 0, 4);
                    // Check if in over-rev range and play blowback
                    if ((((uint)this[0x322] >> 0xb & 1) != 0) &&
                       (FUN_006b6f90(0x3f800000) < g_backfireThreshold)) {
                        FUN_00542d70(); // Start backfire effect
                        FUN_0086b940(); // Update flame visuals
                    }
                }
                // Handle deceleration timer
                if ((float)this[0x2e1] == g_frametime) {
                    this[0x2e0] = 0;
                    float decelRate = g_decelRateDefault;
                    if ((this[0x2a7] != 0) && (*(int *)(this[0x2a7] + 8) != 0)) {
                        decelRate = g_decelRateModified;
                    }
                    this[0x2e0] = (int)decelRate;
                }
                bVar1 = false;
                this[0x2e1] = (int)((float)this[0x2e1] - g_frameDelta);
                // Check if gear shift needed
                if (((((uint)this[0x322] >> 2 & 1) != 0) &&
                    (int gearRef = (**(code **)(*this + 0x1e4))(); gearRef != 0) &&
                    (cVar4 = (**(code **)(*gearRef + 0x78))(); cVar4 == '\0')) {
                    bVar1 = true; // Indicate gear shift needed
                }
                // Engage gear if conditions met
                if ((float)this[0x2e1] <= g_minShiftTime - (float)this[0x2e0]) &&
                    ((*(byte *)(this + 0x286) & 1) == 0) && (!bVar1)) {
                    uStack_94 = CONCAT13(1, (uint3)uStack_94);
                    if (this[0x2dd] != 0) {
                        FUN_004df590(); // Stop previous effect
                    }
                    FUN_004a52e0(0x39d41d0f, (int)&uStack_94 + 2); // Some shift timing
                    if ((uStack_94._2_1_ == '\0') &&
                       (FUN_0087c4e0(1, this + 0x2c1, 0), ((uint)this[0x286] >> 9 & 1) != 0)) {
                        // Play gear shift sound
                        int transform = FUN_00471610();
                        uStack_80 = *(longlong *)(transform + 0x30);
                        uStack_78 = *(uint *)(transform + 0x38);
                        ppppStack_70 = &ppuStack_84;
                        ppuStack_84 = &PTR_LAB_00d76624;
                        uStack_74 = g_gearShiftSound;
                        uStack_6c = 0;
                        FUN_00408a00(&uStack_74, 0);
                    }
                    if (g_maxEngineNoiseSq < local_64 * local_64) {
                        FUN_004088c0(this + 0xf); // Mute engine sound
                    }
                }
            }
        }
        else {
            // Another speed range (e.g., mid speed)
            if (this[0x2db] != 0) {
                FUN_004df590(); // Stop exhaust effect
            }
            if ((this[0x2dc] == 0) &&
               ((((this[0x2b9] != 0 || this[0x2ba] != 0)) || (this[699] != 0)) ||
                (this[700] != 0))) {
                // Spawn different exhaust effect for mid speed
                int transform = FUN_00471610();
                FUN_0044b4e0(afStack_54, transform);
                auStack_90 = (undefined1  [4])0x0;
                (**(code **)(*this + 0x94))(auStack_90, "BP_engine");
                ppuStack_84 = (undefined **)(unaff_EBX >> 2);
                uStack_80 = (ulonglong)uStack_80._4_4_ << 0x20;
                uStack_8c = 3;
                piStack_88 = this;
                uVar7 = (**(code **)(*this + 0x58))(0, &uStack_8c);
                uVar7 = FUN_004df270(&uStack_8c, this + 0x2b9, afStack_54, uVar7);
                FUN_00414db0(uVar7);
                if (uStack_8c != 0) {
                    *(undefined4 *)(uStack_8c + 8) = 0;
                }
            }
        }
    }
    else if (this[0x2db] == 0) {
        // Low speed range
        if ((((uint)this[0x322] >> 5 & 1) != 0) &&
           (iVar5 = FUN_0084daa0(this, 0x383225a1), iVar5 != 0)) {
            FUN_0087c9f0(0); // Play low speed engine sound
        }
        if (((this[0x2b5] != 0) || (this[0x2b6] != 0)) ||
           ((this[0x2b7] != 0 || (this[0x2b8] != 0)))) {
            // Spawn idle exhaust effect
            int transform = FUN_00471610();
            FUN_0044b4e0(afStack_54, transform);
            auStack_90 = (undefined1  [4])0x0;
            (**(code **)(*this + 0x94))(auStack_90, "BP_engine");
            ppuStack_84 = (undefined **)(unaff_EBX >> 2);
            uStack_80 = (ulonglong)uStack_80._4_4_ << 0x20;
            uStack_8c = 3;
            piStack_88 = this;
            uVar7 = (**(code **)(*this + 0x58))(0, &uStack_8c);
            uVar7 = FUN_004df270(&uStack_8c, this + 0x2b5, afStack_54, uVar7);
            FUN_00414db0(uVar7);
            if (uStack_8c != 0) {
                *(undefined4 *)(uStack_8c + 8) = 0;
            }
        }
    }
    
    // Update deceleration timer
    fVar2 = g_noTimerValue;
    float decelTimer = (float)this[0x2e2];
    if (decelTimer != g_noTimerValue) {
        if (0.0 < decelTimer) {
            this[0x2e2] = (int)(decelTimer - g_frameDelta);
        }
        else {
            this[0x2e3] = g_decelCooldown;
            this[0x2e2] = (int)fVar2;
        }
    }
    
    // Handle engine cool-down timer
    if ((float)this[0x2e3] != fVar2) {
        if (0.0 < (float)this[0x2e3]) {
            FUN_0087a880(); // Play cooling sound?
            FUN_004706f0((float)this[0x2e3] * g_coolDownFactor);
            this[0x2e3] = (int)((float)this[0x2e3] - g_frameDelta);
        }
        else {
            this[0x2e3] = (int)fVar2;
            FUN_004088c0(this + 0xf); // Mute engine
        }
    }
    
    // Check if should trigger engine stall after high rev
    if (((uStack_94._3_1_ == '\x01') && (((uint)this[0x322] >> 0xd & 1) == 0)) &&
       (this[0x2eb] != 0)) {
        this[0x322] = this[0x322] | 0x2000;
        FUN_00877c50(); // Trigger stall
    }
    
    // Handle cyclic engine sound (e.g., low idle)
    if ((((uint)this[0x322] >> 6 & 1) != 0) && (((uint)this[0x322] >> 7 & 1) != 0)) {
        float timer2 = g_cycleTime + (float)this[0x321];
        this[0x321] = (int)timer2;
        if ((float)this[0x28a] <= timer2 && timer2 != (float)this[0x28a]) {
            this[0x321] = 0;
            FUN_0087b5b0(); // Play cyclic sound
            if (((uint)this[0x322] >> 0x15 & 1) != 0) {
                ppuStack_84 = &PTR_FUN_00d6ef98;
                uStack_80 = 0;
                FUN_007393b0(this);
                ppppStack_70 = &ppuStack_84;
                uStack_78 = uStack_78 & 0xffffff00;
                uStack_74 = g_hornSound;
                uStack_6c = 0;
                FUN_00408a00(&uStack_74, 0);
                if ((int)uStack_80 != 0) {
                    FUN_004daf90(&uStack_80); // Clean up horn handle
                }
            }
        }
    }
    return;
}