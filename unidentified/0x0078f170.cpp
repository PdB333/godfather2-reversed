// FUN_NAME: ActionCondition::evaluate
undefined1 __thiscall ActionCondition::evaluate(ActionCondition* this, Character* character) {
    undefined1 result = 0;
    int retVal;

    // First, try a quick check via the active character
    retVal = getActiveCharacter();
    if (retVal != 0) {
        result = checkConditionOnCharacter(retVal);
        return result;
    }

    // Bitmask check: character->flags must have all required bits set and no forbidden bits
    if (((this->m_requiredFlags & character->flags) == this->m_requiredFlags) &&
        ((~character->flags & this->m_forbiddenFlags) == this->m_forbiddenFlags)) {
        // Game state check: current game state should match this->m_actionId,
        // or not match this->m_altActionId, or this->m_actionId is 4
        int currentGameState = getGameStateID();
        if ((currentGameState == this->m_actionId) ||
            ((currentGameState != this->m_altActionId) && (this->m_actionId == 4))) {
            // Target ID check: character->currentTargetId must match this->m_targetId,
            // or not match this->m_altTargetId if this->m_targetId is 0
            if ((character->currentTargetId == this->m_targetId) ||
                ((character->currentTargetId != this->m_altTargetId) && (this->m_targetId == 0))) {
                // Additional conditions: character must be valid and able to act
                if ((isCharacterValid(character->stateId) != 0) &&
                    (canCharacterAct(character) != 0)) {
                    result = 1;
                }
            }
        }
    }
    return result;
}