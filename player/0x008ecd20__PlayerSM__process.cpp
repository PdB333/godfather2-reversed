// FUNC_NAME: PlayerSM::process
// Function at 0x008ecd20
// Role: Player state machine update – check whether a state transition is necessary, and if not, perform a default fallback transition.

void PlayerSM::process() {
    int canTransition = this->shouldTransition();
    if (canTransition == 0) {
        this->doDefaultTransition();
    }
}