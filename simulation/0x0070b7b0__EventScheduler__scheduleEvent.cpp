// FUNC_NAME: EventScheduler::scheduleEvent
void __fastcall EventScheduler::scheduleEvent(void* param_1) // possibly a "this" or an object pointer
{
    EventScheduler* scheduler = EventScheduler::getInstance(); // FUN_00471610
    TimedEvent event; // stack-local structure
    void* listHead = nullptr;

    // Initialize event's vtable and type ID
    event.vtable = &PTR_FUN_00d5dbbc; // +0x24? or first member
    event.typeId = 0x388c794f; // +0x20

    // Determine list node pointer from param_1
    if (param_1 == nullptr) {
        listHead = nullptr;
    } else {
        listHead = (void*)((uint8_t*)param_1 + 0x48); // param_1->listField (offset 0x48)
    }

    // Insert this event into a doubly linked list (head manipulation)
    if (listHead != nullptr) {
        event.prev = *(void**)((uint8_t*)listHead + 4); // old prev
        *(void**)((uint8_t*)listHead + 4) = &event.listNode; // new link (seems to point to stack, likely a bug or embedded node)
    }

    // Read current simulation time
    event.timestamp = *(uint64_t*)((uint8_t*)scheduler + 0x30); // +0x30 (low part), +0x38 (high part)
    event.contextData = *(uint32_t*)((uint8_t*)scheduler + 0x38); // +0x38 (maybe part of time or separate)

    // Additional event fields
    event.flags = 1; // local_8 = 1
    event.globalRef = DAT_01205228; // some global data
    event.listNodeForStack = &event.vtable; // local_2c = &local_24 (pointing to the vtable pointer)
    event.unknown = DAT_0112ad8c; // local_30
    event.unknownByte = 0; // local_28

    // Register the event with the scheduler (second param 0 might be priority or flag)
    EventScheduler::addEvent(&event, 0); // FUN_00408a00

    // If we had a listHead, clean up the list insertion? (FUN_004daf90)
    if (listHead != nullptr) {
        EventScheduler::removeListNode(&event.listNode); // FUN_004daf90 (likely removes the temporary list node)
    }
}