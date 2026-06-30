// FUNC_NAME: JobManager::createJob

int JobManager::createJob(void* param_1, int param_2, int param_3) {
    // Increment job counter at offset 0x244
    this->jobCount++;

    // Validate job type and check if system is active
    if (validateJobType(param_3) && isJobSystemActive()) {
        int jobData = prepareJobData(this, param_2); // Creates internal data for the job
        if (jobData != 0) {
            // Allocate a 0x1c-byte job object
            Job* job = (Job*)operatorNew(0x1c);
            if (job != nullptr) {
                // Initialize job fields
                job->internalData = (void*)jobData;   // +0x10: pointer to job data
                job->field8 = 0;                       // +0x08: byte (flags?)
                job->fieldC = 0;                       // +0x0C: int (job ID?)
                job->jobType = param_3;                // +0x14: job type enum
                job->nextJob = nullptr;                // +0x18: linked list pointer
                // Post-creation hook
                onJobCreated();
                // Register job with the context and the job list head (this+0x04)
                registerJob(param_1, this->jobListHead);
                return (int)job;
            }
        }
    }
    return 0;
}