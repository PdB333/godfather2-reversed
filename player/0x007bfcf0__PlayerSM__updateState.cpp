// FUNC_NAME: PlayerSM::updateState
void __thiscall PlayerSM::updateState(PlayerSM *this)
{
    bool canTransition;
    
    // Check if the state machine can transition (virtual function at vtable offset 0x17C)
    canTransition = this->vtable->canTransition();
    if (canTransition) {
        // Perform the actual state transition (virtual function at vtable offset 0x1A4)
        this->vtable->transitionToNextState();
    }
    return;
}