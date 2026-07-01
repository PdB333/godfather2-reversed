// FUNC_NAME: AsyncLoader::waitForCompletion
void __thiscall AsyncLoader::waitForCompletion(TaskHashParam taskParam) {
    // Initialize the loading task
    startLoadingTask(taskParam);
    // Register this task with a specific hash (e.g., 0x556abb68 for main assets)
    registerTaskForHash(taskParam, 0x556abb68);

    // Wait until batch processing is complete
    while (!isBatchProcessingComplete()) {
        // Attempt to fetch a new batch (side effect: advance internal queue)
        fetchNextBatch();

        // Check if there is an active task in the current batch
        if (isActiveTaskPresent() == 0) {
            // Get the active task object
            void* activeTask = getActiveTask();
            // Update our internal flag indicating whether the task is running
            // Offset +0x6c appears to be a boolean member (e.g., m_bTaskRunning)
            *(bool*)(this + 0x6c) = (*(int*)(activeTask + 8) != 0);
        }

        // Process the next batch step (e.g., load assets, update progress)
        processNextBatchStep();
    }
}