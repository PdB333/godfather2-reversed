// FUNC_NAME: AnimationController::processEvent
// Address: 0x005913b0
// Processes an animation event: dispatches to a registered handler, then normalizes the result into an output array.

typedef void (__thiscall *EventHandlerFunc)(int entity, int eventId, float* value);

extern int gEventCount;               // DAT_01205574
extern void* gEventDispatchTable;     // DAT_01205570, base of event handler table (4-byte header, then 0xC entries)

void __thiscall AnimationController::processEvent(float inputValue, int entity, int eventData, int* outputArray)
{
    // Entity state check: offset 0x7c -> field at +0x2c must not be 2
    int* entityStateBlock = reinterpret_cast<int*>(entity + 0x7c);
    int stateFlags = entityStateBlock[0x2c / 4];
    if (stateFlags != 2)
    {
        // Event data structure: offset +4 points to an int array (event descriptor)
        int* eventDescriptor = *reinterpret_cast<int**>(eventData + 4);
        int eventId = eventDescriptor[0];

        // Validate event index against global table size
        if (eventId >= 0 && eventId < gEventCount)
        {
            // Fetch handler from dispatch table (first 4 bytes are header, then each entry is 0xC bytes)
            int handlerEntryOffset = 4 + eventId * 0xC;
            EventHandlerFunc handler = *reinterpret_cast<EventHandlerFunc*>(
                reinterpret_cast<char*>(gEventDispatchTable) + handlerEntryOffset
            );
            if (handler != nullptr)
            {
                // Call the handler; it may modify the input value
                float localValue = inputValue;
                handler(entity, eventId, &localValue);

                // Extract range and output index from event descriptor
                int rangeMin = eventDescriptor[1];
                int rangeMax = eventDescriptor[2];
                int outputSlot = eventDescriptor[3];

                // Bounds check on output array (param_4[1] is capacity?)
                if (outputArray[1] <= outputSlot)
                {
                    int dummy = 0;
                    FUN_00591c00(&dummy); // error handler (likely assert or log)
                }

                // Normalize (localValue - min) / (max - min) and store into output array
                float range = static_cast<float>(rangeMax - rangeMin);
                if (range != 0.0f)
                    outputArray[outputSlot] = (localValue - static_cast<float>(rangeMin)) / range;
                else
                    outputArray[outputSlot] = 0.0f;
            }
        }
    }
}