// FUNC_NAME: GodfatherGameManager::handleCompletedTask
void __fastcall GodfatherGameManager::handleCompletedTask(void* thisPtr)
{
    // +0x1e0: Pointer to a currently active task/job
    int* pendingTask = *(int**)((char*)thisPtr + 0x1e0);
    if (pendingTask != nullptr)
    {
        // +0x08: Completion flag (0 = finished, non-zero = still running)
        if (*(int*)(pendingTask + 2) == 0)   // offset 8 = element index 2 (4 bytes each)
        {
            destroyTask(pendingTask);        // FUN_009e7450: free task memory
            onTaskCompleted();               // FUN_007073c0: post-cleanup logic (using this)
        }
    }
}