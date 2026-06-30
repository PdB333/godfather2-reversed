// FUNC_NAME: TaskQueueManager::processQueue
void __fastcall TaskQueueManager::processQueue(int thisPtr)
{
    int originalCount = *(int *)(thisPtr + 0xB8); // +0xB8: number of items in queue
    int i = originalCount;
    while (i = i - 1, i >= 0)
    {
        void *taskPtr = *(void **)(*(int *)(thisPtr + 0xB4) + i * 4); // +0xB4: pointer to array of task pointers
        bool shouldRemove = FUN_00791230(); // global condition: should we remove and process this task now?
        if (!shouldRemove)
        {
            // Task not ready yet; maybe initialize a deferred callback
            int globalObj = FUN_00791300(); // get some global state object
            if (globalObj != 0 && *(int *)(globalObj + 0x158) == 0)
            {
                // Set a callback function pointer at offset 0x158
                *(int *)(globalObj + 0x158) = &LAB_006b2cc0; // function pointer to handler
            }
        }
        else
        {
            // Remove this task from the array (replace with last element)
            if (i != *(int *)(thisPtr + 0xB8) - 1)
            {
                *(void **)(*(int *)(thisPtr + 0xB4) + i * 4) = *(void **)(*(int *)(thisPtr + 0xB4) + (*(int *)(thisPtr + 0xB8) - 1) * 4);
            }
            *(int *)(thisPtr + 0xB8) = *(int *)(thisPtr + 0xB8) - 1; // decrement count
            FUN_00790110(0); // signal something
            FUN_00791350(thisPtr); // notify manager of removal
            FUN_00792d80(taskPtr); // release/deallocate the task
        }
    }
    if (*(int *)(thisPtr + 0xB8) != originalCount)
    {
        FUN_006b2f70(); // update internal state (e.g., recalc empty flags)
        // Check if all sub-queues are empty
        if (*(int *)(thisPtr + 0x88) == 0 &&    // +0x88: some sub-queue 1
            *(int *)(thisPtr + 0xA0) == 0 &&    // +0xA0: sub-queue 2
            *(int *)(thisPtr + 0xAC) == 0 &&    // +0xAC: sub-queue 3
            *(int *)(thisPtr + 0xB8) == 0)      // main queue empty
        {
            FUN_004086d0(&DAT_0112a640); // wait/suspend on global sync object
        }
        else
        {
            FUN_00408680(&DAT_0112a640); // signal/resume global sync object
        }
    }
}