// FUNC_NAME: BufferedEventQueue::addEvent
void __thiscall BufferedEventQueue::addEvent(uint32_t eventData) {
    // Check if batching is enabled (offset +0x86c indicates if we should buffer events)
    if (this->batchingEnabled != 0) {
        // If buffer not full, store event
        if (this->eventCount < 0x200) {
            // Buffer at +0x68 is array of uint32_t with capacity 0x200
            this->eventBuffer[this->eventCount] = eventData;
            this->eventCount++;
        }
        // If buffer becomes full, flush it
        if (this->eventCount == 0x200) {
            // flushBuffer processes buffer of 0x200 entries
            this->flushBuffer(this->eventBuffer, 0x200);
            this->eventCount = 0;
        }
        return;
    }
    // If batching is disabled, forward event immediately
    this->forwardImmediate(&eventData, eventData);
}