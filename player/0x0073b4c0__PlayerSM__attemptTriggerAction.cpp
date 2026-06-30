// FUNC_NAME: PlayerSM::attemptTriggerAction
void __fastcall PlayerSM::attemptTriggerAction(PlayerSM* this) {
    // Check if action trigger flag (bit 0x800) is not already set,
    // current state is non-zero, and state is not the special "Idle" state (0x48).
    if (((*(this->flags) & 0x800) == 0) &&
        (this->currentState != 0) &&
        (this->currentState != 0x48)) {
        // Retrieve the game manager singleton.
        int gameManager = getGameManager(DAT_0112af98); // FUN_0043b870
        if (gameManager != 0) {
            // Execute a specific action identified by the value at +0x5c.
            executeAction(this->actionId); // FUN_00789600
            // Mark the action trigger flag.
            this->flags |= 0x800;
        }
    }
}