// FUNC_NAME: PlayerSM::processInputAction
// Address: 0x0079de00
// Role: Handles player input actions related to contextual interactions (e.g., entering/exiting vehicles, cover, etc.)
void __thiscall PlayerSM::processInputAction(PlayerSM* this, int actionId)
{
    char isInputAllowed;
    int gameManager;

    isInputAllowed = InputManager::isGameActive(); // FUN_00481620
    if (isInputAllowed == '\0') {
        return;
    }

    // Global pointer to game manager (DAT_0112b9b4)
    gameManager = *(int*)(0x0112b9b4 + 0x40); // +0x40: current player manager or scenario
    if (gameManager == 0) {
        // No active scenario/player manager
        if (actionId == 0) {
            // Debug log: unknown hash for "No target"
            Debug::logHash(0x8fb06fc4); // FUN_00894c90
        }

        // Global pointer to something (e.g., current mission/state) at DAT_011299c4 + 0x1c
        if (*(int*)(0x011299c4 + 0x1c) != 0) {
            // Execute action directly (e.g., trigger quick event)
            MissionManager::startQuickEvent(actionId); // FUN_008fd3f0
            this->m_transitionFlag = 1; // +0x205c: set flag to indicate action processed
            return;
        }

        // Default path: transition to state for action
        PlayerSM::enterState(this, actionId); // FUN_00811be0
        this->m_transitionFlag = 1;
        return;
    }

    // Player manager is active, check its state machine
    if (*(int*)(gameManager + 0xd8) == 2) { // +0xd8: current player state (e.g., 2 = "InVehicle")
        // Check cooldown or target
        if ((*(int*)(gameManager + 0x120) != -1) && (*(int*)(gameManager + 0x124) < 1)) {
            // Indicate that this action should not be processed again until cooldown
            *(uint*)(gameManager + 0x7c) |= 8; // +0x7c: bitfield flags, set bit 3
            return;
        }

        // Decrement a counter (e.g., action attempts)
        *(int*)(gameManager + 0x124) -= 1;

        // Adjust the 'this' pointer if it is null? The decompiled logic:
        // if (param_1 == 0) param_1 = 0; else param_1 = param_1 + 0x3c;
        // This seems like a bug or unusual pattern; maybe intended as:
        // int target = (this != 0) ? (int)this + 0x3c : 0;
        int target = (this != 0) ? (int)this + 0x3c : 0;

        // Play audio event or animation at target offset (e.g., character animation bone)
        AudioManager::playEvent(0x0112b214, target, 0); // FUN_00408c70
        return;
    }

    return;
}