// FUNC_NAME: Player::think
undefined4 __thiscall Player::think(int this, char isForced)
{
    int *pBaseObj;
    DebugTimeStruct timeStruct; // local_1c, local_18, local_14

    // If forced and (state == 1 or (state != 0 && counter < 1)), increment counter and fire state transition
    if ((isForced != '\0') &&
        ((*(int *)(this + 0x14c) == 1) ||
         ((*(int *)(this + 0x14c) != 0 && (*(int *)(this + 0x138) < 1))))) {
        *(int *)(this + 0x138) = *(int *)(this + 0x138) + 1;
        stateMachineTransition(this + 0x14, &LAB_00978de0, 0); // Fire "enter" state event
    }

    // Check time since last update: if not enough time has passed, return 0
    // DAT_01205214 = current time, +0x70 = lastUpdateTime, +0x68 = pointer to rate data (+0x108 = updateRate)
    // _DAT_00d5c458 = global time scale
    if (DAT_01205214 - *(float *)(this + 0x70) <
        *(float *)(*(int *)(this + 0x68) + 0x108) * _DAT_00d5c458) {
        return 0;
    }

    // Setup debug timer struct
    timeStruct = { DAT_011303a8, 0, 0 };
    debugScheduleUpdate(&timeStruct, 0); // FUN_00408a00

    // Retrieve base object from global manager (offset -0x1f30 from vtable)
    if (**(int **)(DAT_012233a0 + 4) == 0) {
        pBaseObj = (int *)0x0;
    } else {
        pBaseObj = (int *)(**(int **)(DAT_012233a0 + 4) - 0x1f30);
    }

    updateTime(); // FUN_0079d520
    (*(code **)(*pBaseObj + 0x74))(); // Virtual function call at offset 0x74

    resetSomething(0); // FUN_00977140
    drawDebugInfo(&DAT_0112dc44, 0, _DAT_00d8f95c, 0, 4); // FUN_00440590

    if (*(int *)(this + 0xb0) != 0) {
        updatePhysics(); // First call to FUN_004df600
    }
    updatePhysics(); // Second call to FUN_004df600

    finalizeUpdate(0); // FUN_0097a310

    // Transition sub-state to 3 if not already
    if (*(int *)(this + 0x158) != 3) {
        *(undefined4 *)(this + 0x158) = 3;
        stateMachineTransition(this + 0x14, &LAB_00978e20, 0); // Fire "think complete" state event
    }

    return 1;
}