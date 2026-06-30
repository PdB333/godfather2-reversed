// FUNC_NAME: AnimStateController::updateStateMachine
void __thiscall AnimStateController::updateStateMachine(int param_1)
{
    // +0x04: some current value (e.g., blend weight, state index)
    // +0x08: previous value (copy of +0x04)
    // +0x0C: result or next value
    // +0x10: pointer to a data structure (used in function call)
    // +0x14: state flag (0x11f = idle, other = active)
    // +0x18: target value (copied to +0x10 when transitioning)

    *(int *)(this + 8) = *(int *)(this + 4); // Save current value as previous

    if (*(int *)(this + 0x14) != 0x11f) { // If not idle
        *(int *)(this + 0x0C) = *(int *)(this + 0x14); // Store current state to result
        *(int *)(this + 0x10) = *(int *)(this + 0x18); // Copy target to active pointer
        *(int *)(this + 0x14) = 0x11f; // Set state to idle
        return;
    }

    // Idle state: process and update result
    int result = FUN_00639c70(*(int *)(this + 0x10), param_1);
    *(int *)(this + 0x0C) = result;
}