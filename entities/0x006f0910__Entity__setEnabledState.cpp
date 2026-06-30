// FUNC_NAME: Entity::setEnabledState
void __thiscall Entity::setEnabledState(bool enable) {
    // Read the current state from offset +0x20 (likely m_activationState)
    int currentState = *(int *)(this + 0x20);

    if (!enable) {
        // Disable: transition from state 1 or 2 to state 0
        if (currentState == 1 || currentState == 2) {
            *(int *)(this + 0x20) = 0;
        }
    } else {
        // Enable: transition from state 0 or 1 to state 2
        if (currentState == 0 || currentState == 1) {
            *(int *)(this + 0x20) = 2;
        }
    }
}