// FUNC_NAME: JobManager::processJob
void JobManager::processJob(void* param_1, void* param_2, uint param_3, uint param_4, uint param_5, uint param_6) {
    if (param_2 == nullptr) {
        return;
    }

    // Check if the job's active flag at offset +0x28 is set
    if (*(char*)((uint8_t*)param_2 + 0x28) == '\0') {
        // Try to initialize the job
        initializeJob(); // 0x0060c2a0 – likely sets the flag
        if (*(char*)((uint8_t*)param_2 + 0x28) == '\0') {
            return; // Still not active – abort
        }
    }

    // Remove job from the global active list under critical section
    EnterCriticalSection(&g_criticalSection); // DAT_012224f8

    int i = 0;
    if (g_activeJobCount > 0) { // DAT_01205854
        do {
            if (g_activeJobs[i] == param_2) { // DAT_011e28f0
                g_activeJobCount--;
                if (g_activeJobCount > 0) {
                    // Replace removed entry with last element
                    g_activeJobs[i] = g_activeJobs[g_activeJobCount];
                }
                break;
            }
            i++;
        } while (i < g_activeJobCount);
    }

    LeaveCriticalSection(&g_criticalSection);

    // Proceed with actual job processing (e.g., completing the operation)
    completeJob(param_1, param_3, param_4, param_5, param_6); // 0x0060cae0
}