// FUNC_NAME: TimerManager::resetSlotsAndClearGlobalList
void __fastcall TimerManager::resetSlotsAndClearGlobalList(int* pTimerSlot)
{
    int* currentSlot = pTimerSlot;
    if (*pTimerSlot != 0)
    {
        DWORD currentTime = GetTickCount();
        int timeOutAddr = currentTime + 10; // 10 ms timeout
        WaitForTimerSlot(&timeOutAddr, 0); // wait for slot to become free
        int timerHandle = *pTimerSlot;
        if (timerHandle != 0)
        {
            SyncThreadState();   // ensure thread safety
            DeleteTimerObject(timerHandle); // free timer resource
        }
        *pTimerSlot = 0; // clear slot
    }

    // Iterate and remove all nodes from the global timer node list
    Node** currentNode = reinterpret_cast<Node**>(g_timerNodeListHead);
    while (currentNode != &g_timerNodeListHead)
    {
        Node** nextNode = reinterpret_cast<Node**>(*currentNode);
        RemoveTimerNode(currentNode); // unlink from list
        currentNode = nextNode;
    }

    // Reset the global circular doubly linked list to empty
    g_timerNodeListHead = reinterpret_cast<Node*>(&g_timerNodeListHead);
    g_timerNodeListTail = reinterpret_cast<Node*>(&g_timerNodeListHead);
    g_timerNodeListCount = 6; // reset count to 6 (probably list version or initial count)
}