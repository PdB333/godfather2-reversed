// FUNC_NAME: JobManager::processCompletedJobs
void JobManager::processCompletedJobs() {
    // Global head of linked list of job nodes (DAT_011a0ef0)
    int* jobNode = (int*)DAT_011a0ef0;

    while (jobNode != 0) {
        // Check if this job belongs to the current manager instance (this pointer comparison)
        bool ownerMatch = (*(int*)((char*)jobNode + 0x60) == (int)this);
        int state = *(int*)((char*)jobNode + 0x68);
        bool stateMatch = (state == 4 || state == 2); // Completed or ready to finalize states

        if (ownerMatch && stateMatch) {
            // Notify (likely debug/log or event) – first call
            FUN_005dbc10(
                *(char*)((char*)jobNode + 0x64),  // +0x64: some byte flag
                *(int*)((char*)jobNode + 0x5c),   // +0x5C: dword identifier
                *(char*)((char*)jobNode + 0x65)   // +0x65: another byte
            );

            // Mark job as processed (state change, argument 1 = true)
            FUN_005f3640(jobNode, 1);

            // Copy +0x88 into +0x8C (probably a timer or value completion)
            *(int*)((char*)jobNode + 0x8C) = *(int*)((char*)jobNode + 0x88);

            // Set flag at +0x67 to 0xFF (fully processed)
            *(char*)((char*)jobNode + 0x67) = 0xFF;

            // Notify again after processing
            FUN_005dbc10(
                *(char*)((char*)jobNode + 0x64),
                *(int*)((char*)jobNode + 0x5C),
                *(char*)((char*)jobNode + 0x65)
            );
        }

        // Advance to next node in linked list (next pointer at offset +0x04)
        jobNode = *(int**)((char*)jobNode + 4);
    }
}