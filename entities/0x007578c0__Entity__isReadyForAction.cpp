// FUNC_NAME: Entity::isReadyForAction
// Address: 0x007578c0
// Role: Checks if the entity is ready to perform an action. Returns false if a forced idle object exists and the game is not paused, or if no action system is available. Otherwise returns true if the action system reports ready.

bool __fastcall Entity::isReadyForAction(Entity* this) {
    // +0x108: Pointer to a forced idle state object (might block actions when game is running)
    // +0x10c: Pointer to an action system interface (e.g., state machine)
    if (this->m_pForcedIdle != nullptr) {
        // 0x005f6820: Global function that checks if game is paused; returns non-zero when paused.
        // If forced idle exists and game is NOT paused, block the action.
        if (IsGamePaused() == 0) {
            return false;
        }
    }
    if (this->m_pActionSystem != nullptr) {
        // Action system vtable slot at offset +8 (index 2) is a readiness check (e.g., isActive/isReady)
        if (this->m_pActionSystem->isReady() != 0) {
            return true;
        }
    }
    return false;
}