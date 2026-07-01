// FUNC_NAME: EventHandler::handleEvent
void __thiscall EventHandler::handleEvent(EventHandler* this, int* eventData)
{
    // This function appears to be a member of a class that is embedded within a larger object.
    // The 'this' pointer points to an offset 0x3c into the outer object.
    // The outer object's vtable is at (this - 0x3c).
    // The offset 0x224 is a member of this embedded class (likely an event ID or state).

    // Call a function on the event data (maybe copy or validate)
    FUN_008dc280(eventData);

    // Check if the stored event ID matches the incoming event's ID
    if (*(int*)(this + 0x224) == *eventData) {
        char isActive = FUN_00481640(); // Checks global state (e.g., game paused or active)
        if (isActive != '\0') {
            // If the game is in a special state, call a separate handler and return
            FUN_008e0290(); // Possibly reset or cancel event
            return;
        }
        // Otherwise, call a virtual function from the outer class's vtable at offset 0x1b4
        // This vtable pointer is at (this - 0x3c)
        (**(code**)(*(int*)(this - 0x3c) + 0x1b4))();
    }
    return;
}