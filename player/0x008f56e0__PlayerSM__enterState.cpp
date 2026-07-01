// FUNC_NAME: PlayerSM::enterState
// Address: 0x008f56e0
// Role: State machine transition handler – updates state, clears a flag, triggers notifications.
// This function is __thiscall on a PlayerSM instance.

// Offset +0x10: uint32 flags
void __thiscall PlayerSM::enterState(uint stateId, uint transitionData) {
    // Pre-transition processing (e.g., time delta, input snapshot)
    PreTransitionUpdate();                      // FUN_008f4160

    // Prepare animation system for new state
    PrepareAnimation();                         // FUN_008f5190

    // Play animation #5 with stateId and transitionData (1 = blend? loop?)
    PlayAnimation(5, stateId, transitionData, 1); // FUN_008f2200

    // Clear bit 12 (0x1000) in flags – likely "isTransitioning" or "isAnimating"
    flags &= ~0x1000;

    // Broadcast state change event to listeners
    NotifyStateChange();                        // FUN_008f37a0
}