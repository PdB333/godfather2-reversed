// FUNC_NAME: PlayerSM::updateStateMachine

void __thiscall PlayerSM::updateStateMachine(int* thisPtr, uint deltaTimeOrInput) // param_1 = this, param_2 = deltaTime or input ID
{
    int subObj;
    char globalCheck;
    uint newVal;

    // +0x290: flag indicating something specific (e.g., "isActive" or "hasPendingAction")
    if (thisPtr[0xa4] != 0) {
        FUN_004df600(); // unknown: maybe start a global sound or VFX
        thisPtr[0x74] |= 0x1000; // +0x1D0: set bit 12 of flags
    }

    // vtable +0x160: virtual method, likely "processSubState" or "updateCurrentBehavior"
    (**(code**)(*thisPtr + 0x160))(deltaTimeOrInput);

    subObj = thisPtr[0x78]; // +0x1E0: pointer to sub-state machine or animation object
    if ((subObj != 0) && (*(int*)(subObj + 8) != 0)) {
        FUN_009e7530(subObj); // cleanup or release sub-object
    }

    // +0x158: transition to state 6 (e.g., "OnFoot", "Idle", etc.)
    FUN_0043c5b0(thisPtr, 6);
    thisPtr[0x56] = 0; // +0x158: reset state timer (local variable after state change)

    newVal = FUN_00445f00(deltaTimeOrInput); // get something from input (e.g., normalized movement)
    FUN_00446600(thisPtr, newVal); // update movement state with new value

    // check bit 7 of flags (mask 0x80)
    if (((uint)thisPtr[0x74] >> 7 & 1) != 0) {
        FUN_008557f0(thisPtr); // handle flag-specific action (e.g., "isCrouching")
    }

    // check bit 8 (0x100), bit 13 (0x2000), and pointer at +0x1B0
    if ((((uint)thisPtr[0x74] >> 8 & 1) != 0) && (thisPtr[0x6c] != 0) &&
        (((uint)thisPtr[0x74] >> 0xd & 1) != 0)) {
        FUN_00707cd0(); // unknown global function
        thisPtr[0x74] &= 0xfffffaff; // clear bits 8 and 9 (0x100, 0x200)
    }

    globalCheck = FUN_00481620(); // check global condition (e.g., game paused, cutscene)
    if (globalCheck != '\0') {
        if (thisPtr[0xa6] != 0) { // +0x298: pointer to some subsystem (e.g., camera, animation)
            FUN_004a91e0(thisPtr[0xa6]); // update that subsystem
        }
        FUN_00707ed0(deltaTimeOrInput); // final update call (maybe post-process)
    }
}