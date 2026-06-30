// FUNC_NAME: EventScheduler::executePendingEvents
void __fastcall EventScheduler::executePendingEvents(EventScheduler* thisPtr) {
    // +0x0C: number of pending events to process
    uint32_t eventCount = *(uint32_t*)((uint8_t*)thisPtr + 0x0C);
    
    if (eventCount != 0) {
        for (uint32_t i = 0; i < eventCount; i++) {
            // Calls function at 0x006b6110 to execute a single pending event
            executeSingleEvent();
        }
    }
}