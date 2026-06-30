// FUNC_NAME: PlayerSM::setInitialState
void __thiscall PlayerSM::setInitialState(PlayerSM* this) {
    // Set the current state to the initial state constant (global DAT_00e2cd5c)
    *(int*)((uintptr_t)this + 0xAC) = DAT_00e2cd5c; // +0xAC: m_currentState
}