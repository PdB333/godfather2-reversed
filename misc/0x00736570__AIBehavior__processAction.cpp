// FUNC_NAME: AIBehavior::processAction

int __thiscall AIBehavior::processAction(int *this, int *actionData) {
    int tempInt;
    bool isSpecialAction;
    char result1, result2;
    int *owner;
    int tempInt2;
    int eventHash1, eventHash2, eventHash3;
    float floatTemp;
    int localArray[5]; // used for hash/event ID
    bool flag = false;

    // Check if actionData->owner is null or is some sentinel value 0x48 (likely 'NoOwner')
    if ((*(int *)(actionData + 0xc) == 0) || (*(int *)(actionData + 0xc) == 0x48)) {
LAB_007365c7:
        // Additional check: if owner is not null and not sentinel, and some global state is valid
        if ((*(int *)(actionData + 0xc) != 0) &&
            (((((*(int *)(actionData + 0xc) != 0x48 && (*(int *)(actionData + 0xc) != 0)) &&
               (*(int *)(actionData + 0xc) != 0x48)) &&
              ((tempInt2 = FUN_0043b870(DAT_01131040), tempInt2 != 0 && (*(int *)(tempInt2 + 0x1c) != 0)))) &&
             (*(int *)(tempInt2 + 0x1c) != 0x48)))) {
            // Get owner from actionData
            if (*(int *)(actionData + 0xc) == 0) {
                owner = (int *)0x0;
            } else {
                owner = (int *)(*(int *)(actionData + 0xc) - 0x48);
            }
            // If owner is not this and there is a global persistent object valid and not sentinel
            if (((owner != this) && (tempInt2 = **(int **)(DAT_012233a0 + 4), tempInt2 != 0)) &&
               (tempInt2 != 0x1f30)) {
                // Multiply actionData->speedMultiplier by some global speed factor
                *(float *)(actionData + 0x2c) = *(float *)(tempInt2 + 0x210) * *(float *)(actionData + 0x2c);
            }
        }
    } else {
        // If owner is not null and not sentinel, compute owner pointer and check some special action hash
        if (*(int *)(actionData + 0xc) == 0) {
            owner = (int *)0x0;
        } else {
            owner = (int *)(*(int *)(actionData + 0xc) - 0x48);
        }
        localArray[0] = 0;
        result1 = (**(code **)(*owner + 0x10))(0x383225a1, localArray); // Virtual call: isActionAllowed?
        if ((result1 == '\0') || (localArray[0] == 0)) goto LAB_007365c7;
        flag = true; // This action is 'special' (bVar2)
    }

    // Check if actionData->flags bit 5 is set (some disable flag)
    if ((*(uint *)(actionData + 0x44) >> 5 & 1) == 0) {
        // Determine audio event hashes based on state
        eventHash1 = 0xe58bc9a;
        localArray[0] = 0xe58bc9a;
        if (*(int *)(actionData + 0x30) == 2) { // state 2: maybe 'reaction' or 'hit'
            eventHash1 = 0x84a42d75;
            localArray[0] = -0x7b5bd28b;
        }

        // If this->flags bit 5 (maybe some powerup) is set, clear audio
        if (((uint)this[0x7d7] >> 5 & 1) != 0) {
            eventHash1 = 0;
            localArray[0] = 0;
            if (*(int *)(actionData + 0x30) == 2) {
                localArray[0] = 0;
            }
        }

        result1 = '\0';
        tempInt = FUN_00806440(); // get game mode
        if ((tempInt == 2) && // Mode 2: maybe multiplayer?
           (((*(uint *)(DAT_0112aa1c + 0x2c6c) >> 7 & 1) != 0 || // global flags
            ((*(int *)(DAT_0112aa1c + 0x2c88) != 0 && (result2 = FUN_00784770(), result2 != '\0')))))) {
            // In multiplayer, clear audio hashes
            eventHash1 = 0;
            localArray[0] = 0;
            if (flag) {
                // Special action: random chance to play a taunt animation
                tempInt = _rand();
                if (tempInt % 100 < 0x21) { // 33% chance
                    eventHash3 = 0;
                    eventHash2 = FUN_006fbc40(0, 0); // get animation handle
                    result1 = FUN_007f96a0(0, 0, eventHash2, eventHash3); // play animation
                    FUN_006fbc70(); // end animation?
                }
            } else if (*(int *)(actionData + 0x30) == 2) {
                eventHash1 = 0;
                localArray[0] = 0;
            }
        }

        if (((*(int *)(actionData + 0x30) == 1) && (result2 = FUN_007f7b90(), result2 == '\0')) &&
           (result1 == '\0')) {
            // State 1: typical action, check owner state
            if (*(int *)(actionData + 0xc) == 0) {
                tempInt = 0;
            } else {
                tempInt = *(int *)(actionData + 0xc) - 0x48;
            }
            result1 = FUN_0072f180(tempInt); // check if owner is alive/valid?
            if (result1 != '\0') {
                eventHash1 = 0;
                tempInt = _rand();
                if (tempInt % 100 < 0x21) {
                    eventHash3 = 0;
                    eventHash2 = FUN_006fbc40(0, 0);
                    result1 = FUN_007f96a0(0, 0, eventHash2, eventHash3);
                    FUN_006fbc70();
                    if (result1 != '\0') goto LAB_007368ff;
                }
            }
            // Check again with maybe a different owner?
            if (*(int *)(actionData + 0xc) == 0) {
                tempInt = 0;
            } else {
                tempInt = *(int *)(actionData + 0xc) - 0x48;
            }
            result1 = FUN_0072f180(tempInt);
            if (result1 != '\0') {
                // Check global persistent object
                if (**(int **)(DAT_012233a0 + 4) == 0) {
                    tempInt = 0;
                } else {
                    tempInt = **(int **)(DAT_012233a0 + 4) - 0x1f30;
                }
                result1 = FUN_0072f180(tempInt);
                if (result1 != '\0') {
                    eventHash3 = 0;
                    eventHash2 = FUN_006fbc40(0, 0);
                    if (flag) {
                        eventHash1 = 0x1349237c;
                    } else {
                        eventHash1 = 0xe05a2c06;
                    }
                    result1 = FUN_007f96a0(eventHash1, 0, eventHash2, eventHash3);
                    FUN_006fbc70();
                    if (result1 != '\0') goto LAB_007368ff;
                }
            }

            // If not a special action, or if special action but not allowed, play an audio event
            if ((!flag) || (result1 = (**(code **)(*this + 0x1bc))(), result1 == '\0')) {
                eventHash2 = 0x62ddb8d;
                eventHash3 = 0x3f95bf;
                if (((uint)this[0x7d7] >> 5 & 1) != 0) {
                    eventHash2 = 0x528ebb94;
                    eventHash3 = 0x28cc0ac6;
                }
                FUN_0072cd00(eventHash1, eventHash2, eventHash3); // play sound/music
            }
        } else if (*(int *)(actionData + 0x30) == 2) {
            // State 2: maybe 'hit' or 'reaction'
            if ((*(int *)(actionData + 0xc) != 0) && (tempInt = *(int *)(actionData + 0xc) - 0x48, tempInt != 0)) {
                eventHash1 = FUN_00806460(); // get current state
                result1 = FUN_0043c6c0(tempInt, eventHash1); // check condition
                if (result1 != '\0') {
                    localArray[0] = 0;
                }
            }
            if ((!flag) || (result1 = (**(code **)(*this + 0x1bc))(), result1 == '\0')) {
                eventHash1 = 0x9c0404e8;
                eventHash2 = 0xcc4460a4;
                if (((uint)this[0x7d7] >> 5 & 1) != 0) {
                    eventHash1 = 0xc8da2c6f;
                    eventHash2 = 0x23692e2b;
                }
                FUN_0072cd00(localArray[0], eventHash1, eventHash2);
            }
        } else if ((*(int *)(actionData + 0x30) == 3) && // State 3: maybe 'block' or 'guard'
                  (floatTemp = (float10)(**(code **)(*this + 0xc0))(), (float10)0 < floatTemp)) {
            // Play a generic animation if something positive
            eventHash2 = 0;
            eventHash1 = FUN_006fbc40(0, 0);
            FUN_007f96a0(0, 0, eventHash1, eventHash2);
            FUN_006fbc70();
        }
    }

LAB_007368ff:
    // Check this->flags bit 0x400 (bit 11) - maybe some forbidden state
    if (((uint)this[0x23a] >> 0xb & 1) != 0) {
        if (*(int *)(actionData + 0x30) != 10) { // State 10: maybe 'interruptible'
            return 3; // Block action
        }
        this[0x863] = this[0x863] | 0x1000000; // Set some flag
        return 3;
    }

    // Check another flag (bits 4 and 8? 0x10c = 0x100 + 0xC? Actually 0x10c = 268 -> bits: 2,3,8? Better: 0x10c = 0x100|0xC -> bits 2,3,8? Hmm)
    if ((this[0x7e6] & 0x10cU) == 0) {
        if ((*(byte *)((int)this + 0x8e6) & 1) != 0) {
            return 2;
        }
    } else {
        if (!flag) {
            // Non-special action: check if owner is null or sentinel
            if ((*(int *)(actionData + 0xc) == 0) || (*(int *)(actionData + 0xc) == 0x48)) {
                return 2;
            }
            if (*(int *)(actionData + 0xc) == 0) {
                tempInt = 0;
            } else {
                tempInt = *(int *)(actionData + 0xc) - 0x48;
            }
            tempInt = FUN_0072dc40(tempInt, 0xf26bb307); // check ability?
            if (tempInt == 0) {
                return 2;
            }
            goto LAB_007369ca;
        }
        // Special action: check something
        result1 = FUN_0071fa50(); // is player controlled?
        if ((result1 == '\0') && (*(int *)(actionData + 0x30) == 1)) {
            FUN_00402050(&DAT_0112ad9c, 0); // set global flag
        }
    }

    if (flag) {
        this[0x7d7] = this[0x7d7] & 0xfffffbff; // Clear bit 10? (0x400)
    }

LAB_007369ca:
    // Check some virtual function results
    floatTemp = (float10)(**(code **)(*this + 0xc4))(); // get float
    if (floatTemp != (float10)0) {
        (**(code **)(*this + 0xc0))(); // set something
        (**(code **)(*this + 0xc4))(); // get something again
    }

    // Check this->flags bit 0x200000 (bit 21)
    if (((uint)this[0x7d5] >> 0x15 & 1) != 0) {
        return 3;
    }

    // Update animation? and check movement state
    FUN_00733ac0(actionData);
    tempInt = FUN_008001e0(actionData); // movement state (2 = something)
    if ((((((tempInt != 2) && (*(int *)(actionData + 0x30) == 1)) && // if not moving and action state 1
          (result1 = FUN_00690150(6), result1 != '\0')) && // check some global condition
         (((tempInt2 = **(int **)(DAT_012233a0 + 4), tempInt2 != 0 && (tempInt2 != 0x1f30)) &&
          ((flag && ((tempInt2 = FUN_007ff880(), tempInt2 == 0 && (result1 = FUN_004209a0(), result1 != '\0'))))
          ))))) && (result1 = FUN_0072c080(1), result1 == '\0') && // check random chance
         (((tempInt2 = FUN_00691810(), tempInt2 != 0 && (((uint)this[0x238] >> 10 & 1) != 0)) &&
          (tempInt2 = _rand(), (float)(tempInt2 % 100) < *(float *)(tempInt2 + 0x228) * DAT_00d5e288)))) {
        // Start a special animation
        FUN_007338c0(actionData, 1);
    }

    // Check another set of flags
    if (((((uint)this[0x238] >> 0x11 & 1) != 0) || (((uint)this[0x238] >> 0x10 & 1) != 0)) &&
       ((tempInt != 2 && (((char)this[0x6e3] != '\0' && (this[0x7b5] == 0x637b907)))))) {
        tempInt = 3;
    }

    return tempInt;
}