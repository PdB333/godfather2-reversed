// FUNC_NAME: EventQueue::ProcessAllEvents
void __fastcall EventQueue::ProcessAllEvents(int* this)
{
    int initialCount;
    int remainingIterations;

    // Acquire lock on the queue's critical section
    EnterCriticalSection(&g_eventQueueCriticalSection); // Assuming FUN_00ab4db0

    remainingIterations = this[0xCA]; // m_nPendingEventsCount at +0x328
    initialCount = remainingIterations;

    // Process events while there are events remaining and we haven't exceeded the initial count
    for (; (initialCount != 0 && (0 < remainingIterations)); remainingIterations = remainingIterations - 1) {
        // Call virtual function at vtable +0x40 (ExecuteEvent) with the current event pointer
        (this->vtable->ExecuteEvent)(this[0x8A]); // m_pCurrentEvent at +0x228
        initialCount = this[0xCA]; // Reload count in case it changed during execution
    }

    // Clear processing state and count
    this[0x89] = 0; // m_bIsProcessing at +0x224
    this[0xCB] = 0; // m_nProcessedCount at +0x32C

    // Release lock
    LeaveCriticalSection(); // Assuming FUN_00ab4e70
}