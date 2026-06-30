// FUNC_NAME: Player::isInAnyActiveState
bool __thiscall Player::isInAnyActiveState(int stateId) {
    // Check if the ground state machine is in the given state (offset +0x1c)
    if (m_groundSM.isInState(stateId)) {
        return true;
    }
    // Check if the wall cover state machine is in the given state (offset +0x28)
    if (m_wallCoverSM.isInState(stateId)) {
        return true;
    }
    return false;
}