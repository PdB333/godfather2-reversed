// FUNC_NAME: PlayerSM::isStateChangeAllowed
// Address: 0x007b9ee0
// Role: Checks if state change is allowed, considering global pause and a stored blocking state.
bool __fastcall PlayerSM::isStateChangeAllowed() {
    // Check if game is paused/cutscene playing (FUN_004ac260)
    if (Engine::isGamePaused()) {
        return true; // state change always allowed during pause? (or rather, no change)
    }
    // Compare current state with stored state at +0x1a8 (blocking state ID)
    int currentState = StateMachine::getCurrentStateID(); // FUN_0045eea0
    if (currentState == *(int*)(this + 0x1a8)) {
        return false; // if matching, disallow state change
    }
    return true; // otherwise allow
}