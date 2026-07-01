// FUNC_NAME: EventScheduler::postEvent
// Address: 0x008490a0
// Reads a value from this+0x7c (likely a delay or event ID), constructs an event structure, and schedules it via scheduleEvent().

struct EventData {
    uint32_t value;   // +0x00
    uint32_t zero;    // +0x04
    uint8_t  flag;    // +0x08
};

void __fastcall EventScheduler::postEvent(void* this) {
    // Grab the event value from offset 0x7c
    uint32_t eventValue = *(uint32_t*)((char*)this + 0x7c);

    // Prepare an event data record
    EventData data;
    data.value = eventValue;
    data.zero  = 0;
    data.flag  = 0;

    // Schedule the event with immediate flag disabled (0)
    scheduleEvent(&data, 0);
}