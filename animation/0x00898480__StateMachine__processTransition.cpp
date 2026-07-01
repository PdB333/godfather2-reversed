// FUNC_NAME: StateMachine::processTransition
void StateMachine::processTransition(int action) {
    if (this != 0) {
        if (action == 0 || action == 1) {
            this->onTransitionStart(action); // previously FUN_008980f0 - initializes transition start
        }
        this->onTransitionEnd(); // previously FUN_00898390 - finalizes transition (always called)
    }
}