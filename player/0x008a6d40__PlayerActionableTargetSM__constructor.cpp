// FUNC_NAME: PlayerActionableTargetSM::constructor
// Address: 0x008a6d40
// Role: Constructor for PlayerActionableTargetSM. Initializes vtable pointers and target state fields.

// Function signature: __thiscall PlayerActionableTargetSM * __thiscall PlayerActionableTargetSM::constructor(PlayerActionableTargetSM *this, int initializationParam)

PlayerActionableTargetSM * __thiscall PlayerActionableTargetSM::constructor(PlayerActionableTargetSM *this, int initializationParam)
{
    // Call base class constructor
    FUN_008a1340(initializationParam);

    // Set base class vtable pointer (offset 0x00)
    this->baseVtable = &PTR_FUN_00d79b04;  // +0x00

    // Additional vtable pointers for interfaces/multiple inheritance
    this->someInterfaceVtable1 = &PTR_LAB_00d79af4;  // +0x3C (offset 0x3C)
    this->someInterfaceVtable2 = &PTR_LAB_00d79af0;  // +0x48 (offset 0x48)

    // Initialize target state fields
    this->targetCount = 0;               // +0x58 (param_1[0x16])
    this->currentTargetIndex = -1;       // +0x5C (param_1[0x17])  -1 means no target selected
    this->maxTargets = 0;                // +0x60 (param_1[0x18])

    return this;
}