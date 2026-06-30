// FUNC_NAME: TimerQueue::insertSorted
void TimerQueue::insertSorted(void)
{
    TimerNode* thisNode = reinterpret_cast<TimerNode*>(this);
    TimerNode* newNode = nullptr;

    // If the node is not active (offset 0x1c), fall back to default insertion
    if (thisNode->flags == 0) {
        FUN_0060ba00(); // fallback insertion (maybe unsorted)
        return;
    }

    // If the node's next pointer (offset 0x04) is null, we need to allocate a new copy
    if (thisNode->next == nullptr) {
        TimerNode* allocedNode = reinterpret_cast<TimerNode*>(
            (**(code**)*DAT_01205868)(0x30, &local_alloc_size)
        );
        // Copy the entire TimerNode (5 qwords = 40 bytes) to the new buffer
        *allocedNode = *thisNode;
        allocedNode->self = allocedNode; // offset 0x20: self-pointer
        thisNode = allocedNode;
    }

    TimerNode* listHead = reinterpret_cast<TimerNode*>(&local_list_head);
    listHead->next = thisNode; // set up local list head

    EnterCriticalSection(&g_timerListLock);

    // Iterate over the global sorted list (DAT_012224ac points to head node)
    TimerNode** current = reinterpret_cast<TimerNode**>(DAT_012224ac);
    while (*current != nullptr) {
        TimerNode* curNode = *current;
        if (thisNode->key < curNode->key) { // compare key at offset 0x14
            FUN_0060d260(&listHead, &local_list_head); // insert before current
            LeaveCriticalSection(&g_timerListLock);
            return;
        }
        current = reinterpret_cast<TimerNode**>(curNode->next);
    }

    // If key is greater or equal to all, append at end
    FUN_0060d150(&local_list_head);
    LeaveCriticalSection(&g_timerListLock);
}