// FUNC_NAME: PlayerStateMachine::tick
void __thiscall PlayerStateMachine::tick(void)
{
    char isPaused;

    isPaused = FUN_00481620(); // IsGamePaused? (likely returns bool)
    if (isPaused != '\0') {
        FUN_0081dce0(); // UpdatePauseState
    }

    // Check bit 12 at offset 0x24a0 (e.g., isDead, isInCutscene, etc.)
    if ((*(uint *)(this + 0x24a0) >> 0xc & 1) != 0) {
        FUN_007a63f0(); // HandleSpecialState
        return;
    }

    FUN_00800880(); // UpdateGeneral

    // Check if active and currentState is valid (not 0 and not 0x48)
    if ((*(char *)(this + 0x161) != '\0') && 
        (*(int *)(this + 0x74c) != 0) && 
        (*(int *)(this + 0x74c) != 0x48)) {
        FUN_00707610(); // UpdateStateSpecific
    }

    // If currentState is valid and not 0x48, and game is paused, transition
    if ((*(int *)(this + 0x74c) != 0) && 
        (*(int *)(this + 0x74c) != 0x48) && 
        (isPaused = FUN_00481620(), isPaused != '\0')) {
        if (*(int *)(this + 0x74c) != 0) {
            FUN_0093b6a0(*(int *)(this + 0x74c) + -0x48, 0); // TransitionToState(state - 0x48, 0)
            return;
        }
        FUN_0093b6a0(0, 0); // TransitionToState(0, 0)
    }
    return;
}