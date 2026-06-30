// FUNC_NAME: StateComponent::setInitialState
void __thiscall StateComponent::setInitialState(int param_2) {
    // Set state data fields to default values
    *(int*)(this + 0x10) = 9;    // +0x10: state field - set to 9 (e.g., kState_Active)
    *(char*)(this + 0x14) = 2;   // +0x14: substate field - set to 2 (e.g., kSubstate_Default)
    *(int*)(this + 0x18) = param_2; // +0x18: additional data parameter
    return;
}