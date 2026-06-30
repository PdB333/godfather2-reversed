// FUNC_NAME: LoopManager::resetAll
void __fastcall LoopManager::resetAll(int* timerHandle)
{
    // local_4 will hold a pointer to a temporary value (tick+10)
    int* tempPtr;

    // If the timer handle is currently active (non-zero)
    if (*timerHandle != 0) {
        // Get current time and add 10ms (possibly to schedule a one-shot cleanup)
        DWORD currentTick = GetTickCount();
        tempPtr = (int*)(currentTick + 10);

        // Schedule something 10ms in the future (likely a delayed callback)
        scheduleTimer(&tempPtr, 0); // FUN_00ab54e0

        int objId = *timerHandle; // original object handle
        if (objId != 0) {
            updateGlobalState(); // FUN_00ab72a0
            destroyObject(objId); // FUN_009c8eb0
        }

        // Clear the timer handle
        *timerHandle = 0;
    }

    // Walk the linked list of loop nodes (circular sentinel-based list)
    // g_loopHead is the sentinel node (points to itself when empty)
    Node** ppCurrent = (Node**)g_loopHead;
    while (ppCurrent != (Node**)&g_loopHead) {
        Node** ppNext = (Node**)*ppCurrent; // next node pointer
        releaseNode(ppCurrent); // FUN_009c8f10: process and free node
        ppCurrent = ppNext;
    }

    // Reset the linked list to empty state (sentinel points to itself)
    g_loopHead = (Node*)&g_loopHead;
    g_loopTail = (Node*)&g_loopHead;
    g_loopState = 6; // mark state as "idle" or "cleaned"
}