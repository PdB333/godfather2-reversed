// FUNC_NAME: PlayerSM::canTransition
uint __thiscall PlayerSM::canTransition(void) {
    uint globalValue = getSomeGlobalValue(); // e.g., frame count or elapsed time
    uint currentState = *(uint *)((int)this + 4); // +0x4: state enum

    if ((int)globalValue < 6 &&
        (currentState == 1 || currentState == 2 || currentState == 3 || currentState == 4)) {
        // State is in the allowed set; set low byte to 1 (transition allowed flag)
        return (currentState & 0xFFFFFF00) | 1;
    }
    // Otherwise return the global value with low byte cleared (transition not allowed)
    return globalValue & 0xFFFFFF00;
}