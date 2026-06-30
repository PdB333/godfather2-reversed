// FUNC_NAME: Event::reset (likely a method of an event/timer object in EARS framework)

void __thiscall Event::reset(Event* thisPtr)
{
    // Check if callback function is set
    if (thisPtr->callbackFunction != nullptr) {
        // Only invoke the callback if the state is not 0 (uninitialized), 3 (stopped), or 4 (destroyed)
        int currentState = thisPtr->state;
        if (currentState != 0 && currentState != 3 && currentState != 4) {
            // Notify the callback with event type 3 (e.g., EVENT_STOP)
            thisPtr->callbackFunction(thisPtr->callbackContext, 3, thisPtr->callbackUserData);
        }
        // Clear callback data
        thisPtr->callbackUserData = nullptr;
        thisPtr->callbackFunction = nullptr;
    }

    // Free a sub-object if present (e.g., an associated allocation)
    if (thisPtr->subObject != nullptr) {
        FUN_004daf90(thisPtr->subObject); // likely a cleanup/destructor call
        thisPtr->subObject = nullptr;
    }

    // Zero out additional state fields
    thisPtr->callbackContext = nullptr;
    thisPtr->field_20 = 0;
    thisPtr->field_24 = 0;
    thisPtr->field_2C = 0;
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(thisPtr) + 0x35) = 0; // boolean flag

    // Reset state to 3 (STOPPED)
    thisPtr->state = 3;

    // Invalidate timer handle
    thisPtr->timerHandle = -1;
}