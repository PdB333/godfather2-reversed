// FUNC_NAME: CharacterAnimationController::handleStateAnimation
void __thiscall SomeClass::handleStateAnimation(int* thisPtr)
{
    int animId1 = thisPtr[0x25];               // +0x94: animation ID (maybe previous)
    char uVar1 = FUN_0076ec60();                // some state or return value
    int localVar6;
    if (**(int**)(DAT_012233a0 + 4) == 0) {
        localVar6 = 0;
    } else {
        localVar6 = **(int**)(DAT_012233a0 + 4) - 0x1f30; // global animation base?
    }

    int currentState = thisPtr[0x22];           // +0x88: current animation state
    if (currentState == 3) {                    // State 3 (e.g., entering vehicle)
        if ((thisPtr[0x17] != 0) && (thisPtr[0x17] != 0x48)) { // +0x5C: some animation index
            int adjustedAnimIdx;
            if (thisPtr[0x17] == 0) {
                adjustedAnimIdx = 0;
            } else {
                adjustedAnimIdx = thisPtr[0x17] - 0x48;
            }
            FUN_0046fd90(adjustedAnimIdx, 0);   // set animation, maybe queue
        }
        if ((*(byte*)(thisPtr + 0x15) & 8) == 0) { // +0x54: bitfield
            FUN_007f4490(1, 0, DAT_00d5ef90);   // debug/log warning
            *(byte*)(thisPtr + 0x15) |= 8;
        }
        (**(code**)(*thisPtr + 0x2c))(0x81cfd529, 1, 1, 0, 0x3f800000, 0x3f800000); // play animation hash
        return;
    }

    if ((currentState == 4) || ((FUN_0084d420(currentState) & 8) != 0)) { // State 4 or bit 3 set
        FUN_0046ffe0(thisPtr + 0x1e, 0);        // reset timer at +0x78
        *(uint*)(thisPtr[0x14] + 0x1b94) |= 8; // set flag in sub-object (+0x50 + 0x1b94)
        if ((*(byte*)(thisPtr + 0x15) & 8) == 0) {
            FUN_007f4490(1, 0, DAT_00d5ef90);
            *(byte*)(thisPtr + 0x15) |= 8;
        }
        (**(code**)(*thisPtr + 0x2c))(0xc996f012, 1, 1, 0, 0x3f800000, 0x3f800000);
        return;
    }

    uint flags = FUN_0084d420(thisPtr[0x22]);
    if ((flags & 0x40) != 0) {                 // bit 6 -> no animation
        return;
    }
    char flagByte = FUN_0084d420(thisPtr[0x22]); // note: same call but cast to char
    if (flagByte < 0) {                        // bit 7 set -> no animation
        return;
    }

    // State not 3 or 4, no high bits, proceed to default logic
    if ((thisPtr[0x19] != 0) && (thisPtr[0x19] != 0x48)) { // +0x64: another animation ID
        int adjustedAnimIdx2;
        if (thisPtr[0x19] == 0) {
            adjustedAnimIdx2 = 0;
        } else {
            adjustedAnimIdx2 = thisPtr[0x19] - 0x48;
        }

        if (((adjustedAnimIdx2 == localVar6) &&                  // matches global animation
            ((FUN_0084d420(thisPtr[0x22]) & 1) != 0)) &&         // bit 0 set
            (FUN_007fd640() == 0) &&                             // some readiness check
            (*(char*)(thisPtr[0x14] + 0x1ec5) != -1 &&          // sub-object slot index
            FUN_00690150(0x66) != 0)) {                          // special condition met
            int subObjSlot = *(int*)(thisPtr[0x14] + 0x1ecc);   // slot count?
            char animIndex = *(char*)(thisPtr[0x14] + 0x1ec5);
            if ((animIndex != -1) && (animIndex < 0x3c) && (subObjSlot < 5)) {
                uint animHash = *(uint*)(&DAT_00d66380 + (animIndex * 0x19 + subObjSlot) * 4);
                (**(code**)(*thisPtr + 0x2c))(animHash, 1, 1, 0, 0x3f800000, 0x3f800000);
                return;
            }
        }
    }

    // Fallback: play default animation
    FUN_0076e860(animId1, uVar1);
    return;
}