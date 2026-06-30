// FUNC_NAME: PlayerSM::PlayerSM(uint)
// Address: 0x006dcdb0
// Role: Constructor for a state machine object (possibly PlayerSM), initializes vtable pointers and zeroes state fields.
// The class has multiple vtable pointers (at +0x00, +0x3C, +0x48, +0x50) indicating multiple inheritance.
// Four DWORD fields at +0x58, +0x5C, +0x60, +0x64 are cleared.
// Calls base class constructor with the same argument and an initialization routine.

void* __thiscall PlayerSM::PlayerSM(uint someArg)
{
    // Base class constructor (e.g., BaseStateMachine::BaseStateMachine)
    FUN_00473840(someArg);

    // Set the primary vtable pointer
    this->vtable0 = &PTR_FUN_00d5f678;
    // Secondary vtable pointers for additional base classes
    *(void**)((uint)this + 0x3C) = &PTR_LAB_00d5f668; // +0x3C
    *(void**)((uint)this + 0x48) = &PTR_LAB_00d5f664; // +0x48
    *(void**)((uint)this + 0x50) = &PTR_LAB_00d5f660; // +0x50

    // Initialize state/flag fields to zero
    *(int*)((uint)this + 0x58) = 0;
    *(int*)((uint)this + 0x5C) = 0;
    *(int*)((uint)this + 0x60) = 0;
    *(int*)((uint)this + 0x64) = 0;

    // Additional initialization
    FUN_006dc940();

    return this;
}