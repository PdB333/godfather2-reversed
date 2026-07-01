// FUNC_NAME: EventHandlerList::handleEvent

// Function address: 0x008352e0
// Role: Event dispatcher for a list of listeners. Handles either a removal event (identified by a specific constant) or broadcasts a generic event to all registered listeners.

// Known class members:
// this+0x14: void** listenerArray   // pointer to array of listener pointers
// this+0x18: int   listenerCount    // current number of listeners

// External functions (to be defined elsewhere):
// void* FUN_00834f80(void* handle);  // resolve handle to object pointer
// byte FUN_008279a0(void* eventData); // process event on a listener (returns status)

#define REMOVAL_EVENT_CONSTANT 0x83BEF348  // -0x7c410cb8 as unsigned

byte __thiscall EventHandlerList::handleEvent(int eventType, void* eventData)
{
    byte overallResult = 0;

    if (eventType == REMOVAL_EVENT_CONSTANT)
    {
        // This event signals removal of a specific listener from the list
        void* listener = FUN_00834f80(eventData);
        if (listener != (void*)0x0)
        {
            int foundIndex = 0;
            if (this->listenerCount != 0)
            {
                // Linear search for the listener pointer
                for (void** current = this->listenerArray; *current != listener; current++)
                {
                    foundIndex++;
                }

                // Replace the found element with the last element (if not already last)
                if (foundIndex != this->listenerCount - 1)
                {
                    this->listenerArray[foundIndex] = this->listenerArray[this->listenerCount - 1];
                }
                this->listenerCount--;
            }

            // Call the first virtual function of the listener (likely a release/destructor) with argument 1
            (*(void (**)(void*, int))listener)(listener, 1);
            return 1;
        }
    }
    else
    {
        // Generic event: broadcast to all listeners
        unsigned int i = 0;
        if (this->listenerCount != 0)
        {
            do
            {
                byte subResult = FUN_008279a0(eventData);
                i++;
                overallResult |= subResult;
            } while (i < (unsigned int)this->listenerCount);
        }
    }

    return overallResult;
}