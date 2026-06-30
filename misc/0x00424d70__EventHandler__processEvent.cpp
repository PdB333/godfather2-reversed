// FUNC_NAME: EventHandler::processEvent
void __thiscall EventHandler::processEvent(int thisPtr, int* pEventType)
{
    // +0x16c: reentrant flag (non-zero prevents processing)
    if (*(int*)(thisPtr + 0x16c) != 0) {
        return;
    }

    if (*pEventType == DAT_012069d4) {
        // Event type A: perform special action
        FUN_004252e0();
        // Fall through to general handler
    } else if (*pEventType == DAT_012069ec) {
        // Event type B: check flag at +0x168 (byte, usually indicates some state)
        if (*(char*)(thisPtr + 0x168) == '\0') {
            // Flag not set, skip special action
            goto commonHandler;
        }
        // Flag set, still do special action
        FUN_004252e0();
    } else {
        // Unknown event type, ignore
        return;
    }

commonHandler:
    // +0x168: byte flag (if zero, special action is skipped for type B)
    // General event handling (e.g., dispatch, update)
    FUN_00425410(thisPtr);
}