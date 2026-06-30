// FUNC_NAME: GameStateManager::processStateTransition

void GameStateManager::processStateTransition(int newState)
{
    // Call base class initialization
    baseInit(newState);

    // Global game state structure (unaff_EDI)
    // Offset: +0x00 = currentState, +0x04 = param (newState?), +0x0C = field3, +0x10 = field4
    if (gGameState->currentState == 9) // e.g., STATE_INIT_DONE
    {
        finishState();
    }

    // Check if a transition is needed (field3 != field4)
    if (gGameState->field3 == gGameState->field4)
        goto skipTransition;

    int canTransition = checkTransition(1); // e.g., check if allowed to leave current state
    if (canTransition == 0)
    {
        canTransition = checkTransition(0); // check if allowed to enter new state
        if (canTransition == 0)
            goto skipTransition2;
    }

    // Transition is allowed
    if (gGameState->currentState != 9)
    {
        cleanupState();
    }

    // Send state exit message (event type 0x42 with state ID)
    this->m_timer = this->m_savedTimer; // +0x18, +0x1c: timer or state duration
    sendMessage((newState << 24) | 0x42, *(int*)(*(int*)(this + 0x0C) + 0x08)); // +0x0C is pointer to another structure

    // Send state enter message (0x8002 type)
    this->m_timer = this->m_savedTimer;
    sendMessage((newState << 24) | 0x8002, *(int*)(*(int*)(this + 0x0C) + 0x08));

    finishState();

skipTransition2:
    // Reset timer
    this->m_timer = this->m_savedTimer;
    runStep(); // e.g., continue processing
    runStep();

skipTransition:
    // Mark transition as complete
    gGameState->field3 = -1;
    gGameState->field4 = -1;
    gGameState->param = newState; // +0x04
    gGameState->currentState = 0x0B; // e.g., STATE_IDLE
    return;
}