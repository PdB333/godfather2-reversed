// FUNC_NAME: Animation::updateTransitionState
void __fastcall Animation::updateTransitionState(uint param_1)
{
    // +0x4: currentState?
    // +0x8: previousState (saved from +0x4)
    // +0xc: activeState (current state to be used)
    // +0x10: transitionData (e.g., blend factor or timer)
    // +0x14: pendingState (new state requested or 0x11f=287 meaning "in transition")
    // +0x18: pendingTransitionData (data for the pending transition)
    
    *(int *)(this + 8) = *(int *)(this + 4);
    if (*(int *)(this + 0x14) != 0x11f) {
        // Not currently in a transition – start a new one
        *(int *)(this + 0xc) = *(int *)(this + 0x14);
        *(int *)(this + 0x10) = *(int *)(this + 0x18);
        *(int *)(this + 0x14) = 0x11f; // Mark transition in progress
        return;
    }
    // Already transitioning – call the transition solver
    int newState = FUN_00639c70(this + 0x10, param_1);
    *(int *)(this + 0xc) = newState;
}