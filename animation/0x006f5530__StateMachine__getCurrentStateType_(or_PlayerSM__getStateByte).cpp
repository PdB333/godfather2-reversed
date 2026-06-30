// FUNC_NAME: StateMachine::getCurrentStateType (or PlayerSM::getStateByte)
// Address: 0x006f5530
// This method returns a byte from the current state object. If the state pointer at +0x20 is null,
// it lazily retrieves it by calling a creation function on the component pointer at +0x18.
// The returned byte (at offset +0x20 of the state object) likely indicates the state identifier or a flag.

uint8_t StateMachine::getCurrentStateByte()
{
    // +0x20: pointer to a state object (initially null)
    if (this->statePtr == nullptr)
    {
        // +0x18: pointer to a component (e.g., PhysicsComponent, AnimationComponent)
        // Dereference it to get an object, then call a function to obtain the state object.
        this->statePtr = StateMachine::createStateFromComponent(*(void**)this->componentPtr);
    }
    // +0x20 in the state object stores the byte we need
    return *(uint8_t*)(this->statePtr + 0x20);
}