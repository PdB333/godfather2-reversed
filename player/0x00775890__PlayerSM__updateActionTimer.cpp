// FUNC_NAME: PlayerSM::updateActionTimer
void __thiscall PlayerSM::updateActionTimer(int *thisPtr) {
    int *actionTimer; // offset +0x68 (param_1[0x1a])
    int *currentAction; // offset +0x5C (param_1[0x17])
    int targetObj; // return from FUN_00724cf0

    if (thisPtr[0x17] != 0 && thisPtr[0x17] != 0x48) {
        // Decrement action timer (countdown before transition)
        actionTimer = thisPtr + 0x1a;
        *actionTimer = *actionTimer - 1;

        targetObj = FUN_00724cf0(); // e.g., getTargetObject() or getPlayer()
        if (targetObj != 0) {
            FUN_007757b0(1); // e.g., setActionComplete(1)
            // Virtual call: launch effect or spawn item at target
            (**(code **)(*thisPtr + 0x2c))(targetObj, 1, 1, 0, 1.0f, 1.0f);
        }
    }
}