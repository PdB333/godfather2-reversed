// FUNC_NAME: EventScheduler::processTimedEvent
// Address: 0x0069b510
// This function schedules a timed callback event and then immediately processes the event queue.
// It is likely used to trigger a callback after a specified delay (param_2 in seconds).
// The callback function pointer and context are stored in a local structure (local_10).
// After setting up the event and processing any pending events, if the callback handle is non-zero,
// the function pointer is invoked with the handle as argument.

void __thiscall EventScheduler::processTimedEvent(void *this, float delaySeconds) {
    // Local structure for event scheduling (size 0xC bytes)
    // +0x00: eventHandle - handle/id for the scheduled event (used as context for callback)
    // +0x04: unknown1
    // +0x08: unknown2
    int eventData[3];
    // Function pointer for the callback
    void (*callback)(int) = nullptr;

    // Initialize the event data
    eventData[0] = 0;
    eventData[1] = 0;
    eventData[2] = 0;

    // Schedule an event with the given delay (converted to double)
    // DAT_00d5cee4 likely points to a global event manager or a vtable for event handling
    ScheduleEvent(eventData, &g_EventManager, (double)delaySeconds);

    // Process any pending events (update timers, fire callbacks)
    ProcessEvents();
    // Finalize or clean up after event processing
    FinalizeEventProcessing();

    // If the event handle is non-zero, invoke the callback with the handle
    if (eventData[0] != 0) {
        callback(eventData[0]);
    }
}