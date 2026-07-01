// FUNC_NAME: CoverState::setOwner
// Address: 0x00892a90
// Role: Sets the owner pointer and ORs flags for a CoverState object.
// The owner pointer is derived from a nested structure: ownerObj->somePtr->currentState.
// Offsets: this+0x00 = owner (void*), this+0x04 = flags (byte)
// ownerObj+0x180 = pointer to a state machine, stateMachine+0x40 = pointer to current state

void __thiscall CoverState::setOwner(void* ownerObj, byte flagsToSet)
{
    // OR the flags into the byte at offset 4
    *(byte*)(this + 4) |= flagsToSet;
    // Set the pointer at offset 0 to the current state from the owner's state machine
    *(void**)this = *(void**)(*(int*)((char*)ownerObj + 0x180) + 0x40);
}