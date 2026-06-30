// FUNC_NAME: GameTaskManager::updateTasks
void GameTaskManager::updateTasks(void)
{
    int status;
    TaskEntry* entryPtr;

    // Update internal state (e.g., check timers, load queued data)
    updateInternalState();

    // If the optional subsystem is active (e.g., streaming or mission system)
    if (g_subsystemActive != 0) {
        // Call virtual function at +0x44 on the primary game object
        // This likely checks if a certain condition is met (e.g., "isReady" or "isPaused")
        status = (*(code**)(*g_gameObject + 0x44))(g_gameObject, 0, 0, 0, 0);
        // Magic constant 0x88766868 (interpreted as -0x7789f798) indicates a specific result
        if (status == 0x88766868) {
            g_subsystemReadyFlag = 1;
        }
    }

    // Determine pointer to task entry based on current index
    if (g_currentTaskIndex < 0x1000) {
        // Array of TaskEntry structures, each 0x38 bytes
        entryPtr = &g_taskArray + g_currentTaskIndex * 0x38;
    }
    else {
        entryPtr = (TaskEntry*)0x0;
    }

    // Process the task entry with the given index
    if (g_currentTaskIndex == 0xffffffff) {
        processTaskEntry(0xffffffff, entryPtr);
        return;
    }
    processTaskEntry(g_currentTaskIndex, entryPtr);
}