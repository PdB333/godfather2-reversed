// FUNC_NAME: PlayerSM::toggleActionState
void __thiscall PlayerSM::toggleActionState(PlayerSM* this, void* stateObj) {
    // FUN_00481620: check if game is active (not paused, not cutscene)
    bool isGameplayActive = isGameplayActive();

    // +0x11c: current player state ID; skip toggle if state is 1 (e.g., kState_Paused)
    if (isGameplayActive && *(int*)((char*)this + 0x11c) != 1) {
        // +0x10: flag on the state object; invert it (toggle)
        *(uint32_t*)((char*)stateObj + 0x10) = (*(uint32_t*)((char*)stateObj + 0x10) == 0) ? 1 : 0;
    }

    // FUN_008b5aa0: apply/process the state transition
    processState(stateObj);
}