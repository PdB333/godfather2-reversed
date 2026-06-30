// FUNC_NAME: JobManager::getFirstActiveJobId
int JobManager::getFirstActiveJobId(int* jobSlots) {
    // Check if any of the four job slots are active (non-zero)
    if ((jobSlots[0] != 0) || (jobSlots[1] != 0) || (jobSlots[2] != 0) || (jobSlots[3] != 0)) {
        // Get the global job manager instance
        int* globalManager = (int*)getGlobalJobManager();
        if ((globalManager != nullptr) && (globalManager[0] != 0)) {
            // Return the first active job ID from the global manager
            return globalManager[0];
        }
    }
    return 0; // No active jobs
}