// FUNC_NAME: StateMachine::transitionToState4
// Function address: 0x005c04e0
// Role: Wrapper that calls a helper function (FUN_005c01d0) with a fixed third argument of 4.
// Likely transitions to a specific state (e.g., idle, attack) identified by the constant.
// Parameters: arg2-arg5 likely correspond to entity ID, extra flags, etc.
void __thiscall StateMachine::transitionToState4(int arg2, int arg3, int arg4, int arg5) {
    FUN_005c01d0(this, arg2, 4, arg3, arg4, arg5);
}