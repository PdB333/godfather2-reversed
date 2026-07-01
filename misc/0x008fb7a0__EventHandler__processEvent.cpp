// FUNC_NAME: EventHandler::processEvent
void __thiscall EventHandler::processEvent(int thisPtr, int *eventMsg)
{
    int eventId = *eventMsg;
    int *extraData; // could be param2[1]

    if (eventId == *(int *)(thisPtr + 0x1b4)) {
        // Clear bit 0 of flags at +0x134
        *(uint *)(thisPtr + 0x134) &= 0xfffffffe;
        destroyEvent(eventMsg);
        return;
    }
    if (eventId == *(int *)(thisPtr + 0x1bc)) {
        // Set some global state (1,1)
        setGlobalState(1, 1);
        setOtherState(0);
        // Set bit 0 of flags
        *(uint *)(thisPtr + 0x134) |= 1;
        destroyEvent(eventMsg);
        return;
    }
    if ((eventId == DAT_0112b36c) || (eventId == DAT_0112fc60)) {
        setGlobalState(0, 1);
        setOtherState(1);
    }
    else if (eventId == DAT_0112fea0) {
        extraData = eventMsg + 1;
        if (*extraData != 0) {
            int someValue = *(int *)(*extraData + 0x54);
            if (someValue == 0) {
                setGlobalState(0, 1);
                setOtherState(1);
                // Compute float at +0x3f4 from some data
                *(float *)(thisPtr + 0x3f4) = (*(float *)(*extraData + 0x90) + *(float *)(*extraData + 0x8c)) * _DAT_00d5c458;
                processNestedEvent(*extraData, 1);
                destroyEvent(eventMsg);
                return;
            }
            // Here someValue is non-zero; check if it equals 2 (via CONCAT31 trick)
            setAnotherState(CONCAT31((int3)((uint)someValue >> 8), someValue == 2), 1);
            destroyEvent(eventMsg);
            return;
        }
    }
    else if (eventId == DAT_0112b53c) {
        // Compute a pointer offset from global DAT_012233a0
        if (**(int **)(DAT_012233a0 + 4) == 0) {
            *(int *)(thisPtr + 0x124) = 0;
        } else {
            *(int *)(thisPtr + 0x124) = **(int **)(DAT_012233a0 + 4) - 0x1f30;
        }
        clearEventId(DAT_0112b53c);
        destroyEvent(eventMsg);
        return;
    }
    // Default: destroy the event
    destroyEvent(eventMsg);
}