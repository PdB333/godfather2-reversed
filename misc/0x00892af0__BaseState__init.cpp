// FUNC_NAME: BaseState::init
void __thiscall BaseState::init(BaseState* this, char stateType) {
    // Initialize all integer fields to 0
    this->field0 = 0;   // +0x00
    this->field1 = 0;   // +0x04
    this->field2 = 0;   // +0x08
    this->field3 = 0;   // +0x0C
    this->type = stateType; // +0x10 (byte) – identifies the specific state type
    this->field5 = 0;   // +0x14
    this->field6 = 0;   // +0x18
    // Total structure size: at least 0x1C (28 bytes)
    // This function is called from numerous constructors across the codebase,
    // suggesting it is a common base initializer for state-like objects.
}