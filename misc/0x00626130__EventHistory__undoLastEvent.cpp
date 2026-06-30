// FUNC_NAME: EventHistory::undoLastEvent
int EventHistory::undoLastEvent(int eventIndex) {
    // this offsets:
    // +0x08: currentEventPtr (pointer to current 8-byte event in the event list)
    // +0x0C: eventArrayBase (base pointer to array of events, each 8 bytes)
    // +0x10: fallbackPointer (some alternative pointer used when previous event is null)

    int* currentEvent;
    if (eventIndex < 1) {
        // Allocate a new event from some pool or get a generic sentinel
        currentEvent = (int*)allocateEvent(); // FUN_00625430
    } else {
        // Index into the event array, offset by -8 to make it 1-based
        int* base = *(int**)(this + 0x0C);
        currentEvent = (int*)((int)base - 8 + eventIndex * 8);
    }

    // Get the previous event (immediately before the current pointer)
    int* previousEvent = (int*)(*(int**)(this + 0x08) - 8);
    if (*previousEvent == 0) {
        // If previous event is empty, use the fallback pointer + 0x34
        previousEvent = (int*)(*(int**)(this + 0x10) + 0x34);
    }

    // Only undo if current event type is 5 or 7
    if (*currentEvent != 5 && *currentEvent != 7) {
        // Move current pointer back (pop current event without action)
        *(int**)(this + 0x08) = *(int**)(this + 0x08) - 8;
        return 0;
    }

    // Restore the object's field at offset 8 from the previous event's second int
    *(int*)(currentEvent[1] + 8) = previousEvent[1];

    // Move current pointer back
    *(int**)(this + 0x08) = *(int**)(this + 0x08) - 8;
    return 1;
}