// FUNC_NAME: StateMachine::processStateMachine

void __thiscall StateMachine::processStateMachine(void) {
    byte stateFlags;
    int randVal;
    uint randBits;

    // Read current state byte from the state array pointer at +0x4C
    stateFlags = **(byte **)(this + 0x4C);   // this->currentStateData pointer
    if ((stateFlags & 1) == 0) {
        if ((stateFlags & 2) == 0) {
            if ((stateFlags & 0x40) == 0) goto LAB_00580111;
            // State bit 6 set: update timer at +0x58
            *(int *)(this + 0x58) += 9;      // e.g., steeringTimer
        }
        else {
            // State bit 1 set: use random to decide timing
            randVal = rand();  // __aullshr(); // generated random value
            randBits = randVal & 3;
            if (randBits > 2) {   // if (randBits & 3) == 0? Actually condition: (randBits - 1) > 2 is true only for randBits==0 due to unsigned wrap
                // Two additional calls? Probably to randomize further
                randomizeTimer();
                randomizeTimer();
            }
            randomizeTimer();
        }
        // Common updates for bits 1 or 6 branch: timer at +8, counter at +0x10
        *(int *)(this + 8) += 6;
        *(int *)(this + 0x10) += 1;
    }
    else {
        // State bit 0 set: different timers
        *(int *)(this + 0x14) += 6;
        *(int *)(this + 0x18) += 1;
    }

LAB_00580111:
    // Re-read state? Actually the same byte pointer is dereferenced again
    stateFlags = **(byte **)(this + 0x4C);
    if ((stateFlags & 0x1C) == 0) {   // bits 2,3,4 not set
        if ((stateFlags & 0x20) == 0) { // bit5 not set
            // Default idle state: advance pointer and update counters
            *(int *)(this + 0x44) += 12;    // accum timer
            *(int *)(this + 0x48) += 1;     // tick counter
            *(int *)(this + 0x50) += 1;     // global tick
            *(int *)(this + 0x4C) = *(int *)(this + 0x4C) + 1; // advance state pointer
            return;
        }
        // Else fall through to increment common items
    }
    else {
        if ((stateFlags & 0x10) != 0) {  // bit4 set
            int backup38 = *(int *)(this + 0x28); // save +0x28? Actually field is +0x28 but decomp shows iVar2 = *(int *)(unaff_EDI + 0x28); but later uses iVar2 incremented to write back.
            randVal = rand();  // __aullshr();
            randBits = randVal & 3;
            if (randBits < 3) {  // condition (randBits - 1) < 3 is true for 0,1,2,3? Actually (uint)(randBits - 1) < 3 includes 0,1,2,3? For randBits=0 -> 0xFFFFFFFF <3 false. So only 1,2,3 pass. Let's use original condition: (uVar3 & 3) - 1 < 3. For uVar3 & 3 = 1 -> 0 < 3 true, 2 -> 1 <3 true, 3 -> 2 <3 true. So all except 0.
                *(int *)(this + 0x1c) += 1;
                *(int *)(this + 0x20) += 12;
                *(int *)(this + 0x50) += 1;
                *(int *)(this + 0x28) = backup38 + 1;
                *(int *)(this + 0x4C) = *(int *)(this + 0x4C) + 1;
                return;
            }
            *(int *)(this + 0x1c) += 3;
            *(int *)(this + 0x20) += 12;
            *(int *)(this + 0x50) += 1;
            *(int *)(this + 0x28) = backup38 + 1;
            *(int *)(this + 0x4C) = *(int *)(this + 0x4C) + 1;
            return;
        }
        if ((stateFlags & 8) != 0) {   // bit3 set
            int backup2C = *(int *)(this + 0x38);  // save +0x38
            randVal = rand();  // __aullshr();
            randBits = randVal & 3;
            if (randBits < 3) { // similar condition
                *(int *)(this + 0x2c) += 2;
                *(int *)(this + 0x30) += 12;
                *(int *)(this + 0x50) += 1;
                *(int *)(this + 0x38) = backup2C + 1;
                *(int *)(this + 0x4C) = *(int *)(this + 0x4C) + 1;
                return;
            }
            *(int *)(this + 0x2c) += 6;
            *(int *)(this + 0x30) += 12;
            *(int *)(this + 0x50) += 1;
            *(int *)(this + 0x38) = backup2C + 1;
            *(int *)(this + 0x4C) = *(int *)(this + 0x4C) + 1;
            return;
        }
        // bits 2 or 4 (0x4) set? Actually 0x1c includes 0x4 and 0x8 and 0x10. So if none of those, must be bit2 (0x4) set? Or bit2+others? Since condition else is reached when ((stateFlags & 0x1C) != 0) and neither 0x10 nor 0x8 set, then 0x4 set.
        *(int *)(this + 0x3c) += 12;
        *(int *)(this + 0x40) += 1;
    }
    // Common increment for all except the fast returns
    *(int *)(this + 0x50) += 1;
    *(int *)(this + 0x4C) = *(int *)(this + 0x4C) + 1;
    return;
}