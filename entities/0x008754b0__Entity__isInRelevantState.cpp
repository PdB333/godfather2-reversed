// FUNC_NAME: Entity::isInRelevantState
bool Entity::isInRelevantState() const {
    int const currentState = this->m_state; // +0x00
    // Checks if the state is one of: 6 (likely kStateFighting), 8 (kStateArrested), 
    // 10 (kStateShooting), or 12 (kStateCovering) – used to determine interaction eligibility.
    return (currentState == 6) || (currentState == 8) || (currentState == 10) || (currentState == 12);
}