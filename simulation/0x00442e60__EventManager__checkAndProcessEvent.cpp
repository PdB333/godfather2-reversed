// FUNC_NAME: EventManager::checkAndProcessEvent
void EventManager::checkAndProcessEvent() {
    // Attempt to retrieve the next pending event (returns event ID or -1 if none)
    int eventId = EventManager::getNextEvent(); // FUN_00443b40, takes this pointer from stack (implicit ECX)
    if (eventId >= 0) {
        // Process the retrieved event
        EventManager::handleEvent(); // FUN_00443af0, handles the event (likely uses this + eventId)
    }
}