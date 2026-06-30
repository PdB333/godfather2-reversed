// FUNC_NAME: StateMachine::processPendingEvent
void __fastcall StateMachine::processPendingEvent() {
    // this->m_eventSlots[0..3] are at offsets +0x67c to +0x688 (4 ints)
    // this->m_currentState at offset +0x68c
    char slotIndex;
    int eventHandle;
    uint eventData;

    // If current state is 0 or 0x48 (72), and there is at least one pending event slot non-zero
    if ((m_currentState == 0 || m_currentState == 0x48) &&
        (m_eventSlots[0] != 0 || m_eventSlots[1] != 0 || m_eventSlots[2] != 0 || m_eventSlots[3] != 0)) {
        slotIndex = 0;
        // Get the first pending event handle and its slot index
        eventHandle = getNextEventSlot(m_eventSlots, &slotIndex);
        if (eventHandle != 0) {
            eventData = 0;
            // Check if the event matches a specific hash (0x2e5f1298)
            if (matchEventByHash(eventHandle, 0x2e5f1298, &eventData)) {
                // Execute the event with the retrieved data
                executeEvent(eventData);
                // Trigger state transition or update
                triggerStateTransition();
            }
        }
    }
}