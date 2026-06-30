// FUNC_NAME: GameObject::setState
bool GameObject::setState(int newState) {
    // If the new state is different from current state (offset 0x484)
    if (newState != this->m_currentState) {
        this->m_currentState = newState; // offset 0x484
        
        // Validate the state transition (calls FUN_005e8900)
        bool valid = this->validateStateTransition(); // offset 0x484?
        if (!valid) {
            return false;
        }
        
        // Store the current state also as previous state (offset 0x480)
        this->m_previousState = this->m_currentState;
    }
    return true;
}