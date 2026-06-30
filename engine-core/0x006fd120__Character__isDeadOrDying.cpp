// FUNC_NAME: Character::isDeadOrDying

// Returns true if the character's state is 3 (dead) or 4 (dying).
// Uses the state index at (+0x28) into a global array of state structures
// (each 0x58 bytes, starting at offset +0x78 of g_stateManager).
bool __thiscall Character::isDeadOrDying() {
    int stateIndex = *(int*)((int)this + 0x28);          // +0x28: state index
    if (stateIndex == -1) {
        return false;
    }

    int* stateEntry = (int*)(stateIndex * 0x58 + 0x78 + (int)g_stateManager); // +0x78: array base in manager
    if (stateEntry == nullptr) {
        return false;
    }

    int currentState = *stateEntry;                      // +0x00: state value
    return (currentState == 3 || currentState == 4);
}