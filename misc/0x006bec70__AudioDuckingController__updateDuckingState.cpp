// FUNC_NAME: AudioDuckingController::updateDuckingState
void __thiscall AudioDuckingController::updateDuckingState(int thisPtr, int forceReset) {
    // +0x14: pointer to primary audio source (e.g., dialog)
    // +0x18: pointer to secondary audio source (e.g., music)
    // Both have +0x54 which holds an audio event hash (0x637b907 = "DIALOG"?)
    int* primarySource = *(int**)(thisPtr + 0x14);
    int* secondarySource = *(int**)(thisPtr + 0x18);
    const int dialogHash = 0x637b907;

    // If forceReset is 0 and either source is the dialog audio event
    if (forceReset == 0 &&
        (primarySource != NULL && primarySource[0x54 / 4] == dialogHash ||
         secondarySource != NULL && secondarySource[0x54 / 4] == dialogHash)) {
        // Check if dialog audio is currently playing
        bool dialogPlaying = FUN_006b34a0(); // isDialogPlaying()?
        int currentState = *(int*)(thisPtr + 0x40);

        if (!dialogPlaying) {
            // Dialog not playing: transition from other states to 1 or 3
            if (currentState != 1) {
                if (currentState == 2) {
                    // State 2 -> 1: reset ducking to normal level
                    FUN_0093ea60(*(int*)(*(int*)(thisPtr + 0x10) + 0x38)); // resetMixer()
                    *(int*)(thisPtr + 0x40) = 1;
                    return;
                }
                if (currentState != 3) {
                    // From any other state (likely 0) to state 3: set ducking level to 0 (unmute)
                    FUN_0093e960(*(int*)(*(int*)(thisPtr + 0x10) + 0x38), 0); // setDuckingLevel(mixer, 0)
                    *(int*)(thisPtr + 0x40) = 3;
                    return;
                }
            }
        } else {
            // Dialog is playing: ensure we are in state 2 (ducking active)
            if (currentState != 2) {
                FUN_0093e960(*(int*)(*(int*)(thisPtr + 0x10) + 0x38), 1); // setDuckingLevel(mixer, 1)
                *(int*)(thisPtr + 0x40) = 2;
                return;
            }
        }
    } else {
        // No dialog audio source active: reset to state 0 (no ducking)
        if (*(int*)(thisPtr + 0x40) != 0) {
            FUN_0093ea60(*(int*)(*(int*)(thisPtr + 0x10) + 0x38)); // resetMixer()
            *(int*)(thisPtr + 0x40) = 0;
        }
    }
}