// FUNC_NAME: EventSource::PushEvent

// Global queue manager structure (DAT_01206880)
// +0x14: current write pointer (stack pointer) for the event queue buffer
extern char* gQueueManager; // 0x01206880

// Global queue index override (DAT_01163d94); if non-zero overrides the queue index argument
extern int gQueueIndexOverride; // 0x01163d94

// VTable pointer for base event type (PTR_LAB_01123c4c)
extern void* gEventVTable; // 0x01123c4c

// Forward declaration of event validation function (FUN_00489a80)
// Returns non-zero if the event is valid for queuing
int IsEventValid(void* event);

// Method: pushes the event stored at this->eventField onto the global event queue.
// If gQueueIndexOverride is non-zero, it uses that; else uses the provided queueIndex.
void __thiscall EventSource::PushEvent(int queueIndex)
{
    int actualQueueIndex = gQueueIndexOverride;
    if (gQueueIndexOverride == 0) {
        actualQueueIndex = queueIndex;
    }

    // Retrieve the event pointer from this object at offset 0x1C
    void* eventPtr = *(void**)((char*)this + 0x1C);

    // Validate the event; only push if valid
    if (IsEventValid(eventPtr)) {
        // Current write position in the queue buffer
        uint32_t* stackPtr = *(uint32_t**)(gQueueManager + 0x14);

        // Write the vtable pointer for the event entry
        *stackPtr++ = (uint32_t)(&gEventVTable);

        // Write the event data pointer
        *stackPtr++ = (uint32_t)eventPtr;

        // Update the global stack pointer
        *(uint32_t**)(gQueueManager + 0x14) = stackPtr;

        // Note: actualQueueIndex is not used in this raw version;
        // it might be used in the validation or elsewhere in the system.
    }
}