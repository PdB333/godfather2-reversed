// FUNC_NAME: Player::checkTimedEvents
void __thiscall Player::checkTimedEvents() {
    // +0x26c: pointer to timed action data (nullable)
    // +0x281: flag for phase 1 complete
    // +0x484: pointer to a condition object (nullable)
    // +0x1cc: some ID/value passed to condition check
    // +0x270: threshold value for phase 1
    // +0x27c: parameter sent to event system
    // +0x274: threshold value for phase 2
    // +0x282: flag for phase 2 complete

    if (*(int*)(this + 0x26c) != 0) { // timedActionData exists
        if (*(char*)(this + 0x281) == 0) { // phase 1 not yet triggered
            if (*(int*)(this + 0x484) != 0) { // condition object exists
                // Call vtable function at +0x68 on a global object pointer (DAT_01223510)
                int currentValue = (**(code**)(*DAT_01223510 + 0x68))(*(undefined4*)(this + 0x1cc));
                if (currentValue >= 0 && currentValue <= *(int*)(this + 0x270)) {
                    *(char*)(this + 0x281) = 1;
                    // Trigger event 6 (e.g., timed fade-out)
                    FUN_005e25a0(DAT_0122350c, *(int*)(this + 0x27c), 6);
                }
            }
        }
        else { // phase 1 already triggered
            if (*(int*)(this + 0x274) >= 0 && *(char*)(this + 0x282) == 0) {
                int currentValue = FUN_005e9780(); // global time function
                if (currentValue >= 0 && currentValue <= *(int*)(this + 0x274)) {
                    *(char*)(this + 0x282) = 1;
                    // Trigger event 7 (e.g., timed fade-in)
                    FUN_005e25a0(DAT_0122350c, *(int*)(this + 0x27c), 7);
                }
            }
        }
    }
}