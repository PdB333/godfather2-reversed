// FUNC_NAME: EventHandler::processEvent
// Function at 0x006be4b0 - Dispatches events based on type, handling continue/end/other events.

void __thiscall EventHandler::processEvent(EventHandler* this, Event* event)
{
    EventType type = event->type;  // param_2[0]
    int* thisPtr = (int*)this;    // For offset arithmetic, not needed in clean code.

    if (type == *(int*)(this + 0x1c))  // Current event type stored at +0x1c
    {
        // Continue current event: if we have an object ID at +0x14, look it up and execute action.
        if (*(int*)(this + 0x14) != 0)
        {
            int objPtr = FUN_006b0ee0(*(int*)(this + 0x14));  // Likely getObjectById
            if (objPtr != 0)
            {
                FUN_006be3f0(*(undefined4*)(objPtr + 0x40));  // Execute action using ID at +0x40 in object
            }
        }
    }
    else if (type == kEventTypeEnd)  // e.g., DAT_0120e93c = kEventTypeEnd
    {
        // End current event: same action as above, then release the event.
        if (*(int*)(this + 0x14) != 0)
        {
            int objPtr = FUN_006b0ee0(*(int*)(this + 0x14));
            if (objPtr != 0)
            {
                FUN_006be3f0(*(undefined4*)(objPtr + 0x40));
            }
        }
        FUN_004086d0(&kEventTypeEnd);  // Release or cleanup event type data.
        return;
    }
    else if (type == kEventTypeOther)  // e.g., DAT_0112a620
    {
        // Check if the event's source object matches the current one.
        // event->data+4 is a pointer, dereference +0x38 to get source ID.
        int* eventData = (int*)event->data;  // param_2[1]
        int* sourceObj = *(int**)(eventData + 1);  // eventData[1] = pointer at +4
        int sourceId = *(int*)(sourceObj + 0x38);   // source's ID at +0x38
        if (sourceId == *(int*)(this + 0x14))        // Compare to current ID at +0x14
        {
            FUN_006be3f0(*(undefined4*)(eventData + 3)); // eventData[3] = action ID at +0xc
        }
    }
    // No explicit return for first case (continues to end)
    return;
}