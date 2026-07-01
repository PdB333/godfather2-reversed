// FUNC_NAME: SomeClass::isCurrentState
// Address: 0x008fe3d0
// Role: Checks if a stored value at offset +0x58 matches the current global value returned by getCurrentValue().
// This is likely a member function of a game object (e.g., Entity, StateMachine) that compares a cached state ID with the active state.

bool __thiscall SomeClass::isCurrentState() {
    // Read stored value from this+0x58 (likely a state ID, type index, or pointer)
    int storedValue = *(int*)(this + 0x58);
    // Get the current global value (e.g., current game mode, active state)
    int currentValue = getCurrentValue(); // Calls FUN_008fe1e0
    // Return true if they match
    return currentValue == storedValue;
}