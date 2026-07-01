// FUNC_NAME: EventScheduler::scheduleEvent
// Function address: 0x0090e2d0
// Schedules a new event/job into the scheduler's dynamic array.
// This: [ +0x14: nextJobId, +0x18: jobArray, +0x1c: jobCount, +0x20: jobCapacity, +0x11: isProcessing ]

int __thiscall EventScheduler::scheduleEvent(
    int this,
    int eventType,
    int eventData,
    uint flags,
    int extraData,
    int context,
    int param_7)
{
    uint* pJob;
    int jobId;
    uint slotIndex;
    int retId;
    uint* newJob;
    undefined4* jobSlot;
    struct EventSignal localEvent;

    // Check if we should cancel an existing job with the same "pending" flag (bit 0)
    if ((flags & 1) != 0 && *(int*)(this + 0x1c) != 0)
    {
        slotIndex = 0;
        jobSlot = (undefined4*)*(int*)(this + 0x18);
        do
        {
            pJob = (uint*)*jobSlot;
            if ((*pJob & 1) != 0)  // Check if job has "pending" flag
            {
                if (*(char*)(this + 0x11) == '\0')  // Not currently processing?
                {
                    // Remove the job: shift last element into its place
                    if (slotIndex != *(int*)(this + 0x1c) - 1)
                    {
                        *(undefined4*)(*(int*)(this + 0x18) + slotIndex * 4) =
                            *(undefined4*)(*(int*)(this + 0x18) + -4 + *(int*)(this + 0x1c) * 4);
                    }
                    *(int*)(this + 0x1c) = *(int*)(this + 0x1c) - 1;
                    // Cleanup the removed job
                    releaseJob(context);      // FUN_0090daf0
                    processPendingJobs();     // FUN_0090d920
                    deleteJob(pJob);          // FUN_009c8eb0
                }
                else
                {
                    // Mark job as cancelled (set bit 6) instead of removing
                    *pJob = *pJob | 0x40;
                    releaseJob(context);
                }
                break;
            }
            slotIndex++;
            jobSlot++;
        } while (slotIndex < *(uint*)(this + 0x1c));
    }

    // Assign a new job ID
    jobId = *(int*)(this + 0x14);
    *(int*)(this + 0x14) = jobId + 1;
    if (jobId + 1 == -1)
    {
        *(int*)(this + 0x14) = 0;  // Wrap around, skip -1
    }
    retId = jobId;

    // If no jobs are pending and we don't have the "no auto dispatch" flag, signal an event
    if (*(int*)(this + 0x1c) == 0 && (flags & 0x10) == 0)
    {
        localEvent.param0 = DAT_0112ffe0;  // Event handle
        localEvent.param1 = 0;
        localEvent.param2 = 0;
        setEvent(&localEvent, 0);  // FUN_00408a00
    }

    // Allocate memory for the new job (size 0x50 = 80 bytes)
    newJob = (uint*)mallocJob(0x50);  // FUN_009c8e50
    if (newJob == 0)
    {
        return 0;  // Allocation failed, but we still return jobId? Actually decompiled sets uVar5=0 and continues. But later it stores uVar5. So if alloc fails, job pointer is 0 and inserted? That seems odd. Might be an error path. We'll follow decompiled: if iVar4==0 then uVar5=0, else uVar5=constructJob(...). Then later store uVar5. So if alloc fails, store 0.
    }
    else
    {
        // Construct the job object
        constructJob(jobId, eventType, eventData, flags, extraData, context, param_7);  // FUN_0090d880
    }

    // Check if array needs to grow
    if (*(int*)(this + 0x1c) == *(int*)(this + 0x20))
    {
        int newCapacity = *(int*)(this + 0x20);
        if (newCapacity == 0)
            newCapacity = 1;
        else
            newCapacity *= 2;
        growJobArray(newCapacity);  // FUN_0090dcd0
    }

    // Insert the new job into the array
    jobSlot = (undefined4*)(*(int*)(this + 0x18) + *(int*)(this + 0x1c) * 4);
    *(int*)(this + 0x1c) = *(int*)(this + 0x1c) + 1;
    if (jobSlot != (undefined4*)0x0)
    {
        *jobSlot = (undefined4)newJob;
    }

    // Unlock the critical section
    unlockCriticalSection(&DAT_012069c4);  // FUN_00408680

    // If not processing, attempt to dispatch jobs
    if (*(char*)(this + 0x11) == '\0')
    {
        dispatchJobs();  // FUN_0090df00
    }

    return jobId;
}