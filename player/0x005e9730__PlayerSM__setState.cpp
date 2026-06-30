// FUNC_NAME: PlayerSM::setState
// Function address: 0x005e9730
// Sets a new state value at +0x484, validates via validateState(), and if valid, commits it to +0x480.
// Returns true on success (validation passed), false if validation fails (but the new value is already stored at +0x484).

bool PlayerSM::setState(int newState) {
    char valid;
    if (newState != *(int *)(this + 0x484)) {
        *(int *)(this + 0x484) = newState;
        valid = this->validateState(); // virtual or member function at 0x005e8900
        if (valid == 0) {
            return false;
        }
        *(int *)(this + 0x480) = *(int *)(this + 0x484); // commit validated state
    }
    return true;
}