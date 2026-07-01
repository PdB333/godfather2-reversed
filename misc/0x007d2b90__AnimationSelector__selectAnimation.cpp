// FUNC_NAME: AnimationSelector::selectAnimation

void __thiscall AnimationSelector::selectAnimation(AnimationSelector* thisPtr, int interpolateFlag, float speed)
{
    // Bitfield extraction from the character state structure at offset +0x8e0, +0x8e4, +0x8e8, +0x249c
    uint stateFlags0 = *(uint*)(thisPtr->stateField[0x16] + 0x8e0);  // +0x8e0: movement/action flags
    uint stateFlags1 = *(uint*)(thisPtr->stateField[0x16] + 0x8e4);  // +0x8e4: combat/cover flags
    uint stateFlags2 = *(uint*)(thisPtr->stateField[0x16] + 0x8e8);  // +0x8e8: additional flags
    uint miscFlags   = *(uint*)(thisPtr->stateField[0x16] + 0x249c); // +0x249c: miscellaneous flags

    bool isAiming = (stateFlags0 >> 1) & 1;        // bit 1 of 0x8e0
    bool isInCover = (stateFlags1 >> 8) & 1;       // bit 8 of 0x8e4
    bool isShooting = (stateFlags1 >> 5) & 1 ||
                      (stateFlags1 >> 6) & 1 ||
                      (stateFlags1 >> 7) & 1 ||
                      (stateFlags1 >> 9) & 1;
    bool isInVehicle = (miscFlags >> 0x17) & 1;   // bit 23 of 0x249c
    bool isInVehicle2 = (miscFlags >> 0x18) & 1;  // bit 24 of 0x249c
    bool isInCover2 = (stateFlags2 >> 1) & 1;     // bit 1 of 0x8e8
    bool isSprinting = (stateFlags2 >> 0xc) & 1;  // bit 12 of 0x8e8
    bool isRunning = (stateFlags2 >> 0xd) & 1;    // bit 13 of 0x8e8

    uint animHash = 0;
    bool forceNewAnimation = false;
    bool animationChanged = false;

    // If not interpolating and aiming, stop certain animations
    if (!isAiming || interpolateFlag != 0) {
        stopAnimation(0x4c);  // Animation ID 76
        stopAnimation(0x4d);  // Animation ID 77
    } else if (inCover) {
        forceNewAnimation = true;
    }

    // If character is shooting, stop animations
    if (isShooting) {
        stopAnimation(0x4c);
        stopAnimation(0x4d);
    }

    bool isSpecialState = false;
    if (isInVehicle || (stateFlags0 >> 9) & 1 || isInVehicle2) {
        isSpecialState = true;
    }

    int movementMode = getMovementMode();  // FUN_007ab1f0
    int stance = getCharacterStance();      // FUN_007ab220

    if (movementMode == 0) {
        // Movement mode 0 (probably standing/walking)
        if ((!isInCover || (thisPtr->state[0x30] != 4 && thisPtr->state[0x30] != 3))) {
            if (stance == 4 || ( isInCover && thisPtr->state[0x30] == 2)) {
                // Stance 4: maybe cover low? or combat stance
                animHash = *(&DAT_00e531b0 + (interpolateFlag + (uint)isAiming * 5) * 4);
                thisPtr->state[0x30] = 2;  // state 2
            } else if (stance == 3 ||
                       ( isInCover && thisPtr->state[0x30] == 1) ||
                       (thisPtr->stateField[0x16] + 0x74c != 0 && *(int*)(thisPtr->stateField[0x16] + 0x74c) != 0x48) ||
                       isCharacterInVehicle() || isWeaponDrawn()) {
                animHash = *(&DAT_00e53188 + (interpolateFlag + (uint)isAiming * 5) * 4);
                thisPtr->state[0x30] = 1;  // state 1 (walking)
            } else {
                animHash = *(&DAT_00e53160 + (interpolateFlag + (uint)isAiming * 5) * 4);
                thisPtr->state[0x30] = 0;  // state 0 (idle)
            }
            goto LAB_007d30c8;
        }
        // Fall through to LAB_007d2db5
    } else {
        // Movement mode != 0 (maybe running or combat movement)
        int moveId = getMovementModeId();  // FUN_00701050
        if (moveId == 2 || moveId == 3 || moveId == 4) {
            // Movement modes 2,3,4: probably run, sprint, climb?
            goto LAB_007d2de2;
        }
        // Else fall through to LAB_007d2db5
    }

    // LAB_007d2db5: State when movement mode 0 but in cover state 4 or 3, or other modes not in 2-4
    if (isInCover && thisPtr->state[0x30] == 4) {
        goto LAB_007d2de2;
    }

    if (forceNewAnimation) {
        animHash = 0x5a159c2c;  // Some forced animation hash
    } else if (!isAiming) {
        if (!isInCover2) {
            if (!isSpecialState) {
                animHash = *(&DAT_00e53070 + (interpolateFlag + (uint)isAiming * 5) * 4);
            } else {
                animHash = *(&DAT_00e530ac + interpolateFlag * 4);
            }
        } else { // isInCover2
            if (isSpecialState) {
                animHash = *(&DAT_00e530c0 + interpolateFlag * 4);
            } else {
                animHash = *(&DAT_00e53098 + interpolateFlag * 4);
            }
        }
    } else { // isAiming
        if (isSpecialState || (stateFlags1 & 0x100) != 0 || (stateFlags1 >> 9 & 1)) {
            animHash = *(&DAT_00e530fc + interpolateFlag * 4);
        } else {
            animHash = *(&DAT_00e53070 + (interpolateFlag + (uint)isAiming * 5) * 4);
        }
    }
    thisPtr->state[0x30] = 3;  // state 3

    // LAB_007d2de2: For movement modes 2,3,4 or forced cover state
    animHash = 0; // reset
    if (forceNewAnimation) {
        animHash = 0x6963fe0b;
        thisPtr->state[0x30] = 4;  // state 4 (cover/combat)
    } else if (!isAiming) {
        if (!isInCover2) {
            if (!isSpecialState) {
                animHash = *(&DAT_00e53124 + interpolateFlag * 4);
                thisPtr->state[0x30] = 4;
            } else {
                animHash = *(&DAT_00e5314c + interpolateFlag * 4);
                thisPtr->state[0x30] = 4;
            }
        } else { // isInCover2
            if (isSpecialState) {
                animHash = *(&DAT_00e53138 + interpolateFlag * 4);
                thisPtr->state[0x30] = 4;
            } else {
                animHash = *(&DAT_00e53138 + interpolateFlag * 4);  // likely same as above
                thisPtr->state[0x30] = 4;
            }
        }
    } else { // isAiming
        if (isSpecialState || (stateFlags1 & 0x100) || (stateFlags1 >> 9 & 1)) {
            animHash = *(&DAT_00e53110 + interpolateFlag * 4);
            thisPtr->state[0x30] = 4;
        } else {
            animHash = *(&DAT_00e530d4 + (interpolateFlag + (uint)isAiming * 5) * 4);
            thisPtr->state[0x30] = 4;
        }
    }

    // Check for running/sprinting transitions
    if ((stateFlags2 >> 0xd & 1) && ((stateFlags2 >> 0xc & 1) == 0)) {
        // Running animation check
        if ((!isAnimationPlaying(0x13765508) || isAnimationFinished()) &&
            (!isAnimationPlaying(0x224f1da7) || isAnimationFinished())) {
            animationChanged = true;
            int moveId = getMovementModeId();
            if (moveId != 2 && moveId != 3 && moveId != 4) {
                animHash = 0x224f1da7;
                goto LAB_007d2fc1;
            }
            animHash = 0x13765508;
        } else {
            stopAnimation(0x4d); // stop running animation
        }
    }

    // Check for sprinting transition
    if ((stateFlags2 >> 0xc & 1) && ((stateFlags1 >> 8 & 1) == 0)) {
        if ((!isAnimationPlaying(0x88b50d47) || isAnimationFinished()) &&
            (!isAnimationPlaying(0xeb7aae8) || isAnimationFinished())) {
            animationChanged = true;
            int moveId = getMovementModeId();
            if (moveId == 2 || moveId == 3 || moveId == 4) {
                animHash = 0x88b50d47;
                forceNewAnimation = false;
            } else {
                moveId = getMovementModeId();
                if (moveId == 1) {
                    animHash = 0xeb7aae8;
                    forceNewAnimation = false;
                }
            }
        } else {
            stopAnimation(0x4c); // stop sprint?
            forceNewAnimation = true;
        }
    }

    // Check if any specific animation is playing that overrides
    if ((isAnimationState(0x77c66174, 0) ||
         isAnimationState(0x7ce0253, 0) ||
         isAnimationState(0x1652518c, 0)) &&
        (!forceNewAnimation && (stateFlags1 >> 8 & 1))) {
        animationChanged = true;
        startAnimation(0x4c); // start blocking animation?
    }

LAB_007d30c8:
    updateAnimations(); // FUN_0045eea0 (possibly flush/commit)

    // Find a non-zero pointer? Not sure
    int* globalPtr = &DAT_00d6eeb4;
    while (*globalPtr != 0) {
        globalPtr++;
    }

    int* statePtr = (int*)thisPtr->stateField[0x16];

    if (animationChanged) {
        // Call vfunc 0x234 (0x234/4 = 0x8D) with (0,0) - maybe set movement state?
        (thisPtr->vtable[0x234])(0, 0);
        startAnimation(0x58); // start animation 88
    } else if ((*(byte*)(statePtr + 0x8eb) & 1) != 0) {
        int param;
        if ((statePtr[0x238] >> 1 & 1) == 0) {
            param = 0;
        } else {
            param = 4;
        }
        // Call vfunc 0x234 with (param, 1)
        (thisPtr->vtable[0x234])(param, 1);
    }

    float animSpeed = _DAT_00d5780c;
    if (interpolateFlag != 0) {
        if (isSpecialState) {
            if (!isAiming) {
                speed = DAT_00e53050 * speed;
                animSpeed = (float)DAT_00e53054;
            } else {
                speed = DAT_00e53060 * speed;
                animSpeed = (float)DAT_00e53064;
            }
        } else if (!isAiming) {
            speed = DAT_00e53068 * speed;
            animSpeed = (float)DAT_00e5306c;
        } else {
            speed = DAT_00e53058 * speed;
            animSpeed = (float)DAT_00e5305c;
        }
    }

    // If character is in some state (flags at +0x24f8 or +0x249c sign)
    if (*(int*)(thisPtr->stateField[0x16] + 0x24f8) != 0 ||
        *(int*)(thisPtr->stateField[0x16] + 0x249c) >= 0) {
        // Call vfunc 0x2c (0x2c/4 = 0xB) with animation hash, layer, etc.
        (thisPtr->vtable[0x2c])(animHash, 1, 0, 0, speed, animSpeed);
    }

    // Call vfunc 0x164 (0x164/4 = 0x59) - finalize update
    (thisPtr->stateField[0x16]->vtable[0x164])();

    return;
}