// FUNC_NAME: AIStateMachine::getState
int __thiscall AIStateMachine::getState(void) {
    // +0x94: flags byte (bit 0 = override flag)
    // +0x90: state index (0 or 1 for normal states)
    char flags = *(char*)((int)this + 0x94);
    if ((flags & 1) == 0) {
        int state = *(int*)((int)this + 0x90);
        if (state == 0) {
            return 1; // e.g., STATE_ACTIVE
        }
        if (state == 1) {
            return 2; // e.g., STATE_COMPLETED
        }
    } else {
        // Override path: check global condition
        if (FUN_00481620()) { // isGlobalOverrideActive?
            return FUN_0080d360(); // getOverrideState
        }
        float timeValue;
        if (FUN_00472510(&timeValue)) { // getTimeUntilSomething
            if (DAT_00d577a0 < timeValue) {
                return 1;
            }
            return 2;
        }
    }
    return 0; // e.g., STATE_INACTIVE
}