// FUNC_NAME: AIComponent::updateStateMachine
void AIComponent::updateStateMachine() {
    // +0x484: current state (0-4)
    uint state = *(uint *)(this + 0x484);
    if (state > 4) {
        return;
    }
    do {
        switch (state) {
        case 2:
            // Call a global vtable function at DAT_01223510 + 0x8c, passing pointer at +0x1d0
            // Likely checks if some object is valid or ready
            char ready = (*(code **)(*DAT_01223510 + 0x8c))(*(undefined4 *)(this + 0x1d0));
            if (ready != '\0') {
                return;
            }
            int target = FUN_005e97d0();    // Resolve/acquire target
            FUN_005e9730();                 // Reset or transition state
            if (target == 0) {
                return;
            }
            if (*(char *)(target + 0x68) == '\0') {
                return;                     // Target not valid/alive
            }
            FUN_005e9380(target, this + 0x210, *(undefined4 *)(this + 0x20c)); // Execute action (target, param1, param2)
            return;
        case 3:
            return;
        case 4:
            if (*(char *)(this + 0x285) == '\0') {
                FUN_005e9730();             // Cleanup if flag not set
            }
            // Fall through to case 1
        case 1:
            char canAdvance = FUN_005e8f20(); // Check condition to proceed
            if (canAdvance == '\0') {
                return;
            }
            FUN_005e9730();                 // Advance state / cleanup
            return;
        }
        // After state switch, verify pointer at +0x1fc
        if (*(int *)(this + 0x1fc) == 0) {
            return;
        }
        FUN_005e9610(this);                 // General update/tick (passes this)
        state = *(uint *)(this + 0x484);    // Re-read state (may have changed)
        if (state == 0) {
            return;
        }
        if (state > 4) {
            return;
        }
    } while (true);
}