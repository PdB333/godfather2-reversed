// FUNC_NAME: EventTrigger::executeCallback

void EventTrigger::executeCallback()
{
    // +0x50: Pending action ID (short), cleared after execution
    short pendingId = *(short *)(this + 0x50);
    if (pendingId != 0)
    {
        // +0x54: Function pointer for the callback
        auto callback = *(void(__thiscall **)(int, int, short))(this + 0x54);
        if (callback != nullptr)
        {
            int baseParam;
            // +0x24: Flag choosing which context pointer to use
            if (*(char *)(this + 0x24) != '\0')
            {
                // +0x20: Pointer to primary context (e.g., game object)
                baseParam = *(int *)(*(int *)(this + 0x20) + 0x444);
            }
            else
            {
                // +0x1c: Pointer to secondary context (e.g., another object)
                baseParam = *(int *)(*(int *)(this + 0x1c) + 0x444);
            }
            // +0x4c: Additional parameter (e.g., target ID, source index)
            callback(baseParam, *(int *)(this + 0x4c), pendingId);
        }
        else
        {
            // Fallback: log or default handler (0xd = error code, 0x18 = size)
            FUN_0060cc10(0xd, pendingId, *(int *)(this + 0x4c), 0x18);
        }
        // Clear the pending ID after execution
        *(short *)(this + 0x50) = 0;
    }
}