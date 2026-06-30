// FUNC_NAME: WorkQueue::flushPendingWork
void __thiscall WorkQueue::flushPendingWork() {
    // Check if any flag prevents processing (e.g., paused, locked)
    if (m_bProcessingLocked == 0 && m_bPaused == 0) {
        int workCount = m_nPendingWorkCount; // +0x74: number of pending items to process
        m_nPendingWorkCount = 0; // Reset count after acquiring

        // Prepare the queue for batch processing (e.g., acquire lock, begin transaction)
        this->preProcessWork(); // calls FUN_006b2f70

        // Process each deferred work item
        while (workCount != 0) {
            this->processWorkItem(); // calls FUN_006b4da0
            workCount--;
        }
    }
}