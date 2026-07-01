//FUNC_NAME: Character::updateMovement

void __thiscall Character::updateMovement(int *this, float deltaTime)
{
    int *piVar1;
    char cVar2;
    int *piVar3;
    float10 fVar4;
    int *piVar5;
    float fVar6;
    float fVar7;
    char cStack_4a9;
    undefined4 *puStack_4a8;
    int *piStack_4a4;
    int *piStack_4a0;
    int *piStack_49c;
    undefined4 *puStack_498;
    int *piStack_494;
    undefined4 *puStack_490;
    undefined4 *puVar8;
    int *piVar9;
    float fVar10;
    undefined4 *puStack_474;
    int *piStack_470;
    undefined1 auStack_46c [12];
    undefined4 uStack_460;
    undefined4 uStack_45c;
    undefined4 uStack_458;
    undefined4 uStack_454;
    undefined4 uStack_450;
    undefined4 uStack_44c;
    int iStack_448;
    undefined4 uStack_444;
    undefined4 uStack_440;
    undefined4 uStack_43c;
    undefined4 uStack_438;
    undefined4 uStack_434;
    float fStack_430;
    undefined4 uStack_42c;
    undefined4 uStack_428;
    float fStack_424;
    undefined4 uStack_420;
    undefined4 uStack_41c;
    float fStack_418;
    undefined1 auStack_414 [4];
    undefined4 uStack_410;
    float fStack_40c;
    float fStack_3e4;
    float fStack_3e0;
    float fStack_3dc;
    float fStack_3d8;
    float fStack_3d4;
    float fStack_3d0;
    float fStack_3cc;
    float fStack_3c8;
    float fStack_3c4;
    undefined8 uStack_3c0;
    undefined4 uStack_3b8;
    undefined4 uStack_3b4;
    undefined8 uStack_3b0;
    undefined4 uStack_3a8;
    undefined4 uStack_3a4;
    undefined8 uStack_3a0;
    undefined4 uStack_398;
    undefined4 uStack_394;
    undefined4 uStack_390;
    undefined4 uStack_38c;
    undefined4 uStack_388;
    float fStack_384;
    float fStack_380;
    undefined4 uStack_37c;
    undefined4 uStack_378;
    undefined4 uStack_374;
    undefined4 uStack_370;
    undefined4 uStack_36c;
    ulonglong uStack_368;
    undefined4 uStack_360;
    float fStack_35c;
    undefined4 uStack_354;
    undefined4 uStack_350;
    float fStack_344;
    float fStack_340;
    undefined1 auStack_33c [8];
    undefined4 uStack_334;
    undefined4 uStack_328;
    undefined4 uStack_324;
    undefined4 uStack_320;
    undefined4 uStack_31c;
    int iStack_318;
    undefined4 uStack_314;
    undefined4 uStack_310;
    undefined4 uStack_30c;
    undefined4 uStack_308;
    float fStack_304;
    float fStack_300;
    undefined4 uStack_2fc;
    undefined4 uStack_2f8;
    undefined4 uStack_2f4;
    undefined4 uStack_2f0;
    undefined4 uStack_2ec;
    float fStack_2e8;
    undefined4 uStack_2e4;
    undefined4 uStack_2e0;
    undefined4 uStack_2dc;
    int iStack_2d8;
    undefined4 uStack_2d4;
    undefined4 uStack_2d0;
    undefined4 uStack_2cc;
    undefined4 uStack_2c8;
    float fStack_2c4;
    float fStack_2c0;
    undefined4 uStack_2bc;
    undefined4 uStack_2b8;
    float fStack_2b4;
    undefined1 auStack_2b0 [12];
    undefined4 uStack_2a4;
    undefined4 uStack_294;
    float fStack_284;
    undefined4 uStack_274;
    undefined4 uStack_264;
    undefined4 uStack_254;
    float fStack_244;
    undefined2 uStack_240;
    undefined2 uStack_23e;
    undefined4 uStack_23c;
    undefined8 uStack_238;
    undefined8 uStack_230;
    undefined8 uStack_228;
    undefined8 uStack_220;
    undefined1 uStack_218;
    undefined2 uStack_217;
    undefined1 uStack_215;
    undefined1 auStack_214 [12];
    float fStack_208;
    float fStack_204;
    undefined4 uStack_7c;

    // Call virtual pre-update function at vtable+0x2e0
    (**(code **)(*this + 0x2e0))();

    // Check if both enable flags (bit 0) are set
    if (((*(byte *)(this + 0x25c) & 1) != 0) && ((*(byte *)(this + 0x25d) & 1) != 0)) {
        piStack_470 = (int *)((uint)piStack_470 & 0xffffff);
        FUN_007f7450(); // Unknown initialization
        this[0x260] = (int)((float)this[0x260] + deltaTime); // Timer 1
        this[0x25f] = (int)((float)this[0x25f] + deltaTime); // Timer 2

        // Initialize local buffer (likely for bounds or collision)
        uStack_240 = 0x80;
        uStack_23e = 0;
        uStack_23c = 0;
        uStack_238 = 0;
        uStack_230 = 0;
        uStack_228 = 0;
        uStack_220 = 0;
        uStack_218 = 0;
        uStack_217 = 0;
        uStack_215 = 0;
        puStack_490 = (undefined4 *)0x804423;
        _memset(auStack_214, 0, 0x200);
        FUN_007ef530(); // Get some bounds/position data

        // Check if character is outside bounds (X axis)
        if (DAT_01206800 * fStack_208 - (float)this[0x25f] < 0.0) {
            this[0x25c] = this[0x25c] & 0xfffffdff; // Clear bit 9
        }
        // Check if character is outside bounds (Y axis)
        if ((fStack_204 + fStack_208) * DAT_01206800 - (float)this[0x260] < 0.0) {
            this[0x25c] = this[0x25c] & 0xfffffbff; // Clear bit 10
        }

        cVar2 = FUN_00803fa0(); // Check if character is in a special state (e.g., ragdoll)
        if (cVar2 == '\0') {
            this[0x25c] = this[0x25c] | 8; // Set bit 3 (maybe enable physics)
        } else {
            // Compute distance between two points
            fStack_3d8 = fStack_3e4 - fStack_3cc;
            fStack_3d0 = fStack_3dc - fStack_3c4;
            fStack_3d4 = fStack_3e0 - fStack_3c8;
            if (DAT_00e44598 <= SQRT(fStack_3d8 * fStack_3d8 + fStack_3d0 * fStack_3d0 + fStack_3d4 * fStack_3d4)) {
                // Store target position
                *(ulonglong *)(this + 0x261) = CONCAT44(fStack_3e0, fStack_3e4);
                this[0x263] = (int)fStack_3dc;
            }
        }

        // Initialize local vectors with global constants (likely physics state)
        uStack_3a8 = DAT_00d71a7c;
        uStack_398 = DAT_00d71a88;
        uStack_3c0 = DAT_00d71a8c;
        uStack_3b8 = DAT_00d71a94;
        uStack_3b0 = DAT_00d71a74;
        uStack_374 = 0;
        uStack_368 = (ulonglong)(uint)uStack_368;
        uStack_354 = 0;
        fStack_344 = _DAT_00d5780c;
        fStack_2b4 = 0.0;
        uStack_2a4 = 0;
        uStack_294 = 0;
        fStack_284 = _DAT_00d5780c;
        uStack_274 = 0;
        uStack_264 = 0;
        uStack_254 = 0;
        fStack_244 = _DAT_00d5780c;
        uStack_2f4 = 0;
        uStack_2e4 = 0;
        uStack_2d4 = 0;
        fStack_2c4 = _DAT_00d5780c;
        fStack_384 = _DAT_00d5780c;
        uStack_3b4 = 0;
        uStack_3a4 = 0;
        uStack_394 = 0;
        uStack_388 = 0;
        uStack_38c = 0;
        uStack_390 = 0;
        uStack_3a0 = DAT_00d71a80;
        uStack_334 = 0;
        uStack_324 = 0;
        uStack_314 = 0;
        fStack_304 = _DAT_00d5780c;
        puStack_490 = (undefined4 *)0x8046ca;
        (**(code **)(*this + 0x90))(); // Virtual call: copy data from this to local?
        puStack_490 = (undefined4 *)0x1;
        piStack_494 = this + 0x1b8;
        puStack_498 = &uStack_38c;
        piStack_49c = (int *)0x8046e7;
        (**(code **)(*this + 0x90))(); // Another virtual copy
        uStack_368 = CONCAT44(uStack_324, uStack_328);
        piStack_49c = &iStack_448;
        uStack_360 = uStack_320;
        uStack_43c = 0;
        uStack_42c = 0;
        uStack_41c = 0;
        fStack_40c = _DAT_00d5780c;
        piStack_4a0 = (int *)0x80474a;
        FUN_007f3430(); // Initialize a vector/transform
        uStack_398 = iStack_448;
        uStack_394 = uStack_444;
        uStack_390 = uStack_440;
        uStack_38c = uStack_43c;
        uStack_388 = uStack_438;
        fStack_384 = (float)uStack_434;
        fStack_380 = fStack_430;
        uStack_37c = uStack_42c;
        piStack_49c = (int *)0x1;
        piStack_4a0 = this + 0x1bb;
        piStack_4a4 = &iStack_318;
        uStack_378 = uStack_428;
        uStack_374 = fStack_424;
        uStack_370 = uStack_420;
        uStack_36c = uStack_41c;
        uStack_360 = uStack_410;
        fStack_35c = fStack_40c;
        puStack_4a8 = (undefined4 *)0x8047a9;
        (**(code **)(*this + 0x90))(); // Another virtual copy
        puStack_4a8 = &uStack_454;
        iStack_448 = 0;
        uStack_438 = 0;
        uStack_428 = 0;
        fStack_418 = _DAT_00d5780c;
        FUN_007f3430(); // Initialize another vector
        uStack_324 = uStack_454;
        uStack_320 = uStack_450;
        uStack_31c = uStack_44c;
        iStack_318 = iStack_448;
        puStack_4a8 = (undefined4 *)0x1;
        cStack_4a9 = (char)((uint)(this + 0x1ba) >> 0x18);
        uStack_314 = uStack_444;
        uStack_310 = uStack_440;
        uStack_30c = uStack_43c;
        uStack_308 = uStack_438;
        fStack_304 = (float)uStack_434;
        fStack_300 = fStack_430;
        uStack_2fc = uStack_42c;
        uStack_2f8 = uStack_428;
        uStack_2f4 = fStack_424;
        uStack_2f0 = uStack_420;
        uStack_2ec = uStack_41c;
        fStack_2e8 = fStack_418;
        (**(code **)(*this + 0x90))(&uStack_2e4); // Copy to local
        uStack_454 = 0;
        uStack_444 = 0;
        uStack_434 = 0;
        fStack_424 = _DAT_00d5780c;
        FUN_007f3430(&uStack_460); // Initialize another vector
        uStack_2f0 = uStack_460;
        uStack_2ec = uStack_45c;
        fStack_2e8 = (float)uStack_458;
        uStack_2e4 = uStack_454;
        uStack_2e0 = uStack_450;
        uStack_2dc = uStack_44c;
        iStack_2d8 = iStack_448;
        uStack_2d4 = uStack_444;
        uStack_2d0 = uStack_440;
        uStack_2cc = uStack_43c;
        uStack_2c8 = uStack_438;
        fStack_2c4 = (float)uStack_434;
        fStack_2c0 = fStack_430;
        uStack_2bc = uStack_42c;
        uStack_2b8 = uStack_428;
        fStack_2b4 = fStack_424;
        (**(code **)(*this + 0x90))(auStack_2b0, this + 0x1b9, 1); // Copy from this to local
        FUN_0056c180(auStack_33c, &piStack_4a4, &puStack_4a8, &piStack_4a0); // Vector operation
        piStack_470 = piStack_4a4;
        puStack_490 = puStack_4a8;
        FUN_0056c180(&uStack_2bc, &piStack_4a4, &puStack_4a8, &piStack_4a0); // Another vector op
        piVar3 = piStack_4a4;
        puStack_498 = puStack_4a8;
        FUN_0056c180(&uStack_2f0, &piStack_4a4, &puStack_4a8, &piStack_4a0); // Another
        piStack_494 = piStack_4a4;
        puVar8 = puStack_4a8;
        FUN_0056c180((int)&uStack_3c0 + 4, &piStack_4a4, &puStack_4a8, &piStack_4a0); // Another
        piVar1 = piStack_4a4;
        puStack_474 = puStack_4a8;
        piVar5 = piStack_4a4;

        // If character has a vehicle (this[0x6f2] != 0)
        if (this[0x6f2] != 0) {
            fVar4 = (float10)FUN_0056aee0((float)piStack_4a4 - (float)piStack_470, DAT_00d5d70c);
            piStack_49c = (int *)(float)fVar4;
            fVar4 = (float10)FUN_0056aee0((float)puStack_474 - (float)puStack_490, DAT_00d5d70c);
            FUN_007efff0(piStack_49c, (float)fVar4);
            fVar4 = (float10)FUN_0056aee0((float)piStack_494 - (float)piVar3, DAT_00d5d70c);
            piStack_49c = (int *)(float)fVar4;
            piVar5 = (int *)((float)puVar8 - (float)puStack_498);
            fVar4 = (float10)FUN_0056aee0(piVar5, DAT_00d5d70c);
            FUN_007f0010(piStack_49c, (float)fVar4);
        }

        FUN_007f6c40(piStack_470, puStack_490, puStack_474); // Physics integration
        piStack_470 = piVar5;
        FUN_007f6c40(piVar3, puStack_498, puVar8); // Another integration

        if (cVar2 != '\0') {
            FUN_007f72b0(auStack_33c, &uStack_2bc); // Apply ragdoll forces?
        }

        piVar3 = this + 0x1c7;
        // Determine which movement mode to use based on flags
        if ((((uint)this[0x25c] >> 3 & 1) == 0) || (((uint)this[0x25d] >> 3 & 1) == 0)) {
            if (this[0x60] != 0) {
                piVar3 = (int *)&DAT_00d71b88; // Use alternative movement parameters
            }
        } else {
            piVar3 = (int *)&DAT_00d71b40; // Use ragdoll movement parameters
            cStack_4a9 = '\x01';
        }

        fVar6 = _DAT_00d5780c; // Default zero
        // Check if bit 2 is set (maybe sprint/run)
        if ((((uint)this[0x25c] >> 2 & 1) != 0) && (((uint)this[0x25d] >> 2 & 1) != 0)) {
            fVar6 = (DAT_00d71b08 - (float)this[0x25e]) * _DAT_00d5ca64;
            if (fVar6 <= 0.0) {
                FUN_007f7050(); // Reset or handle exhaustion
            }
            this[0x25e] = (int)((float)this[0x25e] + deltaTime); // Increment stamina timer
        }

        puStack_498 = (undefined4 *)uStack_230._4_4_;
        // Check bit 11 (maybe special action)
        if ((((uint)this[0x25c] >> 0xb & 1) != 0) && (((uint)this[0x25d] >> 0xb & 1) != 0)) {
            puStack_498 = (undefined4 *)uStack_7c;
        }

        FUN_007fc2c0(deltaTime, (int)&uStack_3c0 + 4, piVar3, fVar6, puStack_498,
                     _DAT_00d5780c - (float)uStack_228); // Main movement update

        puStack_498 = (undefined4 *)DAT_00d5d7b8;
        fVar10 = DAT_00d5d7b8;
        // If in vehicle and bit 22 of this[0x6e5] is set
        if ((this[0x6f2] != 0) && (((uint)this[0x6e5] >> 0x16 & 1) != 0)) {
            FUN_007f6d00(this[0x6f2] + 0x100, &puStack_474, &stack0xfffffb80);
            FUN_007f6d00(this[0x6f2] + 0x130, &stack0xfffffb74, &piStack_494);
            fVar4 = (float10)FUN_007f0900();
            fVar10 = (float)fVar4;
            fVar4 = (float10)FUN_007f1370();
            puStack_498 = (undefined4 *)(float)fVar4;
            if (0.0 < (float)this[0x1eb]) {
                puStack_498 = (undefined4 *)((float)this[0x1ed] * (float)puStack_498);
                fVar10 = (float)this[0x1ed] * fVar10;
            }
        }

        if (cStack_4a9 == '\0') {
            // Normal movement path
            uStack_370 = 0;
            uStack_360 = 0;
            uStack_350 = 0;
            fStack_340 = _DAT_00d5780c;
            uStack_460 = 0;
            uStack_450 = 0;
            uStack_440 = 0;
            fStack_430 = _DAT_00d5780c;
            FUN_007f69a0(&uStack_37c, (int)&uStack_3c0 + 4, auStack_414);
            FUN_007f69a0(auStack_46c, auStack_33c, auStack_414);
            FUN_0056c180(&uStack_37c, &piStack_4a4, &puStack_4a8, &piStack_4a0);
            piVar9 = piStack_4a4;
            puVar8 = puStack_4a8;
            FUN_0056c180(auStack_46c, &piStack_4a4, &puStack_4a8, &piStack_4a0);
        } else {
            // Ragdoll movement path
            FUN_0056c180((int)&uStack_3c0 + 4, &piStack_4a4, &puStack_4a8, &piStack_4a0);
            piVar9 = piStack_4a4;
            puVar8 = puStack_4a8;
            FUN_0056c180(&uStack_2fc, &piStack_4a4, &puStack_4a8, &piStack_4a0);
        }

        piStack_49c = piStack_4a4;
        // Check bit 9 (maybe disable horizontal movement)
        if ((((uint)this[0x25c] >> 9 & 1) == 0) || (((uint)this[0x25d] >> 9 & 1) == 0)) {
            FUN_007f68a0(puStack_490, puStack_474, puVar8, deltaTime, fVar10, piVar3, this + 0x264);
            FUN_007f67b0(piStack_470, piVar1, piVar9, deltaTime, fVar10, piVar3, this + 0x264);
        }
        // Check bit 10 (maybe disable vertical movement)
        if ((((uint)this[0x25c] >> 10 & 1) == 0) || (((uint)this[0x25d] >> 10 & 1) == 0)) {
            FUN_007f67b0(piVar5, piStack_494, piStack_49c, deltaTime, puStack_498, piVar3 + 3, this + 0x268);
        }

        fVar10 = DAT_00d5833c;
        if (cStack_4a9 != '\0') {
            // Scale velocities for ragdoll
            this[0x264] = (int)((float)this[0x264] * DAT_00d5833c);
            this[0x268] = (int)((float)this[0x268] * fVar10);
            this[0x266] = (int)((float)this[0x266] * fVar10);
            this[0x26a] = (int)((float)this[0x26a] * fVar10);
        }

        puStack_490 = (undefined4 *)0x0;
        piStack_49c = (int *)0x0;
        fVar10 = 0.0;
        if (this[0x6f2] != 0) {
            // Vehicle-specific forces
            if ((((uint)this[0x25c] >> 5 & 1) == 0) || (((uint)this[0x25d] >> 5 & 1) == 0)) {
                fVar4 = (float10)FUN_007f0860();
                fVar10 = (float)fVar4;
                FUN_007f08b0();
            }
            if ((((uint)this[0x25c] >> 6 & 1) == 0) || (((uint)this[0x25d] >> 6 & 1) == 0)) {
                fVar4 = (float10)FUN_007f07c0();
                puStack_490 = (undefined4 *)(float)fVar4;
                fVar4 = (float10)FUN_007f0810();
                piStack_49c = (int *)(float)fVar4;
            }
        }

        fVar7 = _DAT_00d5780c;
        piStack_494 = (int *)this[0x266];
        // Clamp velocity component
        if ((float)piStack_494 <= DAT_00d5f00c) {
            if ((float)piStack_494 < DAT_00e446a0) {
                piStack_494 = (int *)(DAT_00e44588 - (float)piStack_494);
            }
        } else {
            piStack_494 = (int *)(DAT_00d5eeec - (float)piStack_494);
        }

        // Check if character is not in ragdoll (byte at vehicle+0x5e2)
        if (*(char *)(this[0x6f2] + 0x5e2) == '\0') {
            if (this[0x3f5] == 0) {
                // Zero out all velocity/force components
                this[0x264] = 0;
                this[0x268] = 0;
                this[0x265] = 0;
                this[0x269] = 0;
                this[0x266] = 0;
                this[0x26a] = 0;
                this[0x267] = 0;
                this[0x26b] = 0;
                this[0x27e] = 0;
                this[0x27d] = 0;
                this[0x27c] = 0;
                this[0x27f] = (int)fVar7;
                this[0x282] = 0;
                this[0x281] = 0;
                this[0x280] = 0;
                this[0x283] = (int)fVar7;
                this[0x286] = 0;
                this[0x285] = 0;
                this[0x284] = 0;
                this[0x287] = (int)fVar7;
                return;
            }
        } else {
            // Ragdoll blending
            fVar4 = (float10)FUN_007ef4c0();
            piStack_49c = (int *)((float)piStack_494 * (float)piStack_49c);
            FUN_0056d370(0, (float)((float10)(float)this[0x264] * (float10)(float)puStack_490 * fVar4 * (float10)fVar6),
                         (float)piStack_49c * (float)fVar4 * fVar6, this + 0x27c);
            fVar7 = _DAT_00d5780c - (float)fVar4;
            FUN_0056d370(0, (float)this[0x264] * (float)puStack_490 * fVar7 * fVar6,
                         (float)piStack_49c * fVar7 * fVar6, this + 0x280);
            FUN_0056d370(0, (float)this[0x268] * fVar10 * fVar6, 0, this + 0x284);
        }
    }
    return;
}