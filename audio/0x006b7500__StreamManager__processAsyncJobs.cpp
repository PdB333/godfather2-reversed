// FUNC_NAME: StreamManager::processAsyncJobs
void __thiscall StreamManager::processAsyncJobs(StreamManager* this, uint32_t streamContextId) {
    char isDone;
    StreamJob* job;

    // Check a flag at offset 0x290 to decide the operation mode
    if (*(int32_t*)((uint8_t*)this + 0x290) < 0) {
        beginReadOperation(streamContextId);   // FUN_008b9590
    } else {
        beginWriteOperation(streamContextId);  // FUN_008bb320
    }

    initializeJobProcessor(streamContextId, 0x6a8acf44); // magic cookie for async jobs
    isDone = hasPendingJobs(); // FUN_0043b120
    while (isDone == '\0') {
        finishCurrentJob();       // FUN_0043b210 (might be start or finish?)
        int32_t jobType = getJobType(); // FUN_0043ab70
        if (jobType == 0) {
            // Read-type job: pop the job again (?) and process it
            job = (StreamJob*)popJob(); // FUN_0043b210
            processReadJob(job->data, job->data); // FUN_006b7240 - note: both params same, likely a bug or intentional copy?
        } else if (jobType == 1) {
            // Write-type job: OR a new flag into status
            job = (StreamJob*)popJob();
            *(uint32_t*)((uint8_t*)this + 0x290) |= (uint32_t)(uint8_t)job->flags;
        }
        advanceJobQueue(); // FUN_0043b1a0
        isDone = hasPendingJobs();
    }
}