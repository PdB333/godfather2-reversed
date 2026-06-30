// FUNC_NAME: StateCondition::checkCondition
// Address: 0x004e4cf0
// Role: Checks if the object state is valid (not in a special false condition).
// Returns 0 (false) if state == 1 and subState == 0, otherwise 1 (true).
// __thiscall - 'this' pointer in EAX.

int StateCondition::checkCondition() {
    // Offset +0x00: state (int)
    // Offset +0x04: subState (int)
    if ((this->state == 1) && (this->subState == 0)) {
        return 0; // condition not met
    }
    return 1; // condition met
}