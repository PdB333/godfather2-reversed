// FUNC_NAME: PlayerSM::updateTransitions
void __thiscall PlayerSM::updateTransitions(PlayerSM* this) {
    int uVar1;
    
    if (((this->flags & 1) != 0) &&
        (((this->stateValue != 0 && this->stateValue != 0x48) ||
         ((this->transitionFlag & 1) != 0)))) {
        if (this->currentState == 0) {
            uVar1 = 0;
        }
        else {
            uVar1 = getNewStateFromManager(DAT_0112afe8); // SimManager::getNextState? 
        }
        this->nextState = uVar1;
    }
    if ((this->flags >> 0xb & 1) == 0) {
        clearFlag(0x20); // e.g., clearTimer or disableInput
    }
}