// FUNC_NAME: EventScheduler::createTimedEvent
struct TimedEvent {
    int32_t type;          // +0x00
    int32_t timeSeconds;   // +0x04
    int32_t flags;         // +0x08
    int32_t someParam;     // +0x0C
    char nameBuffer[0x104]; // +0x10
};

void __thiscall EventScheduler::createTimedEvent(TimedEvent* outEvent, int param3, int param4) {
    // param3 is not used
    outEvent->type = 6;
    
    // Read 64-bit milliseconds from this+0x20 (low) and this+0x24 (high)
    uint32_t lowMillis = *(uint32_t*)(this + 0x20);
    int32_t highMillis = *(int32_t*)(this + 0x24);
    
    // Add 500ms for rounding to nearest second, then convert to seconds
    uint64_t totalMillis = ((uint64_t)highMillis << 32) + lowMillis + 500;
    outEvent->timeSeconds = (uint32_t)(totalMillis / 1000);
    
    outEvent->flags = 0x40000;
    outEvent->someParam = param4;
    
    // Zero out the name buffer and initialize it
    memset(outEvent->nameBuffer, 0, 0x104);
    FUN_00565090(outEvent->nameBuffer); // Initializes the buffer (likely a name string)
}