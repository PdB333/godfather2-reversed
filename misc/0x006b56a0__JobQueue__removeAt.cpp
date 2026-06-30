// FUNC_NAME: JobQueue::removeAt
void __thiscall JobQueue::removeAt(uint index)
{
    // Remove element at index from the dynamic array
    uint* elementPtr = *(uint**)(this + 0xA8);  // +0xA8: pointer to array of element pointers
    void* removedElement = (void*)elementPtr[index];
    int count = *(int*)(this + 0xAC);           // +0xAC: current number of elements

    if (index != count - 1)
    {
        // Swap with the last element to avoid shifting
        elementPtr[index] = elementPtr[count - 1];
    }
    *(int*)(this + 0xAC) = count - 1;           // Decrement count

    // If auto-release flag is set, release the removed element
    if (*(int*)(this + 0xFC) != 0)              // +0xFC: flag indicating if elements should be released
    {
        releaseObject(removedElement);          // FUN_006bebf0 – release the element (e.g., delete)
    }

    // Determine how to handle the removed element based on shutdown state and thread
    if (isShuttingDown() == 0)                  // FUN_00791230: check if game is shutting down
    {
        if (isMainThread() != 0)                // FUN_00791300: check if we are on the main thread
        {
            if (someCondition() != 0)           // FUN_007f47a0: additional condition
            {
                yield(0);                       // FUN_00790110(0): yield to other threads
                processNext(this);              // FUN_00791350: process next pending job
                goto checkIdle;
            }
        }
        destroyObject(removedElement);          // FUN_006b4c10: directly destroy the element
    }
    else
    {
        // Shutting down: yield, process, then deallocate
        yield(0);
        processNext(this);
        deallocateObject(removedElement);       // FUN_00792d80: deallocate memory
    }

checkIdle:
    // Check if all queues are empty to signal idle state
    if ((*(int*)(this + 0x88) == 0) &&          // +0x88: another queue size
        (*(int*)(this + 0xA0) == 0) &&          // +0xA0: yet another queue size
        (count - 1 == 0) &&                     // current queue empty (count already decremented)
        (*(int*)(this + 0xB8) == 0))            // +0xB8: fourth queue size
    {
        setGlobalIdleEvent(&g_idleEvent);       // FUN_004086d0: signal idle
    }
    else
    {
        resetGlobalIdleEvent(&g_idleEvent);     // FUN_00408680: reset idle signal
    }
}