// FUNC_NAME: PlayerSM::PlayerSM
PlayerSM::PlayerSM(int initialParam) {
    // Call base class constructor (likely PlayerStateMachineBase or similar)
    FUN_00adbf50(); 
    // Store the initial state identifier or parameter
    this->m_stateID = initialParam; // +0x0C: state/identifier
    // Mark state machine as active (enabled)
    this->m_isActive = 1;           // +0x38: active flag
}