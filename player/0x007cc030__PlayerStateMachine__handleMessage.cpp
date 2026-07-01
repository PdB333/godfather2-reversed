// FUNC_NAME: PlayerStateMachine::handleMessage
void PlayerStateMachine::handleMessage(PlayerStateMachine* self, uint32_t msgType, uint32_t msgParam0, uint32_t msgParam1) {
    // Guard against null this pointer
    if (self == nullptr) {
        return;
    }

    // Call virtual function at vtable offset 0x284 (likely onEvent or handleInput)
    // Passes the two message parameters
    (self->vtable[0x284 / 4])(msgParam0, msgParam1);

    // Check if the game is paused; if not, resume game update
    bool isPaused = IsGamePaused();  // FUN_007f6340
    if (!isPaused) {
        ResumeGame();  // FUN_007f62b0
    }

    // Perform global update (e.g., logic tick, input processing)
    UpdateSystems();  // FUN_007f64a0

    // Based on some global state (likely a state enum), handle transitions
    // unaff_retaddr represents a register holding a state value (e.g., from a global flag)
    // For state 1: switch to a specific mode
    // For state 7: trigger game over / end sequence
    if (gCurrentState == 1) {
        SetGameState(1);  // FUN_007f6300(1)
    } else if (gCurrentState == 7) {
        ShowGameOverScreen();  // FUN_007fbed0
        return;
    }
}