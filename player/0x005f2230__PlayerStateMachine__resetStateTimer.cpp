// FUNC_NAME: PlayerStateMachine::resetStateTimer
void __thiscall PlayerStateMachine::resetStateTimer() {
    if (this != nullptr) {
        // Call update function with state fields at +0x64 (byte), +0x5C (int), +0x65 (byte)
        updateStateWithArgs(this->field_0x64, this->field_0x5C, this->field_0x65);
        // Process current state (FUN_005f3640)
        processCurrentState();
        // Copy old timer to current timer (+0x88 -> +0x8C)
        this->field_0x8C = this->field_0x88;
        // Set ready flag at +0x67 to 0xFF
        this->field_0x67 = 0xFF;
        // Repeat update call after state change
        updateStateWithArgs(this->field_0x64, this->field_0x5C, this->field_0x65);
    }
}