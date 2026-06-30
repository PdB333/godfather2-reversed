// FUNC_NAME: GameStateManager::processPendingEvents
void GameStateManager::processPendingEvents(int index, int count)
{
    // g_pGameStateManager is a global pointer to the GameStateManager instance
    // offset 0x565 is m_currentState (byte)
    byte currentState = *(byte*)(g_pGameStateManager + 0x565);
    if (currentState == 0x12) // state 0x12 is "idle" or "done"
        return;

    if (count < 0xF) // only process if count is less than 15 (valid pending events)
    {
        // Get the state-specific handler for the current state
        // FUN_00411070 returns a pointer to a StateHandler for the given state byte
        StateHandler* stateHandler = (StateHandler*)FUN_00411070(currentState);
        FUN_004958a0(); // secondary processing (unknown, possibly cleanup)
    }

    // g_pendingEventTable is a global array indexed by (index * 2) -> 4-byte entries
    // Each entry is an event ID or object handle
    int eventId = *(int*)(&g_pendingEventTable[index * 2]);

    // Retrieve the state handler again (possibly another instance or same)
    StateHandler* stateHandler2 = (StateHandler*)FUN_00411070(currentState);
    // Call the vtable function at offset 8 (3rd virtual function: processEvent)
    // Passing the eventId
    stateHandler2->vtable->processEvent(eventId);
}