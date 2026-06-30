// FUNC_NAME: TimedEventManager::processElapsedEvents
void TimedEventManager::processElapsedEvents(TimedEventManager *this)
{
    uint i;
    char elapsed;

    i = 0;
    if (*(int *)(this + 0x94) != 0) {
        while (elapsed = checkEventElapsed(this), elapsed == '\0') {
            i = i + 1;
            if (*(uint *)(this + 0x94) <= i) {
                return;
            }
        }
        // Subtract the event's amount from the running total
        // Event structure at offset +0x24, each event 0x24 bytes
        // Event data: +0x00? -> used here: *(int *)(this + 0x24 + i * 0x24)
        *(int *)(this + 0x98) = *(int *)(this + 0x98) - *(int *)(this + 0x24 + i * 0x24);
        finalizeEventProcessing(this);
    }
    return;
}