// FUNC_NAME: CSentient::processEvent
undefined4 __thiscall CSentient::processEvent(int thisPtr, undefined4 param_2, uint param_3, undefined4 param_4)
{
    char flagResult;
    undefined4 eventResult;
    int actionPtr;
    undefined1 eventNameBuffer[8];

    // Process base event (possibly animation or sound trigger)
    eventResult = processBaseEvent(param_2, param_3, param_4);

    // Test bit 4 of the event flags
    flagResult = testFlag((param_3 >> 4) & 1);
    if (flagResult != '\0') {
        // Get pointer to behavior component at +0x138
        if (*(int *)(thisPtr + 0x138) == 0) {
            actionPtr = 0;
        } else {
            actionPtr = *(int *)(thisPtr + 0x138) + 0x58;
        }
        // Execute action (e.g., play animation, sound, or state change)
        executeAction(actionPtr);
        // Retrieve event name into buffer (e.g., for debug or logging)
        getEventName(param_4, eventNameBuffer);
    }

    // Test bit 5 of the event flags
    flagResult = testFlag((param_3 >> 5) & 1);
    if (flagResult != '\0') {
        // Check a byte flag at +0x128 (e.g., bIsDead, bIsActive, etc.)
        testFlag(*(undefined1 *)(thisPtr + 0x128));
    }

    return eventResult;
}