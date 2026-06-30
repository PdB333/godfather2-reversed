// FUNC_NAME: CharacterStateMachine::setState
void __thiscall CharacterStateMachine::setState(int thisPtr, int newState, char bSilent)
{
    int oldState;
    int bActive;
    int something;
    float stateTime;
    undefined4 local_1c;
    undefined ***local_18;
    undefined1 local_14;
    undefined **local_10;
    int local_c;
    int local_8;
    int local_4;

    // Check if character can change state (not dead, not doing special action, and has valid entity)
    oldState = *(int *)(thisPtr + 0x16c); // current state
    if ((((*(uint *)(thisPtr + 0x34) & 0x120000) == 0) && // flags: not 0x100000 and not 0x20000 (maybe "inVehicle" and "cowering"?)
         ((*(byte *)(thisPtr + 0x34) & 1) == 0)) && // flag bit 0 clear (maybe "dead"?)
        (*(int *)(thisPtr + 0x40) != 0)) { // entity pointer exists
        something = FUN_008c74d0(*(int *)(thisPtr + 0x40)); // check if entity is alive/active
        if ((something == 0) || ((~(byte)(*(uint *)(something + 0x84) >> 5) & 1) == 0)) { goto LAB_006b4e73; } // entity not valid -> force state 1
    } else {
LAB_006b4e73:
        oldState = 1; // force to state 1 (probably dead/inactive)
    }

    // Update state if changed
    int currentState = *(int *)(thisPtr + 0x16c);
    if (currentState != newState) {
        *(int *)(thisPtr + 0x16c) = newState; // set new state
        stateTime = (float)FUN_006b20f0(newState); // get state duration
        *(float *)(thisPtr + 0x170) = stateTime; // store state time

        if (newState == 0) {
            // Entering state 0 (idle/default)
            *(uint *)(thisPtr + 0x34) = *(uint *)(thisPtr + 0x34) & 0xfff5ffff; // clear flags 0xA0000 ? (0x100000 and 0x20000)
            FUN_006b24d0(); // state entry handler for state 0
            *(uint *)(thisPtr + 0x34) = *(uint *)(thisPtr + 0x34) & 0xffbfffff; // clear flag 0x400000 (maybe "special")
            FUN_008b7b70(*(undefined4 *)(thisPtr + 0x38)); // release some resource
            if (*(int *)(DAT_0112a668 + 0x18) != 0) { // global game manager
                *(undefined4 *)(thisPtr + 0x100) = *(undefined4 *)(*(int *)(DAT_0112a668 + 0x18) + 0xc0); // copy some pointer
            }
        } else if (currentState == 0) {
            // Exiting state 0
            FUN_006b2540(); // state exit handler for state 0
        }
        FUN_006b2f70(); // generic state transition callback
    }

    // Recompute active status for event dispatching
    int newActive = *(int *)(thisPtr + 0x16c);
    if ((((*(uint *)(thisPtr + 0x34) & 0x120000) == 0) &&
         ((*(byte *)(thisPtr + 0x34) & 1) == 0)) &&
        (*(int *)(thisPtr + 0x40) != 0)) {
        something = FUN_008c74d0(*(int *)(thisPtr + 0x40));
        if ((something != 0) && ((~(byte)(*(uint *)(something + 0x84) >> 5) & 1) != 0)) {
            goto LAB_006b4f31;
        }
    }
    newActive = 1; // fallback to active
LAB_006b4f31:
    // Dispatch state change event if silent flag not set and active status changed
    if ((newActive != oldState) && (bSilent == '\0')) {
        // Prepare event data structure
        local_10 = &PTR_LAB_00d5e234; // event type info
        local_c = thisPtr; // this object
        local_8 = oldState; // previous active state
        local_4 = newActive; // new active state
        if (*(int *)(thisPtr + 0xd4) != 0) {
            // Send event to signal/slot system (offset 0xd4 + 0x3c = dispatcher)
            FUN_00408bb0(&DAT_0112a600, *(int *)(thisPtr + 0xd4) + 0x3c, &local_10, 0);
        }
        // Another dispatch with different format?
        local_18 = &local_10;
        local_1c = DAT_0112a600;
        local_14 = 0;
        FUN_00408a00(&local_1c, 0);
        // Check per-state flag table (0x10 bytes per state at 0xe50d11)
        if (*(char *)(newActive * 0x10 + 0xe50d11) != '\0') {
            FUN_008c7330(); // maybe additional handling
        }
    }
    return;
}