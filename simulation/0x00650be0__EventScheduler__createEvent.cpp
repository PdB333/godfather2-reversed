// FUNC_NAME: EventScheduler::createEvent
void EventScheduler::createEvent(void)
{
    Event *newEvent;

    // Allocate 32 bytes for Event structure (0x20)
    newEvent = (Event *)FUN_009c8e50(0x20);
    if (newEvent != (Event *)0x0) {
        // Initialize fields
        newEvent->field_4 = 0;      // +0x04
        newEvent->field_8 = 0;      // +0x08
        newEvent->field_10 = 0;     // +0x10
        newEvent->field_C = 1;      // +0x0C (set to 1, possible state/count)
        newEvent->vtable = (uint32_t *)&PTR_LAB_00e43038; // +0x00 vtable pointer
        newEvent->someTable = (uint32_t *)&PTR_LAB_00e43064; // +0x18 secondary vtable/table
        newEvent->someFunction = (uint32_t)&LAB_00652770; // +0x1C function pointer
        newEvent->selfPointer = &newEvent->someTable; // +0x14 points to someTable (offset 0x18)
        // Call initialization routine with the constructed event
        FUN_0064ef60(newEvent);
        return;
    }
    // Allocation failed, call init with null
    FUN_0064ef60(0);
    return;
}