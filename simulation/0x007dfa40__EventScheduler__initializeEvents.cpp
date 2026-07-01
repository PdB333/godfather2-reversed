// FUNC_NAME: EventScheduler::initializeEvents
void __thiscall EventScheduler::initializeEvents(EventScheduler *this) {
    // Set vtable to base class (e.g., EventSchedulerBase)
    this->vtable = &PTR_LAB_00d6f87c;

    // Register three events: likely EVENT_TYPE_UNKNOWN_0x28, EVENT_NONE, EVENT_TYPE_UNKNOWN_0x4d
    FUN_007f6420(0x28);
    FUN_007f6420(0x0);
    FUN_007f6420(0x4d);

    // Switch to derived vtable (e.g., EventScheduler)
    this->vtable = &PTR_LAB_00d6b95c;

    // Final construction/initialization (e.g., initialize internal state)
    FUN_0080ea60();
}