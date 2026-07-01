// FUNC_NAME: SomeStateMachine::initializeState
// Address: 0x00976bc0
// This function initializes a state machine state: sets a flag, stores state ID and data, then calls a virtual activation method.
void __thiscall SomeStateMachine::initializeState(int param_2, undefined8 *param_3) {
    // +0x1c1: byte flag (e.g., bIsActive or bInitialized)
    *(byte *)((int)this + 0x1c1) = 0;  // Clear flag

    // Called with argument 1 - purpose unknown; maybe debug/log or reset timer
    FUN_00957780(1);

    // +0x18: flags (bitfield) - OR with 0x20 indicates state readiness
    this[0x18] |= 0x20;

    // +0x94: store first 8 bytes of stateData (e.g., a pointer or double value)
    *(undefined8 *)(this + 0x25) = *param_3;

    // +0x9c: store next 4 bytes of stateData (int, e.g., substate or counter)
    this[0x27] = *(int *)(param_3 + 1);

    // +0x90: store state ID
    this[0x24] = param_2;

    // Call virtual method at vtable offset 0x28 (index 10) - likely "onActivate" or "begin"
    (*(void (__thiscall **)(int *))(*(int *)this + 0x28))();
}