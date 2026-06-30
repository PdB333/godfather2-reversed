// FUNC_NAME: EventManager::dispatchEvent

void EventManager::dispatchEvent(int eventId)
{
    uint index = 0;
    if (g_eventCount != 0) {
        do {
            // g_eventTable is an array of pairs: [eventId, objectPtr]
            if (g_eventTable[index].eventId == eventId) {
                // Call virtual method at offset 0xC on the object (likely handleEvent)
                (*(void (**)(void))(*(int *)g_eventTable[index].objectPtr + 0xC))();
                // After handling, process pending events or cleanup
                EventManager::processPendingEvents();
                return;
            }
            index++;
        } while (index < g_eventCount);
    }
    return;
}