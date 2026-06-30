// FUNC_NAME: Player::updateAction
void __thiscall Player::updateAction(void)
{
    int newStateId;
    int gameplayState;
    void *newAction;

    // If there is an active action object, update its counter and state
    if (this->m_pCurrentAction != 0) {
        this->m_actionCounter++;
        newStateId = getActionState(this->m_pCurrentAction);
        this->m_currentActionId = newStateId;
        // State 0xD (13) signals action completion? Clear the action.
        if (newStateId == 0xD) {
            this->m_pCurrentAction = 0;
            this->m_actionCounter = 0;
        }
    }

    // If no active action, decide what to start based on global gameplay state
    if (this->m_pCurrentAction == 0) {
        gameplayState = getGameplayState();
        if (gameplayState == 0xE) {
            newAction = createAction(0);
            this->m_pCurrentAction = newAction;
        }
        else if (gameplayState == 0xF) {
            newAction = createAction(1);
            this->m_pCurrentAction = newAction;
        }
        else {
            // No special action; just store the gameplay state as current action ID
            this->m_currentActionId = gameplayState;
        }

        // If we just created an action, initialize its counter and state
        if (this->m_pCurrentAction != 0) {
            this->m_actionCounter = 0;
            newStateId = getActionState(this->m_pCurrentAction);
            this->m_currentActionId = newStateId;
        }
    }
}