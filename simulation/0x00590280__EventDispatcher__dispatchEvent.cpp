// FUNC_NAME: EventDispatcher::dispatchEvent
void EventDispatcher::dispatchEvent(Event* event, int arg3, int arg4, int arg5, uint mask, int arg7)
{
    // Save the original mask before potential modification by callbacks
    uint originalMask = mask;

    // Check if bits 2 or 4 (0x14) are set; if not, attempt to dispatch to handlers
    if ((mask & 0x14) == 0) {
        // event->+0x04 is a pointer to an array of two type IDs
        int* typeIds = *(int**)(event + 4);

        // Dispatch using first type ID
        int firstType = typeIds[0];
        if (firstType >= 0 && firstType < g_eventHandlerCount) {
            // Each dispatch table entry is 12 bytes: unknown at +0, func1 at +4, func2 at +8
            DispatchEntry* entry = &g_eventHandlerTable[firstType];
            if (entry->func1) {
                entry->func1(this, firstType, &mask);
            }
        }

        // Dispatch using second type ID
        int secondType = typeIds[1];
        if (secondType >= 0 && secondType < g_eventHandlerCount) {
            DispatchEntry* entry = &g_eventHandlerTable[secondType];
            if (entry->func2) {
                entry->func2(this, secondType, &mask);
            }
        }
    }

    // Call the base event handler with the original mask (ignoring any modifications from callbacks)
    callBaseHandler(event, arg3, arg4, arg5, originalMask, arg7);
}