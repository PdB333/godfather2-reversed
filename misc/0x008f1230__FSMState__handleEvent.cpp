// FUNC_NAME: FSMState::handleEvent
void __thiscall FSMState::handleEvent(int* pEvent) {
    char canTransition;
    // Local event structure to queue
    struct EventData {
        int type;      // +0x00
        int data;      // +0x04
        char flag;     // +0x08
    } event;

    // Preprocess the incoming event pointer (maybe validate or decode)
    EventManager::preprocessEvent(pEvent);

    if (*pEvent == *(int*)(this + 0x14)) { // compare eventID with expected event stored at +0x14
        // Get parent state machine, which is at a fixed offset before this object
        FSMStateMachine* parent = (FSMStateMachine*)(this - 0x3C);
        canTransition = parent->isTransitionAllowed(); // method at 0x008F1160

        if (canTransition == 0) {
            event.type = *(int*)(this + 0x1C); // event type to send (stored at +0x1C)
            event.data = 0;
            event.flag = 0;
            // Queue the event to the event manager (bool parameter may be priority)
            EventManager::queueEvent(&event, 0);
        }
    }
}