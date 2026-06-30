// FUNC_NAME: AIComponent::dispatchUpdate
void __thiscall AIComponent::dispatchUpdate(int target) {
    // Check if this component has a valid state machine (offset +0x38) and the target has a required component (offset +0xB4)
    if (this->stateMachine != 0 && *(int*)(target + 0xB4) != 0) {
        // Branch based on current state flag (offset +0x3C)
        if (this->currentState == 0) {
            // State 0: normal update path
            FUN_005764e0(target);
        } else {
            // Other states: alternate update path
            FUN_00574bd0(target);
        }
    }
}