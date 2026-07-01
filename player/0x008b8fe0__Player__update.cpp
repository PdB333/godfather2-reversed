// FUNC_NAME: Player::update
void __thiscall Player::update() {
    // Check if game is paused (FUN_00842870)
    bool isPaused = isGamePaused();
    if (!isPaused) {
        // Enable player update (FUN_00471db0(1))
        enablePlayerUpdate(1);
    } else {
        // Disable player update (FUN_00471df0())
        disablePlayerUpdate();
    }

    // +0x130: pointer to a state machine component
    if (m_pStateMachine != nullptr) {
        // Update state machine with its internal data at +0x20 (FUN_00429540)
        updateStateMachine(this, m_pStateMachine->m_pStateData);
    }
}