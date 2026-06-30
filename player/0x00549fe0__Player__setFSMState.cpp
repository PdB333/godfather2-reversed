// FUNC_NAME: Player::setFSMState
void __thiscall Player::setFSMState(Player *this, int newState)
{
    // this+0xc0 is pointer to player's finite state machine (e.g., PlayerF2FSM, PlayerGroundSM, etc.)
    // that FSM object stores the current state ID at offset 0x10
    *(int *)(*(int *)(this + 0xc0) + 0x10) = newState;
}